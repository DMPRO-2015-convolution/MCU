
#ifndef EBI_H_
#define EBI_H_

#include <stdint.h>

extern void init_ebi();
extern void ebi_write(uint32_t *address, uint8_t value);

#endif
