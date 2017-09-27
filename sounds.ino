

#define HEAD_STEP_FREQUENCY				50
#define HEAD_STEP_LENGTH				100

void setUpSounds()
{
}

void headStepSound()
{
	tone(PIN_SPEAKER, HEAD_STEP_FREQUENCY, HEAD_STEP_LENGTH);
}

void handleSounds()
{
	// direct memory access for speed and to guarantee both read simultaneously
	byte driveState = DRIVE_GET_PINS;
	static byte lastState = 0;

	// bit 1 is drive select, bit 0 is head-step, low (zero) indicates active
	// make a sound if this drive is starting (or continuing) a head-step (00)
	// also make a sound if this drive has just stopped a head-step (00->01)
	if (driveState == 0b00 || (lastState == 0b00 && driveState == 0b01))
	{
		headStepSound();
	}
	
	lastState = driveState;
}

