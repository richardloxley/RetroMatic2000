#include "Globals.h"

void setup()
{
	Serial.begin(115200);
	setUpLcd();
	setUpSounds();
	setUpMenu();
	setUpRotaryEncoder();
	setUpHxc();
	setUpVideoBoard();
	setUpScanlines();
}

void loop()
{
	handleHxcInput();
	handleMenu();
	handleSounds();
}


