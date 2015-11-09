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

#include "mcu.h"

#include "bsp.h"
#include "bsp_trace.h"


#include "filesystem.h"
#include "fpgaflash.h"

#include "test.h"
#include "ebi.h"

uint32_t msTicks;


void SysTick_Handler(void)
{
  /* Increment counter necessary in Delay()*/
  msTicks++;
}

void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}



/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{

	/* Use 32MHZ HFRCO as core clock frequency */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);

	//
	// TODO Temp for testing on BSP, separate init for mcu needed
	//

	/* Initialize DK board register access */
#ifdef DEVKIT
	BSP_Init(BSP_INIT_DK_SPI);
	BSP_PeripheralAccess(BSP_MICROSD, true);
#endif
	/* If first word of user data page is non-zero, enable eA Profiler trace */
	//BSP_TraceProfilerSetup();
	/* Test leds */
	//BSP_LedsSet(0x1);
	/* Enable SPI access to MicroSD card */
	//
	//
	//


	//BSP_LedsSet(0xff);

	// Initialize FatFS and MicroSD
	init_filesystem();

	//BSP_LedsSet(0xff);
	// Initialize EBI bus
	//init_ebi();


	//Initialize buttons and their interrupts
	init_buttons();

	// Initialize FPGA flash module
	init_fpgaflash();

	/* Setup SysTick Timer for 10 msec interrupts  */
	/*if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000))
	{
		while (1) ;
	}
	*/


	//BSP_LedsSet(0xff);
/*
	// Testing Output
	GPIO_PinModeSet( gpioPortA, 0, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 1, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 2, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 3, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 4, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 5, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 6, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 7, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 8, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 9, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 10, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 11, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 12, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 13, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 14, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 15, gpioModePushPull, 0 );


	int i = 0;
	for (i=0; i < 16; i++) {
		GPIO_PinOutClear(gpioPortA, i);
	}
	GPIO_PinOutSet(gpioPortA, 10); //2nd bit

	GPIO_PinModeSet( gpioPortA, 14, gpioModePushPull, 0 );
	GPIO_PinModeSet( gpioPortA, 15, gpioModePushPull, 0 );

	GPIO_PinModeSet(gpioPortB, 12, gpioModeInputPullFilter, 1); // DONE
	GPIO_PinModeSet(gpioPortB, 11, gpioModePushPull, 0); // Program B
	GPIO_PinModeSet(gpioPortB, 8, gpioModeInputPullFilter, 1); // INIT_B



	int init_b = 0;
	int program_b = 0;
	program_b = GPIO_PinInGet(gpioPortB, 11);

	//while(1);

	// Set program_b high until init_b is high
	GPIO_PinOutSet(gpioPortB, 11);
	while(init_b == 0) {
		init_b = GPIO_PinInGet(gpioPortB, 8);
	}

	// Set program_b to low until init_b is low
	GPIO_PinOutClear(gpioPortB, 11);
	while (!(init_b == 0)) {
		init_b = GPIO_PinInGet(gpioPortB, 8);
	}

	// Set program_b back to high and wait for init_b is high
	GPIO_PinOutSet(gpioPortB, 11);
	while(init_b == 0) {
		init_b = GPIO_PinInGet(gpioPortB, 8);
	}

	int numFiles = 0;
	char strings[FILE_COUNT][FILENAME_LENGTH];
	get_filenames("./binfile",strings, &numFiles);


	Start_SlaveSerial();
*/
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

	if (GPIO_PinInGet(gpioPortD, 5) == 0) {
		//Switch between SD and camera
	}
	else if (GPIO_PinInGet(gpioPortD, 6) == 0) {
		//Change kernel
	}
	else if (GPIO_PinInGet(gpioPortD, 7) == 0) {
		//Flash FPGA
	}
	else if (GPIO_PinInGet(gpioPortD, 8) == 0) {
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
