/* Altered microsdconfig.h to use correct ports */

#ifndef __MICROSDCONFIG_H
#define __MICROSDCONFIG_H

// Don't increase MICROSD_HI_SPI_FREQ beyond 12MHz. Next step will be 24MHz
// which is out of spec.
#define MICROSD_HI_SPI_FREQ     12000000
#define MICROSD_LO_SPI_FREQ     100000


#ifdef DEVKIT

#define MICROSD_USART           USART0
#define MICROSD_LOC             USART_ROUTE_LOCATION_LOC1
#define MICROSD_CMUCLOCK        cmuClock_USART0
#define MICROSD_GPIOPORT        gpioPortE
#define MICROSD_MOSIPIN         7
#define MICROSD_MISOPIN         6
#define MICROSD_CSPIN           4
#define MICROSD_CLKPIN          5

#else

#define MICROSD_USART           USART2
#define MICROSD_LOC             USART_ROUTE_LOCATION_LOC0
#define MICROSD_CMUCLOCK        cmuClock_USART2
#define MICROSD_GPIOPORT        gpioPortC
#define MICROSD_MOSIPIN         2
#define MICROSD_MISOPIN         3
#define MICROSD_CSPIN           5
#define MICROSD_CLKPIN          4

#endif


/*
#define MICROSD_USART           USART0
#define MICROSD_LOC             USART_ROUTE_LOCATION_LOC1
#define MICROSD_CMUCLOCK        cmuClock_USART0
#define MICROSD_GPIOPORT        gpioPortE
#define MICROSD_MOSIPIN         7
#define MICROSD_MISOPIN         6
#define MICROSD_CSPIN           4
#define MICROSD_CLKPIN          5
*/

/*
#define MICROSD_USART           USART1
#define MICROSD_LOC             USART_ROUTE_LOCATION_LOC0
#define MICROSD_CMUCLOCK        cmuClock_USART1
#define MICROSD_GPIOPORT        gpioPortC
#define MICROSD_MOSIPIN         0
#define MICROSD_MISOPIN         1
#define MICROSD_CSPIN           8
#define MICROSD_CLKPIN          7
*/

#endif // __MICROSDCONFIG_H

