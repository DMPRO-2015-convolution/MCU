#include "font.h"
#include "button.h"
#include "gui.h"
#include "filesystem.h"
#include <string.h>
#include "ebi.h"
#include "fpgaflash.h"
#include "image.h"

// Screen size
#define SCREEN_W 640
#define SCREEN_H 480


// Offset of the GUI window
#define GUI_OFFSET_X 100
#define GUI_OFFSET_Y 100
#define GUI_SIZE 1

// Option choices
#define OPTION_COUNT FILE_COUNT
#define OPTION_NAME_LENGTH FILENAME_LENGTH
#define PAD_LENGTH (SCREEN_W - CHAR_H * OPTION_NAME_LENGTH * GUI_SIZE)/2




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
#define MAIN_MENU_IMAGE 5

#define MAIN_MENU_COUNT 5


#define IMAGE_SOURCE_SD 0
#define IMAGE_SOURCE_CAM 1
#define IMAGE_SOURCE_COUNT 2



// Function prototypes
void display_main_menu();
void display_kernel_menu();
void display_fpga_menu();
void display_map_menu();
void display_reduce_menu();
void display_image_source_menu();
void display_image_menu();
void select_main_menu();
void select_kernel();
void select_fpga();
void select_map();
void select_reduce();
void select_image_source();
void select_image();
void draw_menu();



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
uint8_t currentMap;
uint8_t currentReduce;
uint16_t currentImageSource;
char currentImage[OPTION_NAME_LENGTH];

// Default settings
kernel_t defaultKernel;
uint8_t defaultMap;
uint8_t defaultReduce;
uint16_t defaultImageSource;
char defaultImage[OPTION_NAME_LENGTH];


void init_gui() {
	init_font();
	currentState = IDLE;
	currentSelection = 0;
	optionCount = 0;


	// Setup defaults
	load_kernel("kernel/gauss.krn", &defaultKernel);
	load_kernel("kernel/gauss.krn", &currentKernel);

	defaultMap = MAP_MUL;
	currentMap = MAP_MUL;

	currentReduce = REDUCE_ADD;
	defaultReduce = REDUCE_ADD;

	defaultImageSource = 0x0;
	currentImageSource = 0x0;

	strcpy(defaultImage, "image/default.ppm");
	strcpy(currentImage, "image/default.ppm");

}


void configure_processor() {
	ebi_reset_processor();
	ebi_configure_map_reduce(currentMap, currentReduce);
	ebi_configure_kernel(currentKernel);
}


void exit_gui() {
	currentState = IDLE;

	ebi_set_ebi_mode(EBI_MODE_OFF);

	configure_processor();

	// Start sending image
	//if (currentImageSource == IMAGE_SOURCE_SD) {
	//	image_send_start(currentImage);
	//}
}

void display_main_menu() {



	// Stop image stream and wait until image is sent
	image_send_stop();
	while(image_get_state() != IMAGE_IDLE);


	currentState = MAIN_MENU;

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
	case MAIN_MENU_FPGA:
		display_fpga_menu();
		break;
	case MAIN_MENU_MAP:
		display_map_menu();
		break;
	case MAIN_MENU_REDUCE:
		display_reduce_menu();
		break;
	case MAIN_MENU_IMAGE_SOURCE:
		display_image_source_menu();
		break;
	case MAIN_MENU_IMAGE:
		display_image_menu();
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


void display_map_menu() {
	currentState = MAP_MENU;
	//options[MAP_MUL] = "Multiply";
	//options[MAP_ADD] = "Addition";
	//options[MAP_MASK] = "Mask";
	optionCount = 3;
	draw_menu();
}

void select_map() {
	currentMap = currentSelection;
	exit_gui();
}

void display_reduce_menu() {
	currentState = REDUCE_MENU;
	//options[REDUCE_ADD] = "Addition";
	//options[REDUCE_MUL] = "Multiply";
	//options[REDUCE_MIN] = "Minimum";
	optionCount = 3;
	draw_menu();
}

void select_reduce() {
	currentReduce = currentSelection;
	exit_gui();
}

void display_image_source_menu() {
	currentState = IMAGE_SOURCE_MENU;

	strcpy(options[IMAGE_SOURCE_SD], "MicroSD Card");
	strcpy(options[IMAGE_SOURCE_CAM], "Camera");
	optionCount = IMAGE_SOURCE_COUNT;
	draw_menu();
}

void select_image_source() {
	switch(currentSelection) {
	case IMAGE_SOURCE_SD:
		//TODO set image source to sd
		break;
	case IMAGE_SOURCE_CAM:
		//TODO set image source to cam
		break;
	default:
		break;
	}
}

void display_image_menu() {
	currentState = IMAGE_MENU;
	get_filenames("./image", options, &optionCount);
	draw_menu();
}

void select_image() {
	strcpy(currentImage, options[currentSelection]);
	exit_gui();
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
			for (int gi=0; gi < GUI_SIZE; gi++) {
				imageBuffer[CHAR_H*j*GUI_SIZE + 0*GUI_SIZE + gi] = (byte&(1<<7)) ? fontColor : backColor;
				imageBuffer[CHAR_H*j*GUI_SIZE + 1*GUI_SIZE + gi] = (byte&(1<<6)) ? fontColor : backColor;
				imageBuffer[CHAR_H*j*GUI_SIZE + 2*GUI_SIZE + gi] = (byte&(1<<5)) ? fontColor : backColor;
				imageBuffer[CHAR_H*j*GUI_SIZE + 3*GUI_SIZE + gi] = (byte&(1<<4)) ? fontColor : backColor;
				imageBuffer[CHAR_H*j*GUI_SIZE + 4*GUI_SIZE + gi] = (byte&(1<<3)) ? fontColor : backColor;
				imageBuffer[CHAR_H*j*GUI_SIZE + 5*GUI_SIZE + gi] = (byte&(1<<2)) ? fontColor : backColor;
				imageBuffer[CHAR_H*j*GUI_SIZE + 6*GUI_SIZE + gi] = (byte&(1<<1)) ? fontColor : backColor;
				imageBuffer[CHAR_H*j*GUI_SIZE + 7*GUI_SIZE + gi] = (byte&(1<<0)) ? fontColor : backColor;
			}
		}

		// Write image buffer to SRAM
		for (int y=0; y < CHAR_H; y++) {
			sram_write_buffer(y*SCREEN_W*sizeof(color_t)/sizeof(uint16_t), imageBuffer, OPTION_NAME_LENGTH*CHAR_H*GUI_SIZE*sizeof(color_t)/sizeof(uint16_t));
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
			ebi_set_ebi_mode(EBI_MODE_ON);
			display_main_menu();
		} else {
			switch(currentState) {
			case MAIN_MENU:
				select_main_menu();
				break;
			case KERNEL_MENU:
				select_kernel();
				break;
			case FPGA_MENU:
				select_fpga();
				break;
			case MAP_MENU:
				select_map();
				break;
			case REDUCE_MENU:
				select_reduce();
				break;
			case IMAGE_SOURCE_MENU:
				select_image_source();
				break;
			case IMAGE_MENU:
				select_image();
				break;
			default:
				break;
			}
		}
		break;

	case BTN_BACK:
		if (is_submenu()) {
			display_main_menu();
		}

	}


}
