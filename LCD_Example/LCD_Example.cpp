/*
 * LCD_Example.cpp
 *
 *  Created on: May 26, 2020
 *      Author: jack
 *
 *  Simple test code; just write four lines of text.
 */

#include <LCD.h>
#include <I2C.h>
#include <wiringPi.h>

#include "LCD.h"

static const int LCD_ADDR = 0x27;
LCD lcd;

int main(int argc, const char *argv[])
{
    wiringPiSetup();
    lcd.Init (LCD_ADDR);
	lcd.DisplayString("One",   1);
	lcd.DisplayString("Two",   2);
	lcd.DisplayString("Three", 3);
	lcd.DisplayString("Four",  4);

	return 0;
}
