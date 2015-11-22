#include "ebi.h"
#include "em_ebi.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "filesystem.h"
#include "gui.h"


#define BUFF_SIZE 32
uint16_t ebiBuffer[BUFF_SIZE];
uint8_t lastValue;

extern void init_ebi() {

	EBI_Init_TypeDef ebiConfig = EBI_INIT_DEFAULT;

    /* Enable clocks */
    CMU_ClockEnable(cmuClock_EBI, true);
    CMU_ClockEnable(cmuClock_GPIO, true);

    //CMU_HFRCOBandSet(cmuHFRCOBand_28MHz);

    /* --- Configure GPIO pins as push pull -------------------- */

    /* EBI AD9..15 */
    GPIO_PinModeSet( gpioPortA,  0, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  1, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  2, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  3, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  4, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  5, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  6, gpioModePushPull, 0 );

    /* EBI AD8 */
    GPIO_PinModeSet( gpioPortA, 15, gpioModePushPull, 0 );

    /* EBI A00-A06 */
    GPIO_PinModeSet( gpioPortA, 12, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA, 13, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA, 14, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB, 10, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  6, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  7, gpioModePushPull, 0 );

    /* EBI A07-A14 */
    GPIO_PinModeSet( gpioPortE,  0, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  1, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  10, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  4, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  5, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  6, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  7, gpioModePushPull, 0 );

    /* EBI A15-A18 */
    GPIO_PinModeSet( gpioPortC,  8, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  0, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  1, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  2, gpioModePushPull, 0 );

    /* EBI CS0-CS3 */
    GPIO_PinModeSet( gpioPortD,  9, gpioModePushPull, 1 );
    GPIO_PinModeSet( gpioPortD, 10, gpioModePushPull, 1 );
    GPIO_PinModeSet( gpioPortD, 11, gpioModePushPull, 1 );
    GPIO_PinModeSet( gpioPortD, 12, gpioModePushPull, 1 );

    /* EBI AD0..7 */
    GPIO_PinModeSet( gpioPortE,  8, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 10, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 11, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 12, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 13, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 14, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 15, gpioModePushPull, 0 );

    /* EBI ARDY/WEN/REN/ALE */
    GPIO_PinModeSet( gpioPortF,  2, gpioModeInput,    0 );
    GPIO_PinModeSet( gpioPortF,  8, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortF,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC, 11, gpioModePushPull, 0 );

    /* EBI Byte Lane 0 support BL0/BL1 */
    GPIO_PinModeSet( gpioPortF, 6, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortF, 7, gpioModePushPull, 0 );


    /* --------------------------------------------------------- */
    /* SRAM, Bank 0, Base Address 0x80000000                     */
    /* --------------------------------------------------------- */
    ebiConfig.banks       = EBI_BANK0;
    ebiConfig.csLines     = EBI_CS0;
    ebiConfig.mode        = ebiModeD16;
    ebiConfig.alePolarity = ebiActiveHigh;
    ebiConfig.location    = ebiLocation1;

    /* keep blEnable */
    ebiConfig.blEnable     = false;
    ebiConfig.addrHalfALE  = false;
    ebiConfig.readPrefetch = false;
    ebiConfig.noIdle       = true;

    /* keep alow/ahigh configuration */
    ebiConfig.aLow = ebiALowA0;
    ebiConfig.aHigh = ebiAHighA19;

    /* Address Setup and hold time */
    ebiConfig.addrHoldCycles  = 0;
    ebiConfig.addrSetupCycles = 0;


    /* Read cycle times */
    ebiConfig.readStrobeCycles = 7;
    ebiConfig.readHoldCycles   = 3;
    ebiConfig.readSetupCycles  = 3;

    /* Write cycle times */
    ebiConfig.writeStrobeCycles = 1;
    ebiConfig.writeHoldCycles   = 1;
    ebiConfig.writeSetupCycles  = 0;

    /* Configure EBI bank 0 */
    EBI_Init(&ebiConfig);


    /* --------------------------------------------------------- */
    /* Processor communication, Bank 1, Base Address 0x84000000  */
    /* --------------------------------------------------------- */
    ebiConfig.banks       = EBI_BANK1;
    ebiConfig.csLines     = EBI_CS1;
    ebiConfig.mode        = ebiModeD16;
    ebiConfig.alePolarity = ebiActiveHigh;
    ebiConfig.location    = ebiLocation1;
    /* keep blEnable */
    ebiConfig.blEnable     = false;
    ebiConfig.addrHalfALE  = false;
    ebiConfig.readPrefetch = false;
    ebiConfig.noIdle       = true;

    /* keep alow/ahigh configuration */
    ebiConfig.aLow = ebiALowA0;
    ebiConfig.aHigh = ebiAHighA19;

    /* Address Setup and hold time */
    ebiConfig.addrHoldCycles  = 0;
    ebiConfig.addrSetupCycles = 0;

    /* Read cycle times */
    ebiConfig.readStrobeCycles = 7;
    ebiConfig.readHoldCycles   = 3;
    ebiConfig.readSetupCycles  = 3;

    /* Write cycle times */
    ebiConfig.writeSetupCycles  = 1;
    ebiConfig.writeStrobeCycles = 1;
    ebiConfig.writeHoldCycles   = 0;

    // Set polarity to active high
    ebiConfig.wePolarity = ebiActiveHigh;
    ebiConfig.rePolarity = ebiActiveHigh;

    /* Configure EBI bank 1 */
    EBI_Init(&ebiConfig);

}


extern void sram_write(int address, uint16_t value) {
	*(uint16_t *)(SRAM_BASE_ADDR + (address << 1)) = value;
}

extern void sram_write_buffer(int offset, uint16_t *buffer, uint16_t size) {
	for (int i=0; i<size; i++) {
		*(uint16_t *)(SRAM_BASE_ADDR + ((offset + i) << 1)) = buffer[i];
	}
}

extern uint16_t sram_read(int address) {
	return *(volatile uint16_t*)(SRAM_BASE_ADDR + (address << 1));
}

extern void ebi_reset_processor() {
	*(uint16_t *)(DAISY_BASE_ADDR + (2<<1)) = 0xff;
}

extern void ebi_write_data_stream(uint16_t value) {
	*(uint16_t *)(DAISY_BASE_ADDR) = value;
}

extern void ebi_configure_map_reduce(uint8_t map, uint8_t reduce) {

	// 24 bit should be sent 10 times, means 15 16 bit transfers (10*24/16=15)

	uint8_t instrBuffer[10*3] = {0};
	for (int i=0; i<10; i++) {
		instrBuffer[i*3+1] = reduce;
		instrBuffer[i*3+2] = map;
	}

	uint16_t *ebiBuffer = (uint16_t*)instrBuffer;

	for (int i=0; i < 15; i++) {
		*(uint16_t*)(DAISY_BASE_ADDR) = ebiBuffer[i];
	}
}

extern void ebi_configure_kernel(kernel_t kernel) {
	// Assuming 3x3 kernel

	// We have only 9 values, but need 10 to pipe through everything
	uint8_t kernelBuffer[10*3] = {0};

	// Kernel is loaded in the following way
	//
	// 6 | 7 | 8
	// 3 | 4 | 5
	// 0 | 1 | 2
	//
	for (int i=0; i<9; i++) {
		kernelBuffer[i*3] = kernel.elements[6-(i/3)*3+i%3];
	}

	uint16_t *ebiBuffer = (uint16_t*)kernelBuffer;

	for (int i=0; i < 15; i++) {
		*(uint16_t*)(DAISY_BASE_ADDR) = ebiBuffer[i];
	}

}

extern void ebi_set_ebi_mode(uint16_t mode) {
	*(uint16_t*)(BANK1_BASE_ADDR + (1<<1)) = mode;
}

extern void ebi_write(int address, uint16_t value) {
	*(uint16_t *)(BANK1_BASE_ADDR + (address << 1)) = value;
}


extern uint16_t ebi_read(int address) {
	return *(volatile uint16_t*)(BANK1_BASE_ADDR + (address << 1));
}

extern void ebi_write_buffer(int offset, uint16_t *buffer, int size) {
	uint16_t *addr = (uint16_t *)(BANK1_BASE_ADDR + (offset << 1));
	for (int i=0; i < size; i++) {
		*(addr+i) = buffer[i];
	}
}


// Write zero values to pad images
extern void ebi_write_pad(int offset, uint32_t n) {
	uint16_t *addr = (uint16_t *)(BANK1_BASE_ADDR + (offset << 1));
	for (int i=0; i < n; i++) {
		*(addr+i) = 0;
	}
}


