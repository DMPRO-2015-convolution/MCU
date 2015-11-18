#include "em_gpio.h"
#include "em_cmu.h"
#include "button.h"
#include "gui.h"

void interrupt_handler();

void init_buttons() {
	/* Enable clock for GPIO module */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Configure PD as input with filter enable */
	GPIO_PinModeSet(gpioPortD, 5, gpioModeInputPullFilter, 1);
	GPIO_PinModeSet(gpioPortD, 6, gpioModeInputPullFilter, 1);
	GPIO_PinModeSet(gpioPortD, 7, gpioModeInputPullFilter, 1);
	GPIO_PinModeSet(gpioPortD, 8, gpioModeInputPullFilter, 1);

	/* Enable GPIO_ODD interrupt vector in NVIC */
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

	// Configure interrupt on falling edge
	GPIO_IntConfig(gpioPortD, 5, false, true, true);
	GPIO_IntConfig(gpioPortD, 6, false, true, true);
	GPIO_IntConfig(gpioPortD, 7, false, true, true);
	GPIO_IntConfig(gpioPortD, 8, false, true, true);
}

void GPIO_ODD_IRQHandler(void) {
  /* clear flag for PE1 interrupt */
  GPIO_IntClear(0xffff);
  interrupt_handler();
}

void GPIO_EVEN_IRQHandler(void) {
  /* clear flag for PE1 interrupt */
  GPIO_IntClear(0xffff);
  interrupt_handler();
}

void interrupt_handler() {
	if (GPIO_PinInGet(gpioPortD, 5) == 0) {
		on_button_pressed(BTN_UP);
	}
	else if (GPIO_PinInGet(gpioPortD, 6) == 0) {
		on_button_pressed(BTN_DOWN);
	}
	else if (GPIO_PinInGet(gpioPortD, 7) == 0) {
		on_button_pressed(BTN_BACK);
	}
	else if (GPIO_PinInGet(gpioPortD, 8) == 0) {
		on_button_pressed(BTN_OK);
	}
}
