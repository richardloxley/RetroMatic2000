
// reading the pins takes too long and can slow down sound effects, so only scan for user input occasionally
#define TIME_BETWEEN_MENU_UPDATES_MILLI		50

void startUpSound()
{
	tone(PIN_SPEAKER, 120, 350);
	delay(450);
	tone(PIN_SPEAKER, 520, 350);
}

void setUpMenu()
{	
	lcd.clear();
	lcd.print("RetroMatic 2000");
	startUpSound();
}

void handleMenu()
{
	static unsigned long lastUpdateTime = 0;

	unsigned long now = millis();

	if (now > lastUpdateTime + TIME_BETWEEN_MENU_UPDATES_MILLI)
	{
	 	static int oldmenu = 0;
		static bool oldclicked = false;
		
		int pos = getRotaryEncoderPosition1();
		int menu = (pos / 4) % 5;
		bool clicked = isClicked1();
		
		if (menu != oldmenu || clicked != oldclicked)
		{
			lcd.setCursor(0, 1);
			
			if (clicked)
			{
				lcd.print("Boo!            ");
				startUpSound();
			}
			else
			{
				switch (menu)
				{
					case 0:
						lcd.print("Scanlines: off  ");
						scanlinesOff();
						scanlinesNarrow();
						scanlinesResolutionOther();
						break;
					case 1:
						lcd.print("Scanlines: norm ");
						scanlinesOn();
						scanlinesNarrow();
						scanlinesResolutionOther();
						break;
					case 2:
						lcd.print("Scanlines: wide ");
						scanlinesOn();
						scanlinesWide();
						scanlinesResolutionOther();
						break;
					case 3:
						lcd.print("Scanlines: norm8");
						scanlinesOn();
						scanlinesNarrow();
						scanlinesResolution800x600();
						break;
					case 4:
						lcd.print("Scanlines: wide8");
						scanlinesOn();
						scanlinesWide();
						scanlinesResolution800x600();
						break;
				}
			}
	
			oldmenu = menu;
			oldclicked = clicked;
		}

		lastUpdateTime = now;
	
	}
}
