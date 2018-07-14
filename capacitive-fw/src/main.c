#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>


static void gpio_setup() {
  gpio_mode_setup(GPIO_PORT_A_BASE, GPIO_MODE_OUTPUT, 
      GPIO_PUPD_NONE, GPIO6|GPIO7|GPIO8|GPIO9|GPIO10|GPIO11);
  gpio_mode_setup(GPIO_PORT_B_BASE, GPIO_MODE_OUTPUT, 
      GPIO_PUPD_NONE, GPIO0|GPIO1);

  gpio_set(GPIO_PORT_B_BASE, GPIO0|GPIO1);
}

static void clock_setup() {
  // use external clock
  rcc_clock_setup_in_hse_8mhz_out_48mhz();
  
	/* Enable GPIOC clock for outputs */
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

	/* Enable clocks for USART2. */
	// rcc_periph_clock_enable(RCC_USART1);
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

int systick_entered = 0;

void sys_tick_handler() {
  gpio_toggle(GPIO_PORT_A_BASE, GPIO6|GPIO7|GPIO8|GPIO9);
  systick_entered++;
}

int main() {
  clock_setup();

  gpio_setup();
  systick_setup();

  while (1) {
  }

  return 0;
}
