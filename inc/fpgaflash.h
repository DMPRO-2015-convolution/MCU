
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


#define FPGA_STATUS_PORT gpioPortB
#define FPGA_INIT_B_PIN 8
#define FPGA_PROGRAM_B_PIN 11
#define FPGA_DONE_PIN 12

#define FPGA_OSCILLATOR_PORT gpioPortF
#define FPGA_OSCILLATOR_PIN 12

#endif
