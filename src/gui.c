#include "font.h"
#include "button.h"
#include "gui.h"
#include "filesystem.h"
#include <string.h>
#include "ebi.h"
#include "fpgaflash.h"

// Screen size
#define SCREEN_W 640
#define SCREEN_H 480

// Option choices
#define OPTION_COUNT FILE_COUNT
#define OPTION_NAME_LENGTH FILENAME_LENGTH
#define PAD_LENGTH (SCREEN_W - CHAR_H * OPTION_NAME_LENGTH)/2



// Offset of the GUI window
#define GUI_OFFSET_X 100
#define GUI_OFFSET_Y 100
#define GUI_SIZE 1

// Colors
#define BACKGROUND_COLOR {0,0,0}
#define FONT_COLOR {255,255,255}
#define SELECTED_COLOR {0,0,255}


// Main Menu indices
#define MAIN_MENU_KERNEL 0
#define MAIN_MENU_FPGA 1
#define MAIN_MENU_MAP 2
#define MAIN_MENU_REDUCE 3
#define MAIN_MENU_IMAGE_SOURCE 4

#define MAIN_MENU_COUNT 5

//
// Variables
//

// GUI state
gui_state_t currentState;

// The index of the option that is selected
int currentSelection;

// The current available options
char options[OPTION_COUNT][OPTION_NAME_LENGTH];
int optionCount;

// Kernel settings
kernel_t currentKernel;

// Map and reduce settings
uint16_t currentMap;
uint16_t currentReduce;
uint16_t currentImageSource;

// Default settings
kernel_t defaultKernel;
uint16_t defaultMap;
uint16_t defaultReduce;
uint16_t defaultImageSource;


void init_gui() {
	init_font();
	currentState = IDLE;
	currentSelection = 0;
	optionCount = 0;


	// Setup defaults
	load_kernel("kernel/gauss.krn", &defaultKernel);
	load_kernel("kernel/gauss.krn", &currentKernel);

	defaultMap = 0x0;
	currentMap = 0x0;

	currentReduce = 0x0;
	defaultReduce = 0x0;

	defaultImageSource = 0x0;
	currentImageSource = 0x0;

}

void reset_processor() {
	// Send kernel
	ebi_write_buffer(EBI_KERNEL_START, &defaultKernel, sizeof(kernel_t));

	// Send map
	ebi_write(EBI_MAP, defaultMap);

	// Send reduce
	ebi_write(EBI_REDUCE, defaultReduce);

	// Send image source
	ebi_write(EBI_IMAGE_SOURCE, defaultImageSource);
}


void configure_processor() {
	// Send kernel
	ebi_write_buffer(EBI_KERNEL_START, &currentKernel, sizeof(kernel_t));

	// Send map
	ebi_write(EBI_MAP, currentMap);

	// Send reduce
	ebi_write(EBI_REDUCE, currentReduce);

	// Send image source
	ebi_write(EBI_IMAGE_SOURCE, currentImageSource);
}


void exit_gui() {
	currentState = IDLE;
	configure_processor();
}

void display_main_menu() {

	strcpy(options[MAIN_MENU_KERNEL],"Configure Kernel");
	strcpy(options[MAIN_MENU_FPGA],"Configure FPGA");
	strcpy(options[MAIN_MENU_MAP],"Select Map operand");
	strcpy(options[MAIN_MENU_REDUCE],"Select Reduce operand");
	strcpy(options[MAIN_MENU_IMAGE_SOURCE],"Select image source");
	optionCount = MAIN_MENU_COUNT;

	draw_menu();

}

void select_main_menu() {
	switch(currentSelection) {
	case MAIN_MENU_KERNEL:
		display_kernel_menu();
		break;
	default:
		break;
	}
}

void display_kernel_menu() {
	currentState = KERNEL_MENU;
	get_filenames("./kernel", options, &optionCount);
	draw_menu();

}

void select_kernel() {
	char *kernelFilename = options[currentSelection];
	load_kernel(kernelFilename, &currentKernel);
	exit_gui();
}

void display_fpga_menu() {
	currentState = FPGA_MENU;
	get_filenames("./binfile", options, &optionCount);
	draw_menu();
}

void select_fpga() {
	char *binFilename = options[currentSelection];
	exit_gui();

	slave_serial(binFilename);
}


void display_image_source() {
	strcpy(options[0], "MicroSD Card");
	strcpy(options[1], "Camera");
	optionCount = 2;
	draw_menu();
}


void draw_menu() {

	// String pbm buffer
	size_t pbmBufferSize = OPTION_NAME_LENGTH * CHAR_SIZE;
	size_t imageBufferSize = OPTION_NAME_LENGTH * CHAR_SIZE * CHAR_H * GUI_SIZE;

	uint8_t pbmBuffer[OPTION_NAME_LENGTH * CHAR_SIZE];
	color_t imageBuffer[OPTION_NAME_LENGTH * CHAR_SIZE * CHAR_H * GUI_SIZE];

	color_t fontColor = FONT_COLOR;
	color_t backgroundColor = BACKGROUND_COLOR;
	color_t selectedColor = SELECTED_COLOR;

	color_t backColor;

	color_t padBuffer[PAD_LENGTH];
	memset(padBuffer,0,PAD_LENGTH*sizeof(color_t));

	// Go through choices and create image stream
	for (int i=0; i < optionCount; i++) {

		// Set the background color based on selection
		backColor = (currentSelection == i) ? selectedColor : backgroundColor;

		// Reset PBM buffer
		memset(pbmBuffer, 0, pbmBufferSize);
		memset(imageBuffer, 0, imageBufferSize * sizeof(color_t));

		char *option = options[i];

		// Draw font to pbm buffer
		draw_string_to_buffer(option, strlen(option), pbmBuffer, OPTION_NAME_LENGTH);
		// Fill in imagebuffer
		uint8_t byte;
		for (int j=0; j < pbmBufferSize; j++) {
			byte = pbmBuffer[j];
			imageBuffer[CHAR_H*j + 0] = (byte&(1<<7)) ? fontColor : backColor;
			imageBuffer[CHAR_H*j + 1] = (byte&(1<<6)) ? fontColor : backColor;
			imageBuffer[CHAR_H*j + 2] = (byte&(1<<5)) ? fontColor : backColor;
			imageBuffer[CHAR_H*j + 3] = (byte&(1<<4)) ? fontColor : backColor;
			imageBuffer[CHAR_H*j + 4] = (byte&(1<<3)) ? fontColor : backColor;
			imageBuffer[CHAR_H*j + 5] = (byte&(1<<2)) ? fontColor : backColor;
			imageBuffer[CHAR_H*j + 6] = (byte&(1<<1)) ? fontColor : backColor;
			imageBuffer[CHAR_H*j + 7] = (byte&(1<<0)) ? fontColor : backColor;
		}


		// Write image buffer over EBI
		for (int y=0; y < CHAR_H; y++) {

			// Write left padding
			ebi_write_buffer(EBI_IMAGE_STREAM_START, padBuffer, 200*sizeof(color_t)/sizeof(uint16_t));

			// Wrtie image buffer
			ebi_write_buffer(EBI_IMAGE_STREAM_START, imageBuffer, OPTION_NAME_LENGTH*CHAR_H*sizeof(color_t)/sizeof(uint16_t));

			// Write right  padding
			ebi_write_buffer(EBI_IMAGE_STREAM_START, padBuffer, 200*sizeof(color_t)/sizeof(uint16_t));
		}

	}
}

int is_idle() {
	return (currentState == IDLE ||
			currentState == IDLE_KERNEL ||
			currentState == IDLE_MAP ||
			currentState == IDLE_REDUCE ||
			currentState == IDLE_IMAGE);
}

int is_submenu() {
	return (currentState == KERNEL_MENU ||
			currentState == FPGA_MENU ||
			currentState == MAP_MENU ||
			currentState == REDUCE_MENU ||
			currentState == IMAGE_SOURCE_MENU ||
			currentState == IMAGE_MENU);
}


void on_button_pressed(button_t button) {
	switch (button) {
	case BTN_UP:
		currentSelection--;
		currentSelection = currentSelection % optionCount;
		draw_menu();
		break;
	case BTN_DOWN:
		currentSelection++;
		currentSelection = currentSelection % optionCount;
		draw_menu();
		break;
	case BTN_OK:
		if (is_idle()) {
			reset_processor();
			currentState = MAIN_MENU;
			display_main_menu();
		} else {
			switch(currentState) {
			case MAIN_MENU:
				select_main_menu();
				break;
			case KERNEL_MENU:
				select_kernel();
				break;
			default:
				break;
			}
		}
		break;

	case BTN_BACK:
		break;

	}


}
