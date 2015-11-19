

#ifndef IMAGE_H_
#define IMAGE_H_

typedef enum {IMAGE_IDLE, IMAGE_SENDING, IMAGE_STOPPING} image_state_t;

void init_image();
void image_send_start(char *imageName);

#endif /* IMAGE_H_ */
