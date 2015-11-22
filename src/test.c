#include "filesystem.h"
#include "bsp.h"
#include "fpgaflash.h"
#include "mcu.h"
#include "gui.h"

#define BYTES_TO_READ 1024*64
#define BANK0_BASE_ADDR 0x80000000
#define BANK1_BASE_ADDR 0x84000000

#define NUM_WRITES 512
#define NUM_READS 512
#define WRITE_START 0
#define READ_START 0

extern void test_filesystem() {

	// Init LEDs
	BSP_LedsSet(0x0);

	FIL file;
	uint8_t buffer[BYTES_TO_READ];
	UINT bytesRead;

	open_file(&file, "tutorial.bit");

	read_file(&file, buffer, BYTES_TO_READ, &bytesRead);


	// TEST, read whole file
	seek_file(&file,0);
	while (1) {
		read_file(&file, buffer, BYTES_TO_READ, &bytesRead);
		if (bytesRead == 0) break;
	}
	BSP_LedsSet(0x2);


	close_file(&file);


}

extern void test_read_bmp() {
	// Init LEDs
	BSP_LedsSet(0x0);

	FIL file;
	uint8_t buffer[BYTES_TO_READ];
	UINT bytesRead;
	BMP_HEADER* bmp_header;
	BMP_INFO_HEADER* info_header;

	// Open file
	open_file(&file, "test.bmp");


	// Read bmp header
	read_file(&file, bmp_header, 14, &bytesRead);
	BSP_LedsSet(0x1);

	// Read info header
	read_file(&file, info_header, 40, &bytesRead);
	BSP_LedsSet(0x2);

	// Read image data
	seek_file(&file,bmp_header->image_data_offset);

	while (1) {
		read_file(&file, buffer, BYTES_TO_READ, &bytesRead);
		if (bytesRead == 0) break;
	}
	BSP_LedsSet(0x3);
}



extern void test_ebi() {

	uint16_t i = 0;

	int values[NUM_WRITES] = {0};


	// Write data
	for (i=0; i<NUM_WRITES; i++) {
		ebi_write(i,i<<6);
	}

	// Success
	//BSP_LedsSet(0x1);


	uint16_t data;
	// Read data
	for (i=0; i<NUM_WRITES; i++) {
		//Delay(10);
		data = ebi_read(i);
		//data = *(volatile uint16_t*)(BANK1_BASE_ADDR);
		values[i] = data;
		if (data != i) {
			// Failure
			//BSP_LedsSet(0xff);
		}
	}

	// Read data
	//data = *(volatile uint16_t*)(BANK1_BASE_ADDR);



	while (1);
}

extern void test_ebi_buffer() {

	color_t pixelBuffer[3] = {0};
	for (int i=0; i<3; i++) {
		for (int j=0; j < 3; j++) {
			pixelBuffer[j].r = i+j;
			pixelBuffer[j].g = i+j+1;
			pixelBuffer[j].b = i+j+2;
		}
		ebi_buffer_write(i*3*sizeof(color_t), pixelBuffer, 3*sizeof(color_t));
	}

	color_t outBuffer[3];
	uint16_t values[3*3];

	for (int i=0; i<3*3*sizeof(color_t); i++) {
		values[i] = ebi_read(i);
	}

	while(1);

}


extern void test_ebi_read() {

	int values[NUM_READS] = {0};


	// Testing ebi read with SRAM
	for (long i=0; i<NUM_READS; i++) {
		values[i] = ebi_read(i);
	}

	while(1);

}





extern void test_read_paths() {

}


extern void test_image_to_ebi() {
	// Init LEDs
	BSP_LedsSet(0x0);

	FIL file;
	uint8_t buffer[BYTES_TO_READ];
	UINT bytesRead;

	open_file(&file, "tutorial.bit");


	seek_file(&file,0);
	while (1) {
		read_file(&file, buffer, BYTES_TO_READ, &bytesRead);
		if (bytesRead == 0) break;

		// Write image data over ebi

	}


	close_file(&file);


}




void test_sram() {

	uint16_t values[NUM_READS] = {0};

	//while(1);

	// Write data
	//for (int i=WRITE_START; i<WRITE_START+NUM_WRITES; i++) {
	//	sram_write(i,i);
	//}

	while(1) {
		// Write data
		//for (int i=WRITE_START; i<WRITE_START+NUM_WRITES; i++) {
		//	sram_write(i,i);
		//}

		// Read data
		for (int i=READ_START; i<READ_START+NUM_READS; i++) {
			values[i] = sram_read(i);
		}
		while(1);

	}

	// Breakpoint
	while(1);
}



