#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

#define FIR_HP_BUFFER_SZ 100
#define FIR_LP_BUFFER_SZ1 64
#define FIR_LP_BUFFER_SZ2 32

static int32_t feed_fir1(uint16_t i);
static int32_t feed_fir2(int32_t i);
static int32_t feed_fir3(int32_t i);

#include "trig.h"

#define SAMPLE_BUFFER_SZ 1000

#define PHASE_PIN(x) ((uint32_t[]){GPIO6, GPIO8, GPIO7, GPIO9, GPIO0, GPIO10, GPIO1, GPIO11})[x]
#define IS_PORT_B(x) ((uint8_t[]){0, 0, 0, 0, 1, 0, 1, 0})[x]
#define PHASE_PORT(x) (IS_PORT_B(x) ? GPIO_PORT_B_BASE : GPIO_PORT_A_BASE)

#define PINA_MASK(x) (IS_PORT_B(x) ? 0 : PHASE_PIN(x))
#define PINB_MASK(x) (IS_PORT_B(x) ? PHASE_PIN(x) : 0)

#define TX_PIN GPIO6 // port B
#define RX_PIN GPIO7 // port B

#define ADC_PIN GPIO0 // port A

static void clock_setup() {
  // use external clock
  rcc_clock_setup_in_hse_8mhz_out_48mhz();
}

static void gpio_setup() {
	// enable clocks for GPIO
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

  // set up pins for pulses
  gpio_mode_setup(GPIO_PORT_A_BASE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
      PINA_MASK(0)|PINA_MASK(1)|PINA_MASK(2)|PINA_MASK(3)|
      PINA_MASK(4)|PINA_MASK(5)|PINA_MASK(6)|PINA_MASK(7));
  gpio_mode_setup(GPIO_PORT_B_BASE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
      PINB_MASK(0)|PINB_MASK(1)|PINB_MASK(2)|PINB_MASK(3)|
      PINB_MASK(4)|PINB_MASK(5)|PINB_MASK(6)|PINB_MASK(7));

  gpio_clear(GPIO_PORT_A_BASE, PINA_MASK(0)|PINA_MASK(1)|PINA_MASK(2)|PINA_MASK(3));
  gpio_clear(GPIO_PORT_B_BASE, PINB_MASK(0)|PINB_MASK(1)|PINB_MASK(2)|PINB_MASK(3));

  gpio_set(GPIO_PORT_A_BASE, PINA_MASK(4)|PINA_MASK(5)|PINA_MASK(6)|PINA_MASK(7));
  gpio_set(GPIO_PORT_B_BASE, PINB_MASK(4)|PINB_MASK(5)|PINB_MASK(6)|PINB_MASK(7));

  // set up pins for usart
  gpio_mode_setup(GPIO_PORT_B_BASE, GPIO_MODE_AF, GPIO_PUPD_NONE, TX_PIN|RX_PIN);
  gpio_set_af(GPIO_PORT_B_BASE, GPIO_AF0, TX_PIN|RX_PIN);

  // set up pin for ADC
  gpio_mode_setup(GPIO_PORT_A_BASE, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_PIN);
}

static void systick_setup() {
  // disable counter and interrupt
  systick_interrupt_disable();
  systick_counter_disable();

  systick_set_clocksource(STK_CSR_CLKSOURCE);
  // 200 kHz system clock
  systick_set_reload(48000000/200000-1);
  systick_clear();

  systick_interrupt_enable();
  systick_counter_enable();
}

static void adc_setup() {
  // enable clock for ADC
  rcc_periph_clock_enable(RCC_ADC);

  adc_power_off(ADC1);
  // divide 48 MHz by 4 to get 12 MHz; max clock is 14 MHz
  adc_set_clk_source(ADC1, ADC_CLKSOURCE_PCLK_DIV4);
  adc_calibrate(ADC1);
  adc_set_single_conversion_mode(ADC1);
  adc_set_right_aligned(ADC1);

  static uint8_t channels[] = { 0 };
  adc_set_regular_sequence(ADC1, 1, channels);

  adc_set_sample_time_on_all_channels(ADC1, ADC_SMPTIME_007DOT5);
	adc_set_resolution(ADC1, ADC_RESOLUTION_12BIT);

  adc_disable_external_trigger_regular(ADC1);
	adc_disable_analog_watchdog(ADC1);

  nvic_enable_irq(NVIC_ADC_COMP_IRQ);
  adc_enable_eoc_interrupt(ADC1);

	adc_power_on(ADC1);
}

static void uart_setup() {
	// enable clocks for USART1
	rcc_periph_clock_enable(RCC_USART1);

	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_stopbits(USART1, USART_CR2_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

  nvic_enable_irq(NVIC_USART1_IRQ);
  usart_enable_rx_interrupt(USART1);

	usart_enable(USART1);
}


int16_t adc_idx = -1;

// sys tick rate is 200 KHz
void sys_tick_handler() {
  static uint8_t start_adc = 0;
  static uint8_t count = 0;
  static uint8_t tick = 0;
  // halve to get 100 KHz ADC sample rate
  if (start_adc) {
    // start a conversion
    adc_start_conversion_regular(ADC1);
    if (adc_idx >= SAMPLE_BUFFER_SZ && count == 25 && tick == 0) {
      adc_idx = 0;
    } else {
      ++adc_idx;
    }
  }
  start_adc = !start_adc;
  // 200 KHz/25 = 8 KHz
  if (count == 25) {
    count = 0;
    switch (tick & 3) {
    case 0:
      gpio_toggle(PHASE_PORT(0), PHASE_PIN(0));
      gpio_toggle(PHASE_PORT(4), PHASE_PIN(4));
      break;
    case 1:
      gpio_toggle(PHASE_PORT(1), PHASE_PIN(1));
      gpio_toggle(PHASE_PORT(5), PHASE_PIN(5));
      break;
    case 2:
      gpio_toggle(PHASE_PORT(2), PHASE_PIN(2));
      gpio_toggle(PHASE_PORT(6), PHASE_PIN(6));
      break;
    case 3:
      gpio_toggle(PHASE_PORT(3), PHASE_PIN(3));
      gpio_toggle(PHASE_PORT(7), PHASE_PIN(7));
    }

    tick = (tick + 1) & 0x07;
  }
  ++count;
}

uint16_t sample = 0;
uint16_t sample_idx = 0;
uint8_t new_sample = 0, overrun = 0;

void adc_comp_isr() {
  int tmp = adc_read_regular(ADC1);
  sample_idx = adc_idx;
  sample = tmp;
  if (new_sample) {
    overrun = 1;
  }
  new_sample = 1;
}

enum usart_state {
  USART_FSM_IDLE,
  USART_FSM_SAMPLES,
  USART_FSM_DEBUG,
  USART_FSM_WRITE_IQ_INIT,
  USART_FSM_WRITE_IQ_DOWRITE
} usart_state = USART_FSM_IDLE;

uint8_t sample_full = 0, sample_start = 0;

union {
  struct {
    int8_t nibble;
    int16_t word;
  } samples;
  struct {
    int8_t nibble;
    int16_t word;
  } debug;
  struct {
    int8_t nibble;
    int16_t word;
  } iq;
} usart_data;

static void run_tx_fsm();

void usart1_isr() {
  if (usart_get_flag(USART1, USART_ISR_RXNE)) {
    uint16_t c = usart_recv(USART1);
    if (usart_state == USART_FSM_IDLE) {
      if (c == 'i') {
        usart_state = USART_FSM_DEBUG;
        usart_data.debug.nibble = 0;
        usart_data.debug.word = 0;
      }
      if (c == 'd' && sample_full) {
        usart_state = USART_FSM_SAMPLES;
        usart_data.samples.nibble = 0;
        usart_data.samples.word = 0;
      }
    }
  }
  // clear the TX flag in case we're not transmitting something
  run_tx_fsm();
}

uint8_t phase_started = 0;
int64_t phase_i = 0;
int64_t phase_q = 0;
uint16_t phase_calc_count = 0;

static void feed_phase_start() {
  phase_calc_count = 0;
  phase_started = 1;
  phase_i = 0;
  phase_q = 0;
}

// returns 1 if the period has finished, 0 otherwise
static int8_t feed_phase_calc(int32_t val) {
  // wait until the feed's been started
  if (!phase_started) {
    return 0;
  }
  if (phase_calc_count < 1000) {
    phase_i += (((int64_t)sin32(phase_calc_count))*val)/2048;
    phase_q += (((int64_t)cos32(phase_calc_count))*val)/2048;
    phase_calc_count++;
  }
  return phase_calc_count == 1000;
}

uint8_t iq_ready = 0;
uint64_t usart_i, usart_q;

uint16_t samples[SAMPLE_BUFFER_SZ];

int main() {
  clock_setup();

  gpio_setup();
  uart_setup();
  adc_setup();
  systick_setup();

  while (1) {
    // asm volatile ("wfi");
    if (new_sample) {
      uint16_t tmp = sample;
      uint16_t idx = sample_idx;
      new_sample = 0;

      // write a copy for debugging purposes
      if (idx < SAMPLE_BUFFER_SZ && !sample_full) {
        if (!sample_start || (sample_start && idx == 0)) {
          sample_start = 0;
          samples[idx] = tmp;
          if (idx == SAMPLE_BUFFER_SZ - 1) {
            sample_full = 1;
          }
        }
      }

      int32_t fir_out1 = feed_fir1(tmp);
      int32_t fir_out2 = feed_fir2(fir_out1);
      int32_t fir_out3 = feed_fir3(fir_out2);
      // NOTE: maybe this should be offset by some amount to compensate
      // for the FIR delay
      if (idx == 0) { 
        feed_phase_start();
      }
      if (feed_phase_calc(fir_out3)) {
        // copy the phase data into some other location so the USART FSM can use it,
        // and set iq_ready to trigger the FSM when it's available
        usart_i = phase_i;
        usart_q = phase_q;
        iq_ready = 1;
      }
    }
    if (overrun) {
      usart_send(USART1, 'o');
      overrun = 0;
    }
    if (iq_ready) {
      if (usart_state == USART_FSM_IDLE) {
        // NOTE: race condition with a USART receive at the exact same moment
        // so that's why this is reduced to a single instruction, to make
        // failure impotent instead of potentially causing data corruption
        usart_state = USART_FSM_WRITE_IQ_INIT;
        nvic_set_pending_irq(NVIC_USART1_IRQ);
      // } else {
        // usart_send(USART1, 'b');
      }
    }
  }

  return 0;
}

const char hexstr[] = "0123456789abcdef";
static void usart_fsm_send_nibble_msb16(uint16_t b, uint8_t nibble) {
  usart_send(USART1, hexstr[(b >> (4*(3-nibble))) & 0x0f]);
}
static void usart_fsm_send_nibble_msb64(uint64_t b, uint8_t nibble) {
  usart_send(USART1, hexstr[(b >> (4*(15-nibble))) & 0x0f]);
}

// NOTE: will stop running if it doesn't transmit a character per call
// can be resumed by calling this function from outside the ISR
static void run_tx_fsm() {
  if (usart_get_flag(USART1, USART_ISR_TXE)) {
    switch (usart_state) {
    case USART_FSM_SAMPLES:
      if (usart_data.samples.word < SAMPLE_BUFFER_SZ) {
        if (usart_data.samples.nibble == 0) {
          usart_send(USART1, '0');
        } else if (usart_data.samples.nibble == 1) {
          usart_send(USART1, 'x');
        } else if (usart_data.samples.nibble < 6) {
          usart_fsm_send_nibble_msb16(samples[usart_data.samples.word], usart_data.samples.nibble-2);
        } else {
          usart_send(USART1, ',');
        }
      } else {
        if (usart_data.samples.nibble == 0) {
          usart_send(USART1, '\r');
        } else if (usart_data.samples.nibble == 1) {
          usart_send(USART1, '\n');
          sample_full = 0;
          sample_start = 1;
          usart_state = USART_FSM_IDLE;
        }
      }

      ++usart_data.samples.nibble;
      if (usart_data.samples.nibble > 6) {
        usart_data.samples.nibble = 0;
        ++usart_data.samples.word;
      }
      break;
    case USART_FSM_DEBUG:
      usart_state = USART_FSM_IDLE;
      break;
    case USART_FSM_WRITE_IQ_INIT:
      usart_data.iq.nibble = 0;
      usart_data.iq.word = 0;

      usart_state = USART_FSM_WRITE_IQ_DOWRITE;
      break;
    case USART_FSM_WRITE_IQ_DOWRITE:
      switch (usart_data.iq.word) {
      case 0:
        usart_fsm_send_nibble_msb64(phase_i, usart_data.iq.nibble);
        ++usart_data.iq.nibble;
        if (usart_data.iq.nibble == 16) {
          usart_data.iq.nibble = 0;
          ++usart_data.iq.word;
        }
        break;
      case 1:
        usart_send(USART1, ' ');
        ++usart_data.iq.word;
        break;
      case 2:
        usart_fsm_send_nibble_msb64(phase_i, usart_data.iq.nibble);
        ++usart_data.iq.nibble;
        if (usart_data.iq.nibble == 16) {
          usart_data.iq.nibble = 0;
          ++usart_data.iq.word;
        }
        break;
      case 3:
        usart_send(USART1, '\r');
        ++usart_data.iq.word;
        break;
      case 4:
        usart_send(USART1, '\n');
        usart_state = USART_FSM_IDLE;
        iq_ready = 0;
        break;
      }
      break;
    case USART_FSM_IDLE:
    default:
      break;
    }
  }
  if (usart_state != USART_FSM_IDLE) {
    usart_enable_tx_interrupt(USART1);
  } else {
    usart_disable_tx_interrupt(USART1);
  }
}

// hp, 100 window
static int32_t feed_fir1(uint16_t i) {
  static uint16_t buf[FIR_HP_BUFFER_SZ] = {0};
  static uint8_t half_ptr = FIR_HP_BUFFER_SZ/2;
  static uint8_t cur_ptr = 0;
  static uint32_t sum = 0;

  sum += i;
  sum -= buf[cur_ptr];
  buf[cur_ptr] = i;

  ++cur_ptr;
  if (cur_ptr >= FIR_HP_BUFFER_SZ) {
    cur_ptr = 0;
  }
  ++half_ptr;
  if (half_ptr >= FIR_HP_BUFFER_SZ) {
    half_ptr = 0;
  }
  
  return FIR_HP_BUFFER_SZ*buf[half_ptr] - sum;
}

// lp, 64 window
static int32_t feed_fir2(int32_t i) {
  static int32_t buf[FIR_LP_BUFFER_SZ1] = {0};
  static uint8_t cur_ptr = 0;
  static int32_t sum = 0;

  sum += i;
  sum -= buf[cur_ptr];
  buf[cur_ptr] = i;

  ++cur_ptr;
  if (cur_ptr >= FIR_LP_BUFFER_SZ1) {
    cur_ptr = 0;
  }
  
  return sum;
}

// lp, 32 window
static int32_t feed_fir3(int32_t i) {
  static int32_t buf[FIR_LP_BUFFER_SZ2] = {0};
  static uint8_t cur_ptr = 0;
  static int32_t sum = 0;

  sum += i;
  sum -= buf[cur_ptr];
  buf[cur_ptr] = i;

  ++cur_ptr;
  if (cur_ptr >= FIR_LP_BUFFER_SZ2) {
    cur_ptr = 0;
  }
  
  return sum;
}
