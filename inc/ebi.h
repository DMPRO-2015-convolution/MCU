
#ifndef EBI_H_
#define EBI_H_

#include <stdint.h>

#define SRAM_BASE_ADDR  0x80000000
#define DAISY_BASE_ADDR 0x84000000
#define BANK1_BASE_ADDR 0x84000000

#define EBI_MODE_OFF 0
#define EBI_MODE_ON 1


#define EBI_IMAGE_STREAM_START 0x80000


extern void init_ebi();
extern void ebi_write(int address, uint16_t value);
extern uint16_t ebi_read(int address);
extern void ebi_write_buffer(int offset, uint16_t *buffer, int size);
extern void ebi_write_pad(int offset, uint32_t n);

#endif
