
#ifndef EBI_H_
#define EBI_H_

#include <stdint.h>


#define BANK1_BASE_ADDR 0x84000000

#define EBI_IMAGE_STREAM_START 0x80000

#define EBI_KERNEL_SIZE 0x00100
#define EBI_KERNEL_ELEMENT 0x00101

#define EBI_IMG_CONFIG_START 0x00000
#define EBI_IMG_CONFIG_HEIGHT 0x00000
#define EBI_IMG_CONFIG_WIDTH 0x00001
#define EBI_IMG_CONFIG_DEPTH 0x00002
#define EBI_IMG_CONFIG_SOURCE 0x00003



extern void init_ebi();
extern void ebi_write(int address, uint16_t value);
extern uint16_t ebi_read(int address);

#endif
