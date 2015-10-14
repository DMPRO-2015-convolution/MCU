/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"


#include "bsp.h"
#include "bsp_trace.h"


#include "filesystem.h"
#include "fpgaflash.h"

#include "test.h"

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{

	/* Use 32MHZ HFXO as core clock frequency */
	//CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);

	//
	// TODO Temp for testing on BSP, separate init for mcu needed
	//
	/* Initialize DK board register access */
	//BSP_Init(BSP_INIT_DEFAULT);
	/* If first word of user data page is non-zero, enable eA Profiler trace */
	//BSP_TraceProfilerSetup();
	/* Test leds */
	//BSP_LedsSet(0x1);
	/* Enable SPI access to MicroSD card */
	//BSP_PeripheralAccess(BSP_MICROSD, true);
	//
	//
	//



	// Initialize FatFS and MicroSD
	//init_filesystem();

	// Initialize FPGA flash module
	//init_fpgaflash();

	//Initialize buttons and their interrupts
	//init_buttons();


	// Test components
	//test_filesystem();
	//test_slaveserial();

	//Test EBI
	init_ebi();
	test_ebi();


	while (1) {
		//EMU_EnterEM2();
	}



}

void GPIO_ODD_IRQHandler(void) {
  /* clear flag for PE1 interrupt */
  GPIO_IntClear(0xff);
  interrupt_handler();
}

void GPIO_EVEN_IRQHandler(void) {
  /* clear flag for PE1 interrupt */
  GPIO_IntClear(0xff);
  interrupt_handler();
}

void interrupt_handler() {

	if (GPIO_PinInGet(gpioPortD, 5)) {
		//Switch between SD and camera
	}
	else if (GPIO_PinInGet(gpioPortD, 6)) {
		//Change kernel
	}
	else if (GPIO_PinInGet(gpioPortD, 7)) {
		//Flash FPGA
	}
	else if (GPIO_PinInGet(gpioPortD, 8)) {
		//Mystery function
	}
}

void init_buttons() {
	/* Enable clock for GPIO module */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Configure PE1 as input with filter enable */
	GPIO_PinModeSet(gpioPortD, 5, gpioModeInputPullFilter, 1);
	GPIO_PinModeSet(gpioPortD, 6, gpioModeInputPullFilter, 1);
	GPIO_PinModeSet(gpioPortD, 7, gpioModeInputPullFilter, 1);
	GPIO_PinModeSet(gpioPortD, 8, gpioModeInputPullFilter, 1);

	/* Enable GPIO_ODD interrupt vector in NVIC */
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

	/* Configure PE1 interrupt on falling edge */
	GPIO_IntConfig(gpioPortD, 5, false, true, true);
	GPIO_IntConfig(gpioPortD, 6, false, true, true);
	GPIO_IntConfig(gpioPortD, 7, false, true, true);
	GPIO_IntConfig(gpioPortD, 8, false, true, true);
}
