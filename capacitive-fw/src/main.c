#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>

#define PHASE_PIN(x) ((uint32_t[]){GPIO6, GPIO8, GPIO7, GPIO9, GPIO0, GPIO10, GPIO1, GPIO11})[x]
#define IS_PORT_B(x) ((uint8_t[]){0, 0, 0, 0, 1, 0, 1, 0})[x]
#define PHASE_PORT(x) (IS_PORT_B(x) ? GPIO_PORT_B_BASE : GPIO_PORT_A_BASE)

#define PINA_MASK(x) (IS_PORT_B(x) ? 0 : PHASE_PIN(x))
#define PINB_MASK(x) (IS_PORT_B(x) ? PHASE_PIN(x) : 0)

#define TX_PIN GPIO6 // port B
#define RX_PIN GPIO7 // port B

static void gpio_setup() {
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
}

static void clock_setup() {
  // use external clock
  rcc_clock_setup_in_hse_8mhz_out_48mhz();

	// enable clocks for GPIO
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

	// enable clocks for USART1
	rcc_periph_clock_enable(RCC_USART1);
}

static void systick_setup() {
  // disable counter and interrupt
  systick_interrupt_disable();
  systick_counter_disable();

  systick_set_clocksource(STK_CSR_CLKSOURCE);
  systick_set_reload(48000000/8000-1);
  systick_clear();

  systick_interrupt_enable();
  systick_counter_enable();
}

static void uart_setup() {
	usart_set_baudrate(USART1, 115200);
	usart_set_databits(USART1, 8);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_stopbits(USART1, USART_CR2_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

	usart_enable(USART1);
}

int tick = 0;
void sys_tick_handler() {
  switch (tick) {
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

  tick = (tick + 1) & 0x03;
}

int main() {
  clock_setup();

  gpio_setup();
  uart_setup();
  systick_setup();

  while (1) {
    uint16_t c = usart_recv_blocking(USART1);
    if (c >= 'A' && c <= 'Z') {
      c += 'a' - 'A';
    }
    usart_send(USART1, c);
  }

  return 0;
}
