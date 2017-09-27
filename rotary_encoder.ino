//
// rotary encoder stuff
//
// Good tutorial on Arduino interrupts here: http://gammon.com.au/interrupts


// save register state (including interrupt state); turn off interrupts; execute code; restore register (including interrupt state)
// http://gammon.com.au/forum/?id=11488&reply=7#reply7
#define MUTEX(code)	{ byte oldSREG = SREG; noInterrupts(); code; SREG = oldSREG; }

volatile byte rotaryEncoderState1 = 0;
volatile int rotaryEncoderErrors1 = 0;
volatile int rotaryEncoderPosition1 = 0;

volatile byte rotaryEncoderState2 = 0;
volatile int rotaryEncoderErrors2 = 0;
volatile int rotaryEncoderPosition2 = 0;

/*
ISR (PCINT0_vect)
{
	// handle pin change interrupt for D8 to D13 here
	// http://gammon.com.au/forum/?id=11488&reply=6#reply6
}

ISR (PCINT1_vect)
{
	// handle pin change interrupt for A0 to A5 here
	// http://gammon.com.au/forum/?id=11488&reply=6#reply6
}
*/

ISR (PCINT2_vect)
{
	// handle pin change interrupt for D0 to D7 here
	// http://gammon.com.au/forum/?id=11488&reply=6#reply6

	byte newState1 = ENCODER_1_GET_PINS;
	byte sum1  = (rotaryEncoderState1 << 2) | newState1; //adding it to the previous encoded value
	
	if (sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011)
	{
		rotaryEncoderPosition1++;
	}
	else if (sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000)
	{
		rotaryEncoderPosition1--;
	}
	else if (sum1 == 0b1100 || sum1 == 0b0110 || sum1 == 0b0011 || sum1 == 0b1001)
	{
		rotaryEncoderErrors1++;
	}
	
	rotaryEncoderState1 = newState1;

	
	byte newState2 = ENCODER_2_GET_PINS;
	byte sum2  = (rotaryEncoderState2 << 2) | newState2; //adding it to the previous encoded value
	
	if (sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011)
	{
		rotaryEncoderPosition2++;
	}
	else if (sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000)
	{
		rotaryEncoderPosition2--;
	}
	else if (sum2 == 0b1100 || sum2 == 0b0110 || sum2 == 0b0011 || sum2 == 0b1001)
	{
		rotaryEncoderErrors2++;
	}
	
	rotaryEncoderState2 = newState2;
}

int getRotaryEncoderPosition1()
{
	int pos;
	MUTEX(pos = rotaryEncoderPosition1)
	return pos;
}

bool isClicked1()
{
	// encoder 1 click is on an analog input only pin
	return (analogRead(PIN_ENCODER_1_CLICK) < 512);
	
	//return (digitalRead(PIN_ENCODER_1_CLICK) == LOW);
}

int getRotaryEncoderPosition2()
{
	int pos;
	MUTEX(pos = rotaryEncoderPosition2)
	return pos;
}

bool isClicked2()
{
	return false;
	// encoder 2 click not currently routed to Arduino
	//return (digitalRead(PIN_ENCODER_2_CLICK) == LOW);
}

void setUpRotaryEncoder()
{
	// set inputs
	pinMode(PIN_ENCODER_1_A, INPUT_PULLUP);
	pinMode(PIN_ENCODER_1_B, INPUT_PULLUP);
	pinMode(PIN_ENCODER_2_A, INPUT_PULLUP);
	pinMode(PIN_ENCODER_2_B, INPUT_PULLUP);
	
	//pinMode(PIN_ENCODER_1_CLICK, INPUT_PULLUP);	// encoder 1 click is on an analog only input
	//pinMode(PIN_ENCODER_2_CLICK, INPUT_PULLUP); 	// encoder 2 click not currently routed to Arduino

	// we're using the Nano's analog-only inputs as digital so want to read the ADC as fast as possible (we don't care about accuracy)
	// digitalRead() is 5us, analogRead() is normally 115us, this code makes analogRead() take only 15us :-)
	
	// set ADC set prescale to 16
	#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
	#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
	sbi(ADCSRA,ADPS2);
	cbi(ADCSRA,ADPS1);
	cbi(ADCSRA,ADPS0);

	// record initial state
	rotaryEncoderState1 = ENCODER_1_GET_PINS;
	rotaryEncoderState2 = ENCODER_2_GET_PINS;

	// set pins we're interested in
	ENCODER_1_PCMSK_GROUP |= bit (ENCODER_1_INTERRUPT_A);
	ENCODER_1_PCMSK_GROUP |= bit (ENCODER_1_INTERRUPT_B);
	ENCODER_2_PCMSK_GROUP |= bit (ENCODER_2_INTERRUPT_A);
	ENCODER_2_PCMSK_GROUP |= bit (ENCODER_2_INTERRUPT_B);	
	
	// clear any outstanding interrupts
	PCIFR |= bit (ENCODER_1_PCIFR_GROUP);
	PCIFR |= bit (ENCODER_2_PCIFR_GROUP);
	
	// enable pin change interrupts for groups
	PCICR |= bit (ENCODER_1_PCICR_GROUP);
	PCICR |= bit (ENCODER_2_PCICR_GROUP);
}
