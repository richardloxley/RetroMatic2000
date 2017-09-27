#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

// pins

// PWM only available on digital pins 3, 5, 6, 9, 10, 11
// A6 and A7 analogue only, cannot be used as digital
// 0 (RX) and 1 (TX) ok to use as inputs if left floating during flash and serial port is not used during use! 1k resistor to USB serial
// 13 has an inline LED whose resistor interferes with input so only use for output

/*
// 1 TX
// *** 0 RX
// reset
// ground
#define PIN_HEAD_STEP				2
#define PIN_DRIVE_SELECT			3
// *** 4
#define PIN_SPEAKER					5
#define PIN_HXC_BUTTON_LEFT			6
#define PIN_HXC_BUTTON_RIGHT		7
#define PIN_ENCODER_1_A				8		// also set encoder 1 macros below
#define PIN_ENCODER_1_B				9		// also set encoder 1 macros below
#define PIN_ENCODER_2_CLICK			10
#define PIN_ENCODER_2_A				11		// also set encoder 2 macros below
#define PIN_ENCODER_2_B				12		// also set encoder 2 macros below
*/

#define PIN_HEAD_STEP				1		// TX (don't use serial - make sure floating during flash) - also set drive macros below
#define PIN_DRIVE_SELECT			0		// RX (don't use serial - make sure floating during flash) - also set drive macros below
// 									reset
//									ground
#define PIN_ENCODER_1_A				2		// also set encoder 1 macros below
#define PIN_ENCODER_1_B				3		// also set encoder 1 macros below
#define PIN_ENCODER_2_A				4		// also set encoder 2 macros below
#define PIN_ENCODER_2_B				5		// also set encoder 2 macros below
#define PIN_SPEAKER					6		// needs to be PWM
#define PIN_LCD_RS					7
#define PIN_LCD_ENABLE				8
#define PIN_LCD_DATA_4				9 
#define PIN_LCD_DATA_5				10
#define PIN_LCD_DATA_6				11
#define PIN_LCD_DATA_7				12

//									vin
//									ground
//									reset
//									5v
#define PIN_ENCODER_1_CLICK			A7		// analog input only (hack ADC frequency for faster reads)
#define PIN_DRIVE_MOTOR				A6		// analog input only (hack ADC frequency for faster reads)
#define PIN_SCANLINE_WIDTH			A5
#define PIN_SCANLINE_RESOLUTION		A4
#define PIN_HXC_BUTTON_LEFT			A3
#define PIN_HXC_BUTTON_RIGHT		A2
#define PIN_I2C_SDA					A1		// also set i2c macros below
#define PIN_I2C_SCL					A0		// also set i2c macros below
//									ref
//									3.3v
#define PIN_SCANLINE_ACTIVATE		13


// drive macros (dependent on PIN_HEAD_STEP and PIN_DRIVE_SELECT)
#define DRIVE_GET_PINS				(PIND & 0b11)				// pins RX0 and TX1 are bits 0 and 1 of PIND

// encoder 1 macros (dependent on PIN_ENCODER_1_A and PIN_ENCODER_1_B)
// http://gammon.com.au/forum/?id=11488&reply=6#reply6
#define ENCODER_1_GET_PINS			((PIND & 0b1100) >> 2)		// pins D2 and D3 are bits 2 and 3 of PIND
#define ENCODER_1_PCMSK_GROUP		PCMSK2						// port D is group 2
#define ENCODER_1_PCIFR_GROUP		PCIF2						// port D is group 2
#define ENCODER_1_PCICR_GROUP		PCIE2						// port D is group 2
#define ENCODER_1_INTERRUPT_A		PCINT18						// pin D2
#define ENCODER_1_INTERRUPT_B		PCINT19						// pin D3

// encoder 2 macros (dependent on PIN_ENCODER_2_A and PIN_ENCODER_2_B)
// http://gammon.com.au/forum/?id=11488&reply=6#reply6
#define ENCODER_2_GET_PINS			((PIND & 0b110000) >> 4) 	// pins D4 and D5 are bits 4 and 5 of PIND
#define ENCODER_2_PCMSK_GROUP		PCMSK2						// port D is group 2
#define ENCODER_2_PCIFR_GROUP		PCIF2						// port D is group 2
#define ENCODER_2_PCICR_GROUP		PCIE2						// port D is group 2
#define ENCODER_2_INTERRUPT_A		PCINT20						// pin D4
#define ENCODER_2_INTERRUPT_B		PCINT21						// pin D5

// i2c macros (dependent on PIN_I2C_SCL and PIN_I2C_SDA)
#define DDR_I2CBB					DDRC						// pins A1 and A0 are port C
#define PORT_I2CBB					PORTC						// pins A1 and A0 are port C
#define PIN_I2CBB					PINC						// pins A1 and A0 are port C
#define SDA_BIT						1							// pin A1 is bit 1 of port C
#define SCL_BIT						0							// pin A0 is bit 0 of port C
