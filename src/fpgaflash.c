#include "fpgaflash.h"
#include "filesystem.h"
#include "em_gpio.h"
#include "em_cmu.h"

#define BUFFER_SIZE 1024*8
#define BYTES_TO_READ BUFFER_SIZE

void Start_SlaveSerial();

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

}


// Filesystem for loading bitfile
FIL file;
UINT bytesRead;
uint8_t buffer[BUFFER_SIZE];


extern void Start_SlaveSerial( ) {


	// TODO input file from argument
	open_file(&file, "binfile/default.bin");

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

    while (1) {
    	read_file(&file, buffer, BYTES_TO_READ, &bytesRead);
    	if (bytesRead == 0) break;
    	i++;

    	// Go through all bytes in the buffer
    	for (int j=0; j<bytesRead; j++) {
    		// Clear clk and data
    		byte = buffer[j];

    		// Optimize for sparse files. Set data bit once and clock 8 times
    		if (byte == 0x0) {
    			GPIO->P[gpioPortD].DOUTCLR = 0xffff;
    			GPIO->P[gpioPortD].DOUTSET = 0x0;

    			// 7
    			GPIO->P[gpioPortD].DOUTSET = 0x4;
    			GPIO->P[gpioPortD].DOUTCLR = 0xffff;

    			// 6
    			GPIO->P[gpioPortD].DOUTSET = 0x4;
    			GPIO->P[gpioPortD].DOUTCLR = 0xffff;

    			// 5
    			GPIO->P[gpioPortD].DOUTSET = 0x4;
    			GPIO->P[gpioPortD].DOUTCLR = 0xffff;

    			// 4
    			GPIO->P[gpioPortD].DOUTSET = 0x4;
    			GPIO->P[gpioPortD].DOUTCLR = 0xffff;

    			// 3
    			GPIO->P[gpioPortD].DOUTSET = 0x4;
    			GPIO->P[gpioPortD].DOUTCLR = 0xffff;

    			// 2
    			GPIO->P[gpioPortD].DOUTSET = 0x4;
    			GPIO->P[gpioPortD].DOUTCLR = 0xffff;

    			// 1
    			GPIO->P[gpioPortD].DOUTSET = 0x4;
    			GPIO->P[gpioPortD].DOUTCLR = 0xffff;

    			// 0
    			GPIO->P[gpioPortD].DOUTSET = 0x4;

    		} else {
				// Send out bit 7
				GPIO->P[gpioPortD].DOUTCLR = 0xffff;
				GPIO->P[gpioPortD].DOUTSET = (byte>>7)&1;
				GPIO->P[gpioPortD].DOUTSET = 0x4;

				GPIO->P[gpioPortD].DOUTCLR = 0xffff;
				GPIO->P[gpioPortD].DOUTSET = (byte>>6)&1;
				GPIO->P[gpioPortD].DOUTSET = 0x4;

				GPIO->P[gpioPortD].DOUTCLR = 0xffff;
				GPIO->P[gpioPortD].DOUTSET = (byte>>5)&1;
				GPIO->P[gpioPortD].DOUTSET = 0x4;

				GPIO->P[gpioPortD].DOUTCLR = 0xffff;
				GPIO->P[gpioPortD].DOUTSET = (byte>>4)&1;
				GPIO->P[gpioPortD].DOUTSET = 0x4;

				GPIO->P[gpioPortD].DOUTCLR = 0xffff;
				GPIO->P[gpioPortD].DOUTSET = (byte>>3)&1;
				GPIO->P[gpioPortD].DOUTSET = 0x4;

				GPIO->P[gpioPortD].DOUTCLR = 0xffff;
				GPIO->P[gpioPortD].DOUTSET = (byte>>2)&1;
				GPIO->P[gpioPortD].DOUTSET = 0x4;

				GPIO->P[gpioPortD].DOUTCLR = 0xffff;
				GPIO->P[gpioPortD].DOUTSET = (byte>>1)&1;
				GPIO->P[gpioPortD].DOUTSET = 0x4;

				GPIO->P[gpioPortD].DOUTCLR = 0xffff;
				GPIO->P[gpioPortD].DOUTSET = (byte>>0)&1;
				GPIO->P[gpioPortD].DOUTSET = 0x4;
    		}
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
