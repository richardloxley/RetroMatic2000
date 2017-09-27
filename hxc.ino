
#define BUTTON_DOWN_MILLI	145
#define BUTTON_UP_MILLI		85

#define CLICKS_BEFORE_CONTINOUS_MODE		5
#define TIMEOUT_FOR_CONTINOUS_MODE_MILLI	500
#define TIMEOUT_TO_RESET_CLICK_ERRORS_MILLI	5000

void setUpHxc()
{
	// input mode so they float
	pinMode(PIN_HXC_BUTTON_LEFT, INPUT);
	pinMode(PIN_HXC_BUTTON_RIGHT, INPUT);

	// low so that when we set them to output they'll be pulled to ground
	digitalWrite(PIN_HXC_BUTTON_LEFT, LOW);
	digitalWrite(PIN_HXC_BUTTON_RIGHT, LOW);
}

void hxcLeft()
{
	pinMode(PIN_HXC_BUTTON_LEFT, OUTPUT);
	delay(BUTTON_DOWN_MILLI);
	pinMode(PIN_HXC_BUTTON_LEFT, INPUT);
	delay(BUTTON_UP_MILLI);
}

void hxcRight()
{
	pinMode(PIN_HXC_BUTTON_RIGHT, OUTPUT);
	delay(BUTTON_DOWN_MILLI);
	pinMode(PIN_HXC_BUTTON_RIGHT, INPUT);
	delay(BUTTON_UP_MILLI);
}

void hxcLeftContinuous()
{
	pinMode(PIN_HXC_BUTTON_LEFT, OUTPUT);
}

void hxcRightContinuous()
{
	pinMode(PIN_HXC_BUTTON_RIGHT, OUTPUT);
}

void hxcStop()
{
	pinMode(PIN_HXC_BUTTON_LEFT, INPUT);
	pinMode(PIN_HXC_BUTTON_RIGHT, INPUT);
}

void handleHxcInput()
{
	static int previousPos = 0;
	static unsigned long lastMovementTime = 0;
	static bool movingLeft = false;
	static bool movingRight = false;
	static int bufferedMovement = 0;

	unsigned long now = millis();

	int rotaryEncoderPosition = getRotaryEncoderPosition2();
	
	if (rotaryEncoderPosition != previousPos)
	{
		//Serial.println("moved");

		lastMovementTime = millis();

		if ((movingLeft && rotaryEncoderPosition > previousPos) ||
			(movingRight && rotaryEncoderPosition < previousPos))
		{
			//Serial.println("reversed - stopping");
			hxcStop();
			movingLeft = false;
			movingRight = false;
		}

		if (!movingLeft && !movingRight)
		{
			bufferedMovement += (rotaryEncoderPosition - previousPos);
		}
		//Serial.print("bufferedMovement = ");
		//Serial.println(bufferedMovement);
	}
	else if ((movingLeft || movingRight) && (now > lastMovementTime + TIMEOUT_FOR_CONTINOUS_MODE_MILLI))
	{
		//Serial.println("timeout - stopping");
		hxcStop();
		movingLeft = false;
		movingRight = false;
	}
	else if (now > lastMovementTime + TIMEOUT_TO_RESET_CLICK_ERRORS_MILLI)
	{
		// reset to zero to re-align "clicks" due to encoder errors
		bufferedMovement = 0;
	}
	
	int wholeClicks = bufferedMovement / 4;

	if (wholeClicks > CLICKS_BEFORE_CONTINOUS_MODE)
	{
		// start continuous mode (right)
		movingRight = true;
		bufferedMovement = 0;
		hxcRightContinuous();
		//Serial.println("start continous (right)");
		//Serial.print("bufferedMovement = ");
		//Serial.println(bufferedMovement);
	}
	else if (wholeClicks < -CLICKS_BEFORE_CONTINOUS_MODE)
	{
		// start continuous mode (left)
		movingLeft = true;
		bufferedMovement = 0;
		hxcLeftContinuous();
		//Serial.println("start continous (left)");
		//Serial.print("bufferedMovement = ");
		//Serial.println(bufferedMovement);
	}
	else if (wholeClicks >= 1)
	{
		// one click right
		hxcRight();
		bufferedMovement -= 4;
		//Serial.println("click (right)");
		//Serial.print("bufferedMovement = ");
		//Serial.println(bufferedMovement);
	}
	else if (wholeClicks <= -1)
	{
		// one click left
		hxcLeft();
		bufferedMovement += 4;
		//Serial.println("click (left)");
		//Serial.print("bufferedMovement = ");
		//Serial.println(bufferedMovement);
	}

	previousPos = rotaryEncoderPosition;
}


