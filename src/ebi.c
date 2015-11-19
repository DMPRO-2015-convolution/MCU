#include "ebi.h"
#include "em_ebi.h"
#include "em_gpio.h"
#include "em_cmu.h"

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

    /* Giant or Leopard family. */

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

    /* First bank needs a name, Bank 0, Base Address 0x80000000  */
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
    ebiConfig.addrHoldCycles  = 255;
    ebiConfig.addrSetupCycles = 255;


    /* Read cycle times */
    ebiConfig.readStrobeCycles = 7;
    ebiConfig.readHoldCycles   = 3;
    ebiConfig.readSetupCycles  = 3;

    /* Write cycle times */
    ebiConfig.writeStrobeCycles = 255;
    ebiConfig.writeHoldCycles   = 255;
    ebiConfig.writeSetupCycles  = 255;

    /* Configure EBI bank 0 */
    EBI_Init(&ebiConfig);


    /* --------------------------------------------------------- */
    /* Second bank needs a name, Bank 1, Base Address 0x84000000 */
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
    ebiConfig.aHigh = ebiAHighA18;

    /* Address Setup and hold time */
    ebiConfig.addrHoldCycles  = 0;
    ebiConfig.addrSetupCycles = 0;

    /* Read cycle times */
    ebiConfig.readStrobeCycles = 255;
    ebiConfig.readHoldCycles   = 255;
    ebiConfig.readSetupCycles  = 255;

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







/*
 *
 * --- CURRENTLY NOT WORKING
 *
 * Writes a buffer of an arbitrary amount of bytes.
 * If the buffer is not divisible by 16 the remaining byte is sent on the next function call
 */
uint16_t prevValue = 0;
int wasDivisible = 1;

extern void ebi_buffer_write(int offset, uint8_t *inBuffer, int size) {

	uint16_t *addr = (uint16_t*)(BANK1_BASE_ADDR + (offset << 1));
	uint16_t *ebiBuffer;

	int size8;
	int size16;

	// Check if the last write has an unsent byte
	if (wasDivisible) {
		ebiBuffer = (uint16_t*)inBuffer;
	} else {
		// Put out first value
		*addr = (prevValue << 7)&(uint16_t)(inBuffer[0]);
		addr++;
		ebiBuffer = (uint16_t*)(inBuffer+1);
		size8 = size - 1;
		size16 = (size8)/2;
	}


	// Send out 16 bit data
	for (int i=0; i < size16; i++) {
		*addr = ebiBuffer[i];
		addr++;
	}


	// Check if the sent data was divisible
	if (size8%2) {
		wasDivisible = 1;
	} else {
		prevValue = inBuffer[size];
		wasDivisible = 0;
	}
}

extern void flush_ebi_buffer(int offset) {
	uint16_t *addr = (uint16_t*)(BANK1_BASE_ADDR + (offset << 1));
	*addr = ((uint16_t)prevValue)<<7;
	reset_ebi_buffer();
}

extern void reset_ebi_buffer() {
	prevValue = 0;
	wasDivisible = 1;
}







