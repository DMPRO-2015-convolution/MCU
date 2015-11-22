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


// Map and reduce operations
#define MAP_MUL 0
#define MAP_ADD 1
#define MAP_MASK 2

#define REDUCE_ADD 0
#define REDUCE_MUL 1
#define REDUCE_MIN 2

#endif
