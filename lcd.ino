#include <LiquidCrystal.h>

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_DATA_4, PIN_LCD_DATA_5, PIN_LCD_DATA_6, PIN_LCD_DATA_7);
 
void setUpLcd()
{
	lcd.begin(16, 2);
}
