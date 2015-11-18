#include "fpgaflash.h"
#include "filesystem.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#define BUFFER_SIZE 1024*32
#define BYTES_TO_READ BUFFER_SIZE


const int clkPort = gpioPortD;
const int clkPin = 2;
const int dinPort = gpioPortD;
const int dinPin = 0;


extern void init_fpgaflash() {

	/* Enable clock for GPIO module */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Configure PD0-2 as push pull output */
	GPIO_PinModeSet(clkPort, clkPin, gpioModePushPull, 0); //CLK
	GPIO_PinModeSet(dinPort, dinPin, gpioModePushPull, 0); //DIN

	GPIO_PinModeSet(gpioPortB, 12, gpioModeInputPullFilter, 1); // DONE
	GPIO_PinModeSet(gpioPortB, 11, gpioModePushPull, 0); // Program B
	GPIO_PinModeSet(gpioPortB, 8, gpioModeInputPullFilter, 1); // INIT_B

	// Enable FPGA Oscillator
	GPIO_PinModeSet(gpioPortF, 12, gpioModePushPull, 0); // Program B
	GPIO_PinOutSet(gpioPortF, 12);


	/* Enabling clock to USART 0 */
	CMU_ClockEnable(FPGA_CMUCLOCK, true);
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Initialize USART in SPI master mode. */
	USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;
	init.baudrate = FPGA_HI_SPI_FREQ;
	init.msbf     = true;
	USART_InitSync(FPGA_USART, &init);

	/* Enabling pins and setting location, SPI CS not enable */
	FPGA_USART->ROUTE = USART_ROUTE_TXPEN | USART_ROUTE_RXPEN |
	                         USART_ROUTE_CLKPEN | FPGA_LOC;

	  /* IO configuration */
	GPIO_PinModeSet(FPGA_GPIOPORT, FPGA_MOSIPIN, gpioModePushPull, 0);  /* MOSI */
	GPIO_PinModeSet(FPGA_GPIOPORT, FPGA_MISOPIN, gpioModeInputPull, 1); /* MISO */
	GPIO_PinModeSet(FPGA_GPIOPORT, FPGA_CSPIN,   gpioModePushPull, 1);  /* CS */
	GPIO_PinModeSet(FPGA_GPIOPORT, FPGA_CLKPIN,  gpioModePushPull, 0);  /* CLK */


}



extern void slave_serial(char *binFilename) {
	FIL file;
	UINT bytesRead;
	uint16_t buffer[BUFFER_SIZE/2];


	open_file(&file, binFilename);

	int init_b = 0;
    int i = 0;
    uint8_t byte;


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

	/* Clear send and receive buffers. */
	FPGA_USART->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;


	while (1) {
		read_file(&file, buffer, BYTES_TO_READ, &bytesRead);
		if (bytesRead == 0) break;
		i++;

		// Go through all bytes in the buffer
		for (int j=0; j<bytesRead/2; j++) {

			//byte = buffer[j];

			while (!(FPGA_USART->STATUS & USART_STATUS_TXBL));
			FPGA_USART->TXDOUBLE = (uint32_t) buffer[j];
		}
	}


    GPIO->P[gpioPortD].DOUTCLR = 0xffff;


    // Set data to 1
    GPIO_PinOutSet(dinPort, dinPin);

    // Add extra clock cycles until done and init is high
    int done = 0;


    init_b = GPIO_PinInGet(gpioPortB, 8);

    while(done == 0 && init_b == 1) {
    	GPIO_PinOutClear(clkPort, clkPin);
    	done = GPIO_PinInGet(gpioPortB,12);
    	init_b = GPIO_PinInGet(gpioPortB, 8);
    	GPIO_PinOutSet(clkPort, clkPin);
    }

    // Add extra clock cycles
    for (i=0; i<8; i++) {
    	GPIO_PinOutClear(clkPort, clkPin);
    	GPIO_PinOutSet(clkPort, clkPin);
    }

    // Close file
    close_file(&file);

}
