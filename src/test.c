#include "filesystem.h"
#include "bsp.h"
#include "fpgaflash.h"

#define BYTES_TO_READ 1024*64


extern void test_filesystem() {

	// Init LEDs
	BSP_LedsSet(0x0);

	FIL file;
	uint8_t buffer[BYTES_TO_READ];
	UINT bytesRead;

	open_file(&file, "tutorial.bit");

	read_file(&file, buffer, BYTES_TO_READ, &bytesRead);


	/*
	// TEST, write bytes to leds
	int i;
	int j;
	int x;
	int k = 1000000;
	for (i = 0; i < bytesRead; i++) {
		BSP_LedsSet(buffer[i]);

		//Delay
		for (j = 0; j<k; j++) x++;
	}*/


	// TEST, read whole file
	seek_file(&file,0);
	while (1) {
		read_file(&file, buffer, BYTES_TO_READ, &bytesRead);
		if (bytesRead == 0) break;
	}
	BSP_LedsSet(0x2);


	close_file(&file);


}


extern void test_slaveserial() {

	Start_SlaveSerial();

}

extern void test_ebi() {
	int i = 0;
	ebi_write(0,0b1010);
	//int x = 0;
	while (i < 14) {
		ebi_write(0, i);

//		for (int j = 0; j < 1000000; j++) {
//			x++;
//		}
		i++;
	}
	while (1);
}



