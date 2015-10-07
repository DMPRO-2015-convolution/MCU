#include "fpgaflash.h"
#include "filesystem.h"
#include "em_gpio.h"


#define BUFFER_SIZE 1024


extern void init_fpgaflash() {

	/* Enable clock for GPIO module */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Configure PD with alternate drive strength of 0.5mA */
	GPIO_DriveModeSet(gpioPortD, gpioDriveModeLowest);

	/* Configure PD0-2 as push pull output */
	GPIO_PinModeSet(gpioPortD, 0, gpioModePushPull, 0); //DIN
	GPIO_PinModeSet(gpioPortD, 1, gpioModePushPull, 0); //PROGRAM
	GPIO_PinModeSet(gpioPortD, 2, gpioModePushPull, 0); //CLK

	/* Configure PD3-4 as input with filter*/
	GPIO_PinModeSet(gpioPortD, 3, gpioModeInput, 0); //INIT
	GPIO_PinModeSet(gpioPortD, 4, gpioModeInput, 0); //DONE

}

 //CPLD Register Addresses:

 //WordPtr CPLD_Config_Reg        = 0x29000000;
 //WordPtr CPLD_Program_Reg       = 0x29000002;
 //WordPtr CPLD_Input_Reg         = 0x29000004;


 //Program Register:

 //int CS_Bit     = 0x0004;
 //int Write_Bit      = 0x0002;
 //int Prog_Bit       = 0x0001;

// Filesystem for loading bitfile
FIL file;
UINT bytesRead;
uint16_t buffer[BUFFER_SIZE];


void Start_SlaveSerial( ) {

    open_file(&file, "tutorial.bit");

    while (1) {
    	read_file(&file, buffer, BUFFER_SIZE, &bytesRead);
    	if (bytesRead == 0) break;
    	SlaveSerial(buffer);
    }

    //----------------------------------------------------------------------
    // SlaveSerial()
    //----------------------------------------------------------------------

    //SlaveSerial(flash_start_addr, flash_end_addr);


    //----------------------------------------------------------------------
    // Monitor the DONE bit in the CPLD Input Register to see if
    // configuration successful
    //----------------------------------------------------------------------

    Check_DONE_Bit();

}


void SlaveSerial(uint16_t buffer) {
	uint16_t Data16;


    //----------------------------------------------------------------------
    //Toggle Program Pin by Toggling Program_OE bit
    //This is accomplished by writing to the Program Register in the CPLD
    //
    //NOTE: The Program_OE bit should be driven high to bring the Virtex
    //      Program Pin low. Likewise, it should be driven low
    //      to bring the Virtex Program Pin to High-Z
    //----------------------------------------------------------------------

    //IOWrite(CPLD_Program_Reg, Prog_Bit); //PROGRAM_OE LOW
    GPIO_PinOutSet(gpioPortD, 1);


    //----------------------------------------------------------------------
    //Bring Program High-Z
    //(Drive Program_OE bit low to bring Virtex Program Pin to High-Z
    //----------------------------------------------------------------------

    //Program_OE bit Low brings the Virtex Program Pin to High Z:
    //IOWrite(CPLD_Program_Reg, 0x0000);
    GPIO_PinOutClear(gpioPortD, 1);


    //----------------------------------------------------------------------
    //Check for /INIT after Program is High Z:
    //----------------------------------------------------------------------


    Data16 = 0;  //Initialize Data16 variable before entering While Loop

    while(Data16 == 0) {
        //Data16 = IORead(CPLD_Input_Reg);    //Read Input Register
        Data16 = GPIO_PinInGet(gpioPortD, 3); //Read INIT
        Data16 = Data16 & 0x0001;           //Check Status of /INIT
    }


    //----------------------------------------------------------------------
    //Begin Slave-Serial Configuration
    //----------------------------------------------------------------------

    int i;
    for (i = 0; i < bytesRead; i++) {
    	Data16 = buffer[i];
    	ShiftDataOut(Data16);
    }

}


void ShiftDataOut( Data16 ) {

	uint8_t DataOut;
    //Word SCLK_LOW;
    //Word SCLK_HIGH;

    //SCLK_LOW  = 0x0000;
    //SCLK_HIGH = 0x0002;

/*
	DIN PD0
	PROGRAM PD1
	CLK PD2
	INIT PD3
    DONE PD4?
*/

    //Upper Byte:

    DataOut = (Data16 & 0x0100) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //1st bit
    if (DataOut == 1) {
    	GPIO_PinOutSet(gpioPortD, 0); //1st bit
    }
    GPIO_PinOutClear(gpioPortD, 2); //CLK low
    GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0200) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //2nd bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //2nd bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0400) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //3rd bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //3rd bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0800) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //4th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //4th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x1000) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //5th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //5th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x2000) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //6th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //6th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x4000) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //7th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //7th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x8000) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //8th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //8th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


// --  Lower Byte:

    DataOut = (Data16 & 0x0001) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //9th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //9th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0002) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //10th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //10th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0004) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //11th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //11th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0008) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //12th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //12th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0010) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //13th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //13th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0020) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //14th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //14th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0040) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //15th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //15th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high


    DataOut = (Data16 & 0x0080) ? 1 : 0;
    GPIO_PinOutClear(gpioPortD, 0); //16th bit
	if (DataOut == 1) {
		GPIO_PinOutSet(gpioPortD, 0); //16th bit
	}
	GPIO_PinOutClear(gpioPortD, 2); //CLK low
	GPIO_PinOutSet(gpioPortD, 2); //CLK high

}


void Check_DONE_Bit(void) {

	uint16_t Data16;
    uint8_t Done;
    uint8_t Init;
    uint8_t ExtraCclk;

    Done = 0;
    Init = 1;

    while ( (Done==0) && (Init==1) ) {

    	//Apply additional CCLK pulse until DONE=1
        //IOWrite(CPLD_Config_Reg, 0x0001 );  //CCLK=0, DATA=1
        //IOWrite(CPLD_Config_Reg, 0x0003 );  //CCLK=1, DATA=1
    	GPIO_PinOutClear(gpioPortD, 0); //Clear DIN, for safety
        GPIO_PinOutSet(gpioPortD, 0); //DATA = 1
        GPIO_PinOutClear(gpioPortD, 2); //CLK = 0
        GPIO_PinOutSet(gpioPortD, 2); //CLK = 1

        //Read CPLD Input Register:
        //Data16 = IORead(CPLD_Input_Reg);

        //Check the DONE bit of the CPLD Input Register:
        //Done = (Data16 & 0x0002) ? 1 : 0;
        Done = GPIO_PinInGet(gpioPortD, 4);

        //Check the INIT bit of the CPLD Input Register
        //Init = (Data16 & 0x0001) ? 1 : 0;
        Init = GPIO_PinInGet(gpioPortD, 3);
        //Note: FPGA user design should drive INIT High or make INIT HIGHZ
        //      to ensure no false INIT error detected by this code.

    }

    if (Done == 1) {                     //If DONE Pin is High, display message
        for (ExtraCclk = 0; ExtraCclk < 8; ExtraCclk++) {
            //Apply additional CCLK pulse to ensure end-of-startup
            //IOWrite(CPLD_Config_Reg, 0x0001 );  //CCLK=0, DATA=1
            //IOWrite(CPLD_Config_Reg, 0x0003 );  //CCLK=1, DATA=1
        	GPIO_PinOutClear(gpioPortD, 0); //Clear DIN, for safety
            GPIO_PinOutSet(gpioPortD, 0); //DATA = 1
			GPIO_PinOutClear(gpioPortD, 2); //CLK = 0
			GPIO_PinOutSet(gpioPortD, 2); //CLK = 1
            //Note:  FPGA user design should keep CCLK and DATA HIGHZ to avoid
            //       conflict with this code.
        }
        //FrmAlert (resAlertIDSuccess);   //"Successful! DONE is High!"
    }
    else {//Done==0 and Init==0
        //FrmAlert (resAlertIDFailed_and_InitLow);    //"Configuration Failed", DONE is Low, Init is Low"
    }
}
