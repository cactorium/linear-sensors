#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

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

	usart_enable(USART1);
}

uint16_t count = 0;
uint16_t adc_count = 0;
uint8_t tick = 0;
uint8_t start_adc = 0;

int16_t adc_idx = -1;
uint16_t adc_data[1000];

// sys tick rate is 200 KHz
void sys_tick_handler() {
  // halve to get 100 KHz ADC sample rate
  if (start_adc) {
    // start a conversion
    adc_start_conversion_regular(ADC1);
    if (adc_idx == -1 && count == 25 && tick == 0) {
      adc_idx = 0;
    } else if (adc_idx < 1000 && adc_idx != -1) {
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

static void usart_send_nibble(uint8_t n) {
  const char s[] = "0123456789abcdef";
  usart_send_blocking(USART1, s[n & 15]);
}

static void usart_send_byte(uint8_t b) {
  usart_send_nibble(b >> 4);
  usart_send_nibble(b & 0x0f);
}

static void usart_send_int16(uint16_t i) {
  usart_send_byte(i >> 8);
  usart_send_byte(i & 0x0ff);
}

static void usart_send_newline() {
  usart_send_blocking(USART1, '\r');
  usart_send_blocking(USART1, '\n');
}

void adc_comp_isr() {
  int tmp = adc_read_regular(ADC1);
  if (adc_idx < 1000 && adc_idx != -1) {
    adc_data[adc_idx] = tmp;
  }
}

int main() {
  clock_setup();

  gpio_setup();
  uart_setup();
  adc_setup();
  systick_setup();

  while (1) {
    uint16_t c = usart_recv_blocking(USART1);
    if (c == 'i') {
      int last_idx = adc_idx;
      usart_send_int16(last_idx);
      usart_send_int16(start_adc);
      usart_send_newline();
    }
    if (c == 'd') {
      for (int i = 0; i < 1000; ++i) {
        usart_send_blocking(USART1, '0');
        usart_send_blocking(USART1, 'x');
        usart_send_int16(adc_data[i]);
        usart_send_blocking(USART1, ',');
      }
      usart_send_newline();
      adc_idx = -1;
    }
  }

  return 0;
}
