#ifndef GUI_H_
#define GUI_H_
#include "button.h"

void on_button_pressed(button_t button);

typedef enum {
	IDLE,
	IDLE_KERNEL,
	IDLE_MAP,
	IDLE_REDUCE,
	IDLE_IMAGE,
	MAIN_MENU,
	KERNEL_MENU,
	FPGA_MENU,
	MAP_MENU,
	REDUCE_MENU,
	IMAGE_SOURCE_MENU,
	IMAGE_MENU
} gui_state_t;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color_t;

#endif
