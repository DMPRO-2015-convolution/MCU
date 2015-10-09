
#ifndef EBI_H_
#define EBI_H_

#include <stdint.h>

extern void init_ebi();
extern void ebi_write(int address, uint16_t value);

#endif
