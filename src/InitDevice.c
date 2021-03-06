//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include "InitDevice.h"

// USER PROTOTYPES
// USER FUNCTIONS

// $[Library includes]
#include "em_system.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_ebi.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "em_usart.h"
// [Library includes]$

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	CMU_enter_DefaultMode_from_RESET();
	USART0_enter_DefaultMode_from_RESET();
	USART1_enter_DefaultMode_from_RESET();
	USART2_enter_DefaultMode_from_RESET();
	I2C0_enter_DefaultMode_from_RESET();
	EBI_enter_DefaultMode_from_RESET();
	PORTIO_enter_DefaultMode_from_RESET();
	// [Config Calls]$

}

//================================================================================
// HFXO_enter_DefaultMode_from_RESET
//================================================================================
extern void HFXO_enter_DefaultMode_from_RESET(void) {
	// $[HFXO]
	// [HFXO]$

}

//================================================================================
// LFXO_enter_DefaultMode_from_RESET
//================================================================================
extern void LFXO_enter_DefaultMode_from_RESET(void) {
	// $[Use oscillator source]
	// [Use oscillator source]$

	// $[LFXO Boost Percent]
	// [LFXO Boost Percent]$

	// $[REDLFXO Boost]
	// [REDLFXO Boost]$

}

//================================================================================
// CMU_enter_DefaultMode_from_RESET
//================================================================================
extern void CMU_enter_DefaultMode_from_RESET(void) {
	// $[LFXO enable]
	// [LFXO enable]$

	// $[HFXO enable]
	// [HFXO enable]$

	// $[LFACLK Setup]
	// [LFACLK Setup]$

	// $[High Frequency Clock select]
	/* Using HFRCO at 14MHz as high frequency clock, HFCLK */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
	// [High Frequency Clock select]$

	// $[Peripheral Clock enables]
	/* Enable clock for EBI */
	CMU_ClockEnable(cmuClock_EBI, true);

	/* Enable clock for I2C0 */
	CMU_ClockEnable(cmuClock_I2C0, true);

	/* Enable clock for USART0 */
	CMU_ClockEnable(cmuClock_USART0, true);

	/* Enable clock for USART1 */
	CMU_ClockEnable(cmuClock_USART1, true);

	/* Enable clock for USART2 */
	CMU_ClockEnable(cmuClock_USART2, true);

	/* Enable clock for GPIO by default */
	CMU_ClockEnable(cmuClock_GPIO, true);

	// [Peripheral Clock enables]$

}

//================================================================================
// ADC0_enter_DefaultMode_from_RESET
//================================================================================
extern void ADC0_enter_DefaultMode_from_RESET(void) {
	// $[ADC_Init]
	// [ADC_Init]$

	// $[ADC_InitSingle]
	// [ADC_InitSingle]$

	// $[ADC_InitScan]
	// [ADC_InitScan]$

}

//================================================================================
// ACMP0_enter_DefaultMode_from_RESET
//================================================================================
extern void ACMP0_enter_DefaultMode_from_RESET(void) {
	// $[ACMP Initialization]
	// [ACMP Initialization]$

	// $[ACMP Channel config]
	// [ACMP Channel config]$

}

//================================================================================
// ACMP1_enter_DefaultMode_from_RESET
//================================================================================
extern void ACMP1_enter_DefaultMode_from_RESET(void) {
	// $[ACMP Initialization]
	// [ACMP Initialization]$

	// $[ACMP Channel config]
	// [ACMP Channel config]$

}

//================================================================================
// DAC0_enter_DefaultMode_from_RESET
//================================================================================
extern void DAC0_enter_DefaultMode_from_RESET(void) {
	// $[DAC Initialization]
	// [DAC Initialization]$

	// $[DAC Channel 0 config]
	// [DAC Channel 0 config]$

	// $[DAC Channel 1 config]
	// [DAC Channel 1 config]$

}

//================================================================================
// BURTC_enter_DefaultMode_from_RESET
//================================================================================
extern void BURTC_enter_DefaultMode_from_RESET(void) {
	// $[CMU_ClockEnable]
	// [CMU_ClockEnable]$

	// $[CMU_OscillatorEnable]
	// [CMU_OscillatorEnable]$

	// $[RMU_ResetControl]
	// [RMU_ResetControl]$

	// $[BURTC_Init]
	// [BURTC_Init]$

	// $[BURTC_CompareSet]
	// [BURTC_CompareSet]$

}

//================================================================================
// RTC_enter_DefaultMode_from_RESET
//================================================================================
extern void RTC_enter_DefaultMode_from_RESET(void) {
	// $[RTC_Init]
	// [RTC_Init]$

}

//================================================================================
// OPAMP0_enter_DefaultMode_from_RESET
//================================================================================
extern void OPAMP0_enter_DefaultMode_from_RESET(void) {
	// $[DAC Output]
	// [DAC Output]$

	// $[OPAMP_Enable]
	// [OPAMP_Enable]$

}

//================================================================================
// OPAMP1_enter_DefaultMode_from_RESET
//================================================================================
extern void OPAMP1_enter_DefaultMode_from_RESET(void) {
	// $[DAC Output]
	// [DAC Output]$

	// $[OPAMP_Enable]
	// [OPAMP_Enable]$

}

//================================================================================
// OPAMP2_enter_DefaultMode_from_RESET
//================================================================================
extern void OPAMP2_enter_DefaultMode_from_RESET(void) {
	// $[DAC Output]
	// [DAC Output]$

	// $[OPAMP_Enable]
	// [OPAMP_Enable]$

}

//================================================================================
// USART0_enter_DefaultMode_from_RESET
//================================================================================
extern void USART0_enter_DefaultMode_from_RESET(void) {
	// $[USART_InitAsync]
	// [USART_InitAsync]$

	// $[USART_InitSync]
	USART_InitSync_TypeDef initsync = USART_INITSYNC_DEFAULT;

	initsync.baudrate = 115200;
	initsync.databits = usartDatabits8;
	initsync.master = 1;
	initsync.msbf = 1;
	initsync.clockMode = usartClockMode0;
#if defined( USART_INPUT_RXPRS ) && defined( USART_TRIGCTRL_AUTOTXTEN )
	initsync.prsRxEnable = 0;
	initsync.prsRxCh = 0;
	initsync.autoTx = 0;
#endif

	USART_InitSync(USART0, &initsync);
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

	initprs.rxTriggerEnable = 0;
	initprs.txTriggerEnable = 0;
	initprs.prsTriggerChannel = usartPrsTriggerCh0;

	USART_InitPrsTrigger(USART0, &initprs);
	// [USART_InitPrsTrigger]$

}

//================================================================================
// USART1_enter_DefaultMode_from_RESET
//================================================================================
extern void USART1_enter_DefaultMode_from_RESET(void) {
	// $[USART_InitAsync]
	// [USART_InitAsync]$

	// $[USART_InitSync]
	USART_InitSync_TypeDef initsync = USART_INITSYNC_DEFAULT;

	initsync.baudrate = 115200;
	initsync.databits = usartDatabits8;
	initsync.master = 1;
	initsync.msbf = 1;
	initsync.clockMode = usartClockMode0;
#if defined( USART_INPUT_RXPRS ) && defined( USART_TRIGCTRL_AUTOTXTEN )
	initsync.prsRxEnable = 0;
	initsync.prsRxCh = 0;
	initsync.autoTx = 0;
#endif

	USART_InitSync(USART1, &initsync);
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

	initprs.rxTriggerEnable = 0;
	initprs.txTriggerEnable = 0;
	initprs.prsTriggerChannel = usartPrsTriggerCh0;

	USART_InitPrsTrigger(USART1, &initprs);
	// [USART_InitPrsTrigger]$

}

//================================================================================
// USART2_enter_DefaultMode_from_RESET
//================================================================================
extern void USART2_enter_DefaultMode_from_RESET(void) {
	// $[USART_InitAsync]
	USART_InitAsync_TypeDef initasync = USART_INITASYNC_DEFAULT;

	initasync.baudrate = 115200;
	initasync.databits = usartDatabits8;
	initasync.parity = usartNoParity;
	initasync.stopbits = usartStopbits1;
	initasync.oversampling = usartOVS16;
#if defined( USART_INPUT_RXPRS ) && defined( USART_CTRL_MVDIS )
	initasync.mvdis = 0;
	initasync.prsRxEnable = 0;
	initasync.prsRxCh = 0;
#endif

	USART_InitAsync(USART2, &initasync);
	// [USART_InitAsync]$

	// $[USART_InitSync]
	// [USART_InitSync]$

	// $[USART_InitPrsTrigger]
	USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

	initprs.rxTriggerEnable = 0;
	initprs.txTriggerEnable = 0;
	initprs.prsTriggerChannel = usartPrsTriggerCh0;

	USART_InitPrsTrigger(USART2, &initprs);
	// [USART_InitPrsTrigger]$

}

//================================================================================
// UART0_enter_DefaultMode_from_RESET
//================================================================================
extern void UART0_enter_DefaultMode_from_RESET(void) {
	// $[UART_InitAsync]
	// [UART_InitAsync]$

	// $[USART_InitPrsTrigger]
	// [USART_InitPrsTrigger]$

}

//================================================================================
// UART1_enter_DefaultMode_from_RESET
//================================================================================
extern void UART1_enter_DefaultMode_from_RESET(void) {
	// $[UART_InitAsync]
	// [UART_InitAsync]$

	// $[USART_InitPrsTrigger]
	// [USART_InitPrsTrigger]$

}

//================================================================================
// LEUART0_enter_DefaultMode_from_RESET
//================================================================================
extern void LEUART0_enter_DefaultMode_from_RESET(void) {
	// $[LEUART0 initialization]
	// [LEUART0 initialization]$

}

//================================================================================
// LEUART1_enter_DefaultMode_from_RESET
//================================================================================
extern void LEUART1_enter_DefaultMode_from_RESET(void) {
	// $[LEUART1 initialization]
	// [LEUART1 initialization]$

}

//================================================================================
// VCMP_enter_DefaultMode_from_RESET
//================================================================================
extern void VCMP_enter_DefaultMode_from_RESET(void) {
	// $[VCMP_Init]
	// [VCMP_Init]$

}

//================================================================================
// WDOG_enter_DefaultMode_from_RESET
//================================================================================
extern void WDOG_enter_DefaultMode_from_RESET(void) {
	// $[CMU_ClockEnable]
	// [CMU_ClockEnable]$

	// $[CMU_OscillatorEnable]
	// [CMU_OscillatorEnable]$

	// $[WDOG_Init]
	// [WDOG_Init]$

}

//================================================================================
// I2C0_enter_DefaultMode_from_RESET
//================================================================================
extern void I2C0_enter_DefaultMode_from_RESET(void) {
	// $[I2C0 initialization]
	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	init.enable = 1;
	init.master = 1;
	init.freq = I2C_FREQ_STANDARD_MAX;
	init.clhr = i2cClockHLRStandard;
	I2C_Init(I2C0, &init);
	// [I2C0 initialization]$

}

//================================================================================
// I2C1_enter_DefaultMode_from_RESET
//================================================================================
extern void I2C1_enter_DefaultMode_from_RESET(void) {
	// $[I2C1 initialization]
	// [I2C1 initialization]$

}

//================================================================================
// LCD_enter_DefaultMode_from_RESET
//================================================================================
extern void LCD_enter_DefaultMode_from_RESET(void) {
	// $[LCD initialization]
	// [LCD initialization]$

}

//================================================================================
// TIMER0_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER0_enter_DefaultMode_from_RESET(void) {
	// $[TIMER0 initialization]
	// [TIMER0 initialization]$

	// $[TIMER0 CC0 init]
	// [TIMER0 CC0 init]$

	// $[TIMER0 CC1 init]
	// [TIMER0 CC1 init]$

	// $[TIMER0 CC2 init]
	// [TIMER0 CC2 init]$

	// $[TIMER0 DTI init]
	// [TIMER0 DTI init]$

}

//================================================================================
// TIMER1_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER1_enter_DefaultMode_from_RESET(void) {
	// $[TIMER1 initialization]
	// [TIMER1 initialization]$

	// $[TIMER1 CC0 init]
	// [TIMER1 CC0 init]$

	// $[TIMER1 CC1 init]
	// [TIMER1 CC1 init]$

	// $[TIMER1 CC2 init]
	// [TIMER1 CC2 init]$

}

//================================================================================
// TIMER2_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER2_enter_DefaultMode_from_RESET(void) {
	// $[TIMER2 initialization]
	// [TIMER2 initialization]$

	// $[TIMER2 CC0 init]
	// [TIMER2 CC0 init]$

	// $[TIMER2 CC1 init]
	// [TIMER2 CC1 init]$

	// $[TIMER2 CC2 init]
	// [TIMER2 CC2 init]$

}

//================================================================================
// TIMER3_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER3_enter_DefaultMode_from_RESET(void) {
	// $[TIMER3 initialization]
	// [TIMER3 initialization]$

	// $[TIMER3 CC0 init]
	// [TIMER3 CC0 init]$

	// $[TIMER3 CC1 init]
	// [TIMER3 CC1 init]$

	// $[TIMER3 CC2 init]
	// [TIMER3 CC2 init]$

}

//================================================================================
// PCNT0_enter_DefaultMode_from_RESET
//================================================================================
extern void PCNT0_enter_DefaultMode_from_RESET(void) {
	// $[PCNT0 initialization]
	// [PCNT0 initialization]$

}

//================================================================================
// PCNT1_enter_DefaultMode_from_RESET
//================================================================================
extern void PCNT1_enter_DefaultMode_from_RESET(void) {
	// $[PCNT1 initialization]
	// [PCNT1 initialization]$

}

//================================================================================
// PCNT2_enter_DefaultMode_from_RESET
//================================================================================
extern void PCNT2_enter_DefaultMode_from_RESET(void) {
	// $[PCNT2 initialization]
	// [PCNT2 initialization]$

}

//================================================================================
// PRS_enter_DefaultMode_from_RESET
//================================================================================
extern void PRS_enter_DefaultMode_from_RESET(void) {
	// $[PRS initialization]
	// [PRS initialization]$

}

//================================================================================
// ETM_enter_DefaultMode_from_RESET
//================================================================================
extern void ETM_enter_DefaultMode_from_RESET(void) {
	// $[ETM initialization]
	// [ETM initialization]$

}

//================================================================================
// EBI_enter_DefaultMode_from_RESET
//================================================================================
extern void EBI_enter_DefaultMode_from_RESET(void) {
	// $[EBI initialization]
	EBI_Init_TypeDef ebiInit = EBI_INIT_DEFAULT;

	/* Start with initializing the base EBI */
	ebiInit.mode = ebiModeD16;
	ebiInit.ardyPolarity = ebiActiveLow;
	ebiInit.alePolarity = ebiActiveLow;
	ebiInit.wePolarity = ebiActiveLow;
	ebiInit.rePolarity = ebiActiveLow;
	ebiInit.csPolarity = ebiActiveLow;
	ebiInit.ardyEnable = 0;
	ebiInit.ardyDisableTimeout = 0;
	ebiInit.addrSetupCycles = 1;
	ebiInit.addrHoldCycles = 0;
	ebiInit.readSetupCycles = 0;
	ebiInit.readStrobeCycles = 0;
	ebiInit.readHoldCycles = 1;
	ebiInit.writeSetupCycles = 0;
	ebiInit.writeStrobeCycles = 1;
	ebiInit.writeHoldCycles = 0;
	ebiInit.banks = 0 | EBI_BANK0 | EBI_BANK1;
	ebiInit.csLines = 0 | EBI_CS0 | EBI_CS1;

	/* Generating extra config parameters on Giant/Wonder */
	ebiInit.blPolarity = ebiActiveLow;
	ebiInit.blEnable = 0;
	ebiInit.noIdle = 0;
	ebiInit.addrHalfALE = 0;
	ebiInit.readPageMode = 0;
	ebiInit.readPrefetch = 0;
	ebiInit.readHalfRE = 0;
	ebiInit.writeBufferDisable = 0;
	ebiInit.writeHalfWE = 0;
	ebiInit.aLow = ebiALowA0;
	ebiInit.aHigh = ebiAHighA19;

	/* Enable/disable EBI after initialization */
	ebiInit.enable = 1;
	EBI_Init(&ebiInit);
	/* TFT mode has not been enabled or is not available */
	// [EBI initialization]$
}

extern void PORTIO_enter_DefaultMode_from_RESET(void) {

	// $[Port A Configuration]

	/* Pin PA0 is configured to Push-pull */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_PUSHPULL;

	/* Pin PA1 is configured to Push-pull */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE1_MASK)
			| GPIO_P_MODEL_MODE1_PUSHPULL;

	/* Pin PA2 is configured to Push-pull */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE2_MASK)
			| GPIO_P_MODEL_MODE2_PUSHPULL;

	/* Pin PA3 is configured to Push-pull */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE3_MASK)
			| GPIO_P_MODEL_MODE3_PUSHPULL;

	/* Pin PA4 is configured to Push-pull */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE4_MASK)
			| GPIO_P_MODEL_MODE4_PUSHPULL;

	/* Pin PA5 is configured to Push-pull */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE5_MASK)
			| GPIO_P_MODEL_MODE5_PUSHPULL;

	/* Pin PA6 is configured to Push-pull */
	GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE6_MASK)
			| GPIO_P_MODEL_MODE6_PUSHPULL;

	/* Pin PA12 is configured to Push-pull */
	GPIO->P[0].MODEH = (GPIO->P[0].MODEH & ~_GPIO_P_MODEH_MODE12_MASK)
			| GPIO_P_MODEH_MODE12_PUSHPULL;

	/* Pin PA13 is configured to Push-pull */
	GPIO->P[0].MODEH = (GPIO->P[0].MODEH & ~_GPIO_P_MODEH_MODE13_MASK)
			| GPIO_P_MODEH_MODE13_PUSHPULL;

	/* Pin PA14 is configured to Push-pull */
	GPIO->P[0].MODEH = (GPIO->P[0].MODEH & ~_GPIO_P_MODEH_MODE14_MASK)
			| GPIO_P_MODEH_MODE14_PUSHPULL;

	/* Pin PA15 is configured to Push-pull */
	GPIO->P[0].MODEH = (GPIO->P[0].MODEH & ~_GPIO_P_MODEH_MODE15_MASK)
			| GPIO_P_MODEH_MODE15_PUSHPULL;
	// [Port A Configuration]$

	// $[Port B Configuration]

	/* Pin PB0 is configured to Push-pull */
	GPIO->P[1].MODEL = (GPIO->P[1].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_PUSHPULL;

	/* Pin PB1 is configured to Push-pull */
	GPIO->P[1].MODEL = (GPIO->P[1].MODEL & ~_GPIO_P_MODEL_MODE1_MASK)
			| GPIO_P_MODEL_MODE1_PUSHPULL;

	/* Pin PB2 is configured to Push-pull */
	GPIO->P[1].MODEL = (GPIO->P[1].MODEL & ~_GPIO_P_MODEL_MODE2_MASK)
			| GPIO_P_MODEL_MODE2_PUSHPULL;

	/* Pin PB3 is configured to Push-pull */
	GPIO->P[1].MODEL = (GPIO->P[1].MODEL & ~_GPIO_P_MODEL_MODE3_MASK)
			| GPIO_P_MODEL_MODE3_PUSHPULL;

	/* Pin PB7 is configured to Push-pull */
	GPIO->P[1].MODEL = (GPIO->P[1].MODEL & ~_GPIO_P_MODEL_MODE7_MASK)
			| GPIO_P_MODEL_MODE7_PUSHPULL;

	/* Pin PB8 is configured to Input enabled */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE8_MASK)
			| GPIO_P_MODEH_MODE8_INPUT;

	/* Pin PB9 is configured to Push-pull */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE9_MASK)
			| GPIO_P_MODEH_MODE9_PUSHPULL;

	/* Pin PB10 is configured to Push-pull */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE10_MASK)
			| GPIO_P_MODEH_MODE10_PUSHPULL;

	/* Pin PB13 is configured to Push-pull */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE13_MASK)
			| GPIO_P_MODEH_MODE13_PUSHPULL;

	/* Pin PB14 is configured to Push-pull */
	GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE14_MASK)
			| GPIO_P_MODEH_MODE14_PUSHPULL;
	// [Port B Configuration]$

	// $[Port C Configuration]

	/* Pin PC0 is configured to Push-pull */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_PUSHPULL;

	/* Pin PC1 is configured to Input enabled */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE1_MASK)
			| GPIO_P_MODEL_MODE1_INPUT;

	/* Pin PC2 is configured to Push-pull */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE2_MASK)
			| GPIO_P_MODEL_MODE2_PUSHPULL;

	/* Pin PC3 is configured to Input enabled */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE3_MASK)
			| GPIO_P_MODEL_MODE3_INPUT;

	/* Pin PC4 is configured to Push-pull */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE4_MASK)
			| GPIO_P_MODEL_MODE4_PUSHPULL;

	/* Pin PC5 is configured to Push-pull */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE5_MASK)
			| GPIO_P_MODEL_MODE5_PUSHPULL;

	/* Pin PC6 is configured to Push-pull */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE6_MASK)
			| GPIO_P_MODEL_MODE6_PUSHPULL;

	/* Pin PC7 is configured to Push-pull */
	GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE7_MASK)
			| GPIO_P_MODEL_MODE7_PUSHPULL;

	/* Pin PC8 is configured to Push-pull */
	GPIO->P[2].MODEH = (GPIO->P[2].MODEH & ~_GPIO_P_MODEH_MODE8_MASK)
			| GPIO_P_MODEH_MODE8_PUSHPULL;

	/* Pin PC9 is configured to Push-pull */
	GPIO->P[2].MODEH = (GPIO->P[2].MODEH & ~_GPIO_P_MODEH_MODE9_MASK)
			| GPIO_P_MODEH_MODE9_PUSHPULL;

	/* Pin PC10 is configured to Push-pull */
	GPIO->P[2].MODEH = (GPIO->P[2].MODEH & ~_GPIO_P_MODEH_MODE10_MASK)
			| GPIO_P_MODEH_MODE10_PUSHPULL;
	// [Port C Configuration]$

	// $[Port D Configuration]

	/* Pin PD0 is configured to Push-pull */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_PUSHPULL;

	/* Pin PD1 is configured to Input enabled */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE1_MASK)
			| GPIO_P_MODEL_MODE1_INPUT;

	/* Pin PD2 is configured to Push-pull */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE2_MASK)
			| GPIO_P_MODEL_MODE2_PUSHPULL;

	/* Pin PD3 is configured to Push-pull */
	GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE3_MASK)
			| GPIO_P_MODEL_MODE3_PUSHPULL;

	/* Pin PD9 is configured to Push-pull */
	GPIO->P[3].MODEH = (GPIO->P[3].MODEH & ~_GPIO_P_MODEH_MODE9_MASK)
			| GPIO_P_MODEH_MODE9_PUSHPULL;

	/* Pin PD10 is configured to Push-pull */
	GPIO->P[3].MODEH = (GPIO->P[3].MODEH & ~_GPIO_P_MODEH_MODE10_MASK)
			| GPIO_P_MODEH_MODE10_PUSHPULL;

	/* Pin PD14 is configured to Open-drain with pull-up and filter */
	GPIO->P[3].MODEH = (GPIO->P[3].MODEH & ~_GPIO_P_MODEH_MODE14_MASK)
			| GPIO_P_MODEH_MODE14_WIREDANDPULLUPFILTER;

	/* Pin PD15 is configured to Open-drain with pull-up and filter */
	GPIO->P[3].MODEH = (GPIO->P[3].MODEH & ~_GPIO_P_MODEH_MODE15_MASK)
			| GPIO_P_MODEH_MODE15_WIREDANDPULLUPFILTER;
	// [Port D Configuration]$

	// $[Port E Configuration]

	/* Pin PE0 is configured to Push-pull */
	GPIO->P[4].MODEL = (GPIO->P[4].MODEL & ~_GPIO_P_MODEL_MODE0_MASK)
			| GPIO_P_MODEL_MODE0_PUSHPULL;

	/* Pin PE1 is configured to Push-pull */
	GPIO->P[4].MODEL = (GPIO->P[4].MODEL & ~_GPIO_P_MODEL_MODE1_MASK)
			| GPIO_P_MODEL_MODE1_PUSHPULL;

	/* Pin PE4 is configured to Push-pull */
	GPIO->P[4].MODEL = (GPIO->P[4].MODEL & ~_GPIO_P_MODEL_MODE4_MASK)
			| GPIO_P_MODEL_MODE4_PUSHPULL;

	/* Pin PE5 is configured to Push-pull */
	GPIO->P[4].MODEL = (GPIO->P[4].MODEL & ~_GPIO_P_MODEL_MODE5_MASK)
			| GPIO_P_MODEL_MODE5_PUSHPULL;

	/* Pin PE6 is configured to Push-pull */
	GPIO->P[4].MODEL = (GPIO->P[4].MODEL & ~_GPIO_P_MODEL_MODE6_MASK)
			| GPIO_P_MODEL_MODE6_PUSHPULL;

	/* Pin PE7 is configured to Push-pull */
	GPIO->P[4].MODEL = (GPIO->P[4].MODEL & ~_GPIO_P_MODEL_MODE7_MASK)
			| GPIO_P_MODEL_MODE7_PUSHPULL;

	/* Pin PE8 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE8_MASK)
			| GPIO_P_MODEH_MODE8_PUSHPULL;

	/* Pin PE9 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE9_MASK)
			| GPIO_P_MODEH_MODE9_PUSHPULL;

	/* Pin PE10 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE10_MASK)
			| GPIO_P_MODEH_MODE10_PUSHPULL;

	/* Pin PE11 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE11_MASK)
			| GPIO_P_MODEH_MODE11_PUSHPULL;

	/* Pin PE12 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE12_MASK)
			| GPIO_P_MODEH_MODE12_PUSHPULL;

	/* Pin PE13 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE13_MASK)
			| GPIO_P_MODEH_MODE13_PUSHPULL;

	/* Pin PE14 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE14_MASK)
			| GPIO_P_MODEH_MODE14_PUSHPULL;

	/* Pin PE15 is configured to Push-pull */
	GPIO->P[4].MODEH = (GPIO->P[4].MODEH & ~_GPIO_P_MODEH_MODE15_MASK)
			| GPIO_P_MODEH_MODE15_PUSHPULL;
	// [Port E Configuration]$

	// $[Port F Configuration]

	/* Pin PF5 is configured to Push-pull */
	GPIO->P[5].MODEL = (GPIO->P[5].MODEL & ~_GPIO_P_MODEL_MODE5_MASK)
			| GPIO_P_MODEL_MODE5_PUSHPULL;

	/* Pin PF8 is configured to Push-pull */
	GPIO->P[5].MODEH = (GPIO->P[5].MODEH & ~_GPIO_P_MODEH_MODE8_MASK)
			| GPIO_P_MODEH_MODE8_PUSHPULL;

	/* Pin PF9 is configured to Push-pull */
	GPIO->P[5].MODEH = (GPIO->P[5].MODEH & ~_GPIO_P_MODEH_MODE9_MASK)
			| GPIO_P_MODEH_MODE9_PUSHPULL;
	// [Port F Configuration]$

	// $[Route Configuration]

	/* Module EBI is configured to location 1 */
	EBI->ROUTE = (EBI->ROUTE & ~_EBI_ROUTE_LOCATION_MASK)
			| EBI_ROUTE_LOCATION_LOC1;

	/* Enable signals APEN_A20, ALB_A0, EBI, CS0, CS1 */
	EBI->ROUTE |= EBI_ROUTE_APEN_A20 | EBI_ROUTE_ALB_A0 | EBI_ROUTE_EBIPEN
			| EBI_ROUTE_CS0PEN | EBI_ROUTE_CS1PEN;

	/* Module I2C0 is configured to location 3 */
	I2C0->ROUTE = (I2C0->ROUTE & ~_I2C_ROUTE_LOCATION_MASK)
			| I2C_ROUTE_LOCATION_LOC3;

	/* Enable signals SCL, SDA */
	I2C0->ROUTE |= I2C_ROUTE_SCLPEN | I2C_ROUTE_SDAPEN;

	/* Module PCNT0 is configured to location 1 */
	PCNT0->ROUTE = (PCNT0->ROUTE & ~_PCNT_ROUTE_LOCATION_MASK)
			| PCNT_ROUTE_LOCATION_LOC1;

	/* Module USART0 is configured to location 4 */
	USART0->ROUTE = (USART0->ROUTE & ~_USART_ROUTE_LOCATION_MASK)
			| USART_ROUTE_LOCATION_LOC4;

	/* Enable signals CLK, CS, RX, TX */
	USART0->ROUTE |= USART_ROUTE_CLKPEN | USART_ROUTE_CSPEN | USART_ROUTE_RXPEN
			| USART_ROUTE_TXPEN;

	/* Module USART1 is configured to location 1 */
	USART1->ROUTE = (USART1->ROUTE & ~_USART_ROUTE_LOCATION_MASK)
			| USART_ROUTE_LOCATION_LOC1;

	/* Enable signals CLK, CS, RX, TX */
	USART1->ROUTE |= USART_ROUTE_CLKPEN | USART_ROUTE_CSPEN | USART_ROUTE_RXPEN
			| USART_ROUTE_TXPEN;

	/* Enable signals CLK, CS, RX, TX */
	USART2->ROUTE |= USART_ROUTE_CLKPEN | USART_ROUTE_CSPEN | USART_ROUTE_RXPEN
			| USART_ROUTE_TXPEN;
	// [Route Configuration]$

}

