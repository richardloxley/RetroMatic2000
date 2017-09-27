
void setUpScanlines()
{
	pinMode(PIN_SCANLINE_ACTIVATE, OUTPUT);
	pinMode(PIN_SCANLINE_WIDTH, OUTPUT);
	pinMode(PIN_SCANLINE_RESOLUTION, OUTPUT);

	scanlinesOff();
	scanlinesNarrow();
	scanlinesResolutionOther();
}

void scanlinesOff()
{
	digitalWrite(PIN_SCANLINE_ACTIVATE, LOW);
}

void scanlinesOn()
{
	digitalWrite(PIN_SCANLINE_ACTIVATE, HIGH);
}

void scanlinesNarrow()
{
	digitalWrite(PIN_SCANLINE_WIDTH, LOW);
}

void scanlinesWide()
{
	digitalWrite(PIN_SCANLINE_WIDTH, HIGH);
}

void scanlinesResolutionOther()
{
	digitalWrite(PIN_SCANLINE_RESOLUTION, HIGH);
}

void scanlinesResolution800x600()
{
	digitalWrite(PIN_SCANLINE_RESOLUTION, LOW);
}
