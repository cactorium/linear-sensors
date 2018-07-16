#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

#define FIR_HP_BUFFER_SZ (100)
#define FIR_LP_BUFFER_SZ1 (64)
#define FIR_LP_BUFFER_SZ2 (32)

static int32_t feed_fir1(uint16_t i);
static int32_t feed_fir2(int32_t i);
static int32_t feed_fir3(int32_t i);

#include "trig.h"

#define BASE_FREQ           1000
#define SAMPLE_RATE         96000
#define SAMPLE_NUM_PERIODS  26
#define TOTAL_NUM_PERIODS   40
#define BASE_PERIOD         (SAMPLE_RATE/BASE_FREQ)
#define SAMPLE_BUFFER_SZ    (SAMPLE_NUM_PERIODS*BASE_PERIOD)
#define SAMPLE_PERIOD       SAMPLE_BUFFER_SZ 

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
  // 96 kHz system clock
  systick_set_reload(48000000/96000-1);
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


volatile int32_t adc_idx = -1;
volatile int32_t sample_idx = -1;
volatile uint8_t calc_finished = 0;
volatile uint8_t sample_full = 0;

// sys tick rate is 96 KHz
void sys_tick_handler() {
  static uint8_t tick = 0;
  // start a conversion
  if (adc_idx < SAMPLE_BUFFER_SZ) {
    adc_start_conversion_regular(ADC1);
  }

  if (tick == 0 && adc_idx >= TOTAL_NUM_PERIODS*BASE_PERIOD) {
    if (calc_finished) {
      sample_idx = -1;
      adc_idx = 0;
      calc_finished = 0;
      sample_full = 0;
    } else {
      usart_send(USART1, 'o');
    }
  } else {
    ++adc_idx;
  }
  // 96 KHz/12 = 8 KHz
  int tick_half = tick;
  if (tick_half >= 48) {
    tick_half -= 48;
  }
  if (tick_half == 0) { 
    gpio_toggle(PHASE_PORT(0), PHASE_PIN(0));
    gpio_toggle(PHASE_PORT(4), PHASE_PIN(4));
  } else if (tick_half == 12) {
    gpio_toggle(PHASE_PORT(1), PHASE_PIN(1));
    gpio_toggle(PHASE_PORT(5), PHASE_PIN(5));
  } else if (tick_half == 24) {
    gpio_toggle(PHASE_PORT(2), PHASE_PIN(2));
    gpio_toggle(PHASE_PORT(6), PHASE_PIN(6));
  } else if (tick_half == 36) {
    gpio_toggle(PHASE_PORT(3), PHASE_PIN(3));
    gpio_toggle(PHASE_PORT(7), PHASE_PIN(7));
  }
  ++tick;
  if (tick == 96) {
    tick = 0;
  }
}

volatile uint16_t samples[SAMPLE_BUFFER_SZ];

void adc_comp_isr() {
  int idx = adc_idx;
  int tmp = adc_read_regular(ADC1);
  samples[idx] = tmp;
  sample_idx = idx;
  if (idx == SAMPLE_BUFFER_SZ - 1) {
    sample_full = 1;
  }
}

enum usart_state {
  USART_FSM_IDLE,
  USART_FSM_SAMPLES,
  USART_FSM_DEBUG,
  USART_FSM_WRITE_IQ_INIT,
  USART_FSM_WRITE_IQ_DOWRITE
} usart_state = USART_FSM_IDLE;

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

#include "trig.c"

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
  if (phase_calc_count < SAMPLE_PERIOD) {
    phase_i += (((int64_t)sin32(phase_calc_count))*val)/2048;
    phase_q += (((int64_t)cos32(phase_calc_count))*val)/2048;
  }
  phase_calc_count++;
  return phase_calc_count == SAMPLE_PERIOD;
}

uint8_t iq_ready = 0;
uint64_t usart_i, usart_q;

// have the ADC ISR fill up a buffer with values while
// calculating over it in the main loop. empty the buffer after the calculation
// is complete and wait for the start of the next cycle
int main() {
  clock_setup();

  gpio_setup();
  uart_setup();
  adc_setup();
  systick_setup();

  while (1) {
    feed_phase_start();
    for (int i = 0; i < SAMPLE_BUFFER_SZ; ++i) {
      while (sample_idx < i) {}
      uint16_t tmp = samples[i];

      int32_t fir_out1 = feed_fir1(tmp);
      int32_t fir_out2 = feed_fir2(fir_out1);
      int32_t fir_out3 = feed_fir3(fir_out2);

      feed_phase_calc(fir_out3);
    }
    calc_finished = 1;
    usart_i = phase_i;
    usart_q = phase_q;
    while (usart_state == USART_FSM_IDLE) {
      // NOTE: race condition with a USART receive at the exact same moment
      // so that's why this is reduced to a single instruction, to make
      // failure impotent instead of potentially causing data corruption
      usart_state = USART_FSM_WRITE_IQ_INIT;
      usart_enable_tx_interrupt(USART1);
      nvic_set_pending_irq(NVIC_USART1_IRQ);
    }
    while (calc_finished) {}
  }

  return 0;
}

const char hexstr[] = "0123456789abcdef";
static void usart_fsm_send_nibble_msb32(uint32_t b, uint8_t nibble) {
  usart_send(USART1, hexstr[(b >> (4*(7-nibble))) & 0x0f]);
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
        } else if (usart_data.samples.nibble < 10) {
          usart_fsm_send_nibble_msb32(samples[usart_data.samples.word], usart_data.samples.nibble-2);
        } else {
          usart_send(USART1, ',');
        }
      } else {
        if (usart_data.samples.nibble == 0) {
          usart_send(USART1, '\r');
        } else if (usart_data.samples.nibble == 1) {
          usart_send(USART1, '\n');
          sample_full = 0;
          usart_state = USART_FSM_IDLE;
        }
      }

      ++usart_data.samples.nibble;
      if (usart_data.samples.nibble > 10) {
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
        usart_fsm_send_nibble_msb64(usart_i, usart_data.iq.nibble);
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
        usart_fsm_send_nibble_msb64(usart_q, usart_data.iq.nibble);
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
  static int32_t sum = 0;

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
