
#ifndef FPGAFLASH_H_
#define FPGAFLASH_H_


extern void init_fpgaflash();
extern void slave_serial(char *binFilename);


#define FPGA_HI_SPI_FREQ     24000000
#define FPGA_LO_SPI_FREQ     100000
#define FPGA_USART           USART1
#define FPGA_LOC             USART_ROUTE_LOCATION_LOC1
#define FPGA_CMUCLOCK        cmuClock_USART1
#define FPGA_GPIOPORT        gpioPortD
#define FPGA_MOSIPIN         0
#define FPGA_MISOPIN         1
#define FPGA_CSPIN           3
#define FPGA_CLKPIN          2

#endif
