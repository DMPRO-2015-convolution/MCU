
#ifndef EBI_H_
#define EBI_H_

#include <stdint.h>


#define BANK1_BASE_ADDR 0x84000000

#define EBI_IMAGE_STREAM_START 0x80000


#define EBI_KERNEL_START 0x00100
#define EBI_KERNEL_SIZE 0x00100
#define EBI_KERNEL_ELEMENT 0x00101


// TODO Assign proper address for map, reduce and image source
#define EBI_MAP 0x1
#define EBI_REDUCE 0x2
#define EBI_IMAGE_SOURCE 0x3

#define EBI_IMG_CONFIG_START 0x00000
#define EBI_IMG_CONFIG_HEIGHT 0x00000
#define EBI_IMG_CONFIG_WIDTH 0x00001
#define EBI_IMG_CONFIG_DEPTH 0x00002
#define EBI_IMG_CONFIG_SOURCE 0x00003



extern void init_ebi();
extern void ebi_write(int address, uint16_t value);
extern uint16_t ebi_read(int address);
extern void ebi_write_buffer(int offset, uint16_t *buffer, int size);
extern void ebi_write_pad(int offset, uint32_t n);

#endif
