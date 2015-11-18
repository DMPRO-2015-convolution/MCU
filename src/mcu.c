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

#include "gui.h"

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

	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);


#ifdef DEVKIT
	/* Initialize DK board register access */
	BSP_Init(BSP_INIT_DK_SPI);
	BSP_PeripheralAccess(BSP_MICROSD, true);
#endif


	// Initialize FatFS and MicroSD
	init_filesystem();

	// Initialize EBI bus
	init_ebi();

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


	// Initialize GUI
	init_gui();
	Start_SlaveSerial();


	int numFiles = 0;
	char strings[FILE_COUNT][FILENAME_LENGTH];
	get_filenames("./kernel",strings, &numFiles);

	while (1) {
		//EMU_EnterEM2();
	}

}

