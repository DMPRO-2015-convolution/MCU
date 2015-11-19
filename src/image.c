#include "filesystem.h"
#include "ebi.h"
#include "image.h"

#define BUFFSIZE 1024*8

image_state_t currentState;


void init_image() {
	currentState = IMAGE_IDLE;
}

void image_send_stop() {
	currentState = IMAGE_STOPPING;
}

image_state_t image_get_state() {
	return currentState;
}

void image_send_start(char *imageName) {
	currentState = IMAGE_SENDING;

	FIL file;
	uint16_t imageBuffer[BUFFSIZE/2];
	uint16_t bytesRead;

	// Open image
	open_file(&file, imageName);


	while (currentState == IMAGE_SENDING) {

		read_file(&file, imageBuffer, BUFFSIZE, &bytesRead);

		if (bytesRead == 0) {
			// Seek file back to start or to next frame
			seek_file(&file, 0);
		} else {
			// Send image buffer over EBI
			ebi_write_buffer(EBI_IMAGE_STREAM_START, imageBuffer, bytesRead/2);
		}
	}

	// Finished sending image, close file
	close_file(&file);
	currentState = IMAGE_IDLE;
}
