/*
 * LCD.cpp
 *
 *  Created on: May 25, 2020
 *      Author: jack
 */


#include "LCD.h"

LCD::LCD (void)
{
}

bool LCD::Init (int addr)
{
	i2c_Device.Init(addr);
	Write (0x03);
	Write (0x03);
	Write (0x03);
	Write (0x02);

    Write (LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
    Write (LCD_DISPLAYCONTROL | LCD_DISPLAYON);
    Write (LCD_CLEARDISPLAY);
    Write (LCD_ENTRYMODESET | LCD_ENTRYLEFT);

    // Delay for .2 secs
    usleep (MSEC_200);

    return true;
}



