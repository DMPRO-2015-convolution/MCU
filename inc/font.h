#ifndef FONT_H_
#define FONT_H_
#include <stdint.h>


#define PBM_W 16
#define PBM_H 16
#define CHAR_W 1
#define CHAR_H 8
#define CHAR_SIZE CHAR_W*CHAR_H

void init_font();
void draw_string_to_buffer(char* string, int len, uint8_t *buffer, int buff_w);

#endif
