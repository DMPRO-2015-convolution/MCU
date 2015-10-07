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
	BSP_Init(BSP_INIT_DEFAULT);
	/* If first word of user data page is non-zero, enable eA Profiler trace */
	BSP_TraceProfilerSetup();
	/* Test leds */
	BSP_LedsSet(0x1);
	/* Enable SPI access to MicroSD card */
	BSP_PeripheralAccess(BSP_MICROSD, true);
	//
	//
	//



	// Initialize FatFS and MicroSD
	init_filesystem();

	// Initialize FPGA flash module
	init_fpgaflash();



	// Test components
	test_filesystem();




	while (1) {

	}



}




