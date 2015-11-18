#include "filesystem.h"
#include "font.h"

#define PBM_SIZE PBM_W*PBM_H*CHAR_W*CHAR_SIZE

uint8_t pbmFont[PBM_SIZE];
const int pbm_w = 16;
const int pbm_h = 16;
const int char_w = 1;
const int char_h = 8;


void init_font() {
	FIL file;
	int bytesRead;

	// Open font file
	open_file(&file, "system/8x8.pbm");


	// Read font to memory
	read_file(&file, pbmFont, PBM_SIZE, &bytesRead);

	// Close file
	close_file(&file);
}


void draw_string_to_buffer(char* string, int len, uint8_t *buffer, int buff_w) {
	for (int i=0; i < len; i++) {
		uint8_t ch = string[i];

		int start = ch%PBM_W + (ch/PBM_W)*PBM_W*CHAR_SIZE;

		// Copy to buffer
		for (int row=0; row < CHAR_H; row++) {
			buffer[i+row*buff_w] = pbmFont[start+row*PBM_W*CHAR_W];
		}
	}
}
