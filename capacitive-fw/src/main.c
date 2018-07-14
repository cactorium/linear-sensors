#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>


static void gpio_setup() {
}

static void clock_setup() {
  // use external clock
  rcc_clock_setup_in_hse_8mhz_out_48mhz();
  
	/* Enable GPIOC clock for LED & USARTs. */
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Enable clocks for USART2. */
	rcc_periph_clock_enable(RCC_USART1);
}

static void systick_setup() {
  // disable counter and interrupt
  systick_interrupt_disable();
  systick_counter_disable();

  systick_set_clocksource(STK_CSR_CLKSOURCE);
  systick_set_reload(48000000/4000-1);
  systick_clear();

  systick_interrupt_enable();
  systick_counter_enable();
}

int main() {
  gpio_setup();
  clock_setup();
  systick_setup();

  while (1) {
  }

  return 0;
}
