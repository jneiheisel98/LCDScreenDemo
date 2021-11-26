/*
 * LCD.h
 *
 *  Created on: May 25, 2020
 *      Author: jack
 *
 *  This code is based heavily on the article:
 *
 *	"Control a HD44780 LCD display via I2C with the Raspberry Pi" at
 *
 *  https://tutorials-raspberrypi.com/control-a-raspberry-pi-hd44780-lcd-display-via-i2c/
 */

#ifndef LCD_H_
#define LCD_H_

#include <unistd.h>

#include "I2C.h"

class LCD
{
	/*
	 * Public methods
	 */
public:
	// Constructor
	//
	// Since this is done at load time, little initialization can
	// be done here.
	LCD(void);

	// Run time initialization
	bool Init (int addr);

	// clocks EN to latch command
	void Strobe(int data)
	{
		i2c_Device.Write (data | En | LCD_BACKLIGHT);
		// .0005 secs
		usleep (500);
		i2c_Device.Write ((data & ~En) | LCD_BACKLIGHT);
		// .0001 secs
		usleep (100);
	}


	void WriteFourBits (int data)
	{
		i2c_Device.Write (data | LCD_BACKLIGHT);
		Strobe (data);
	}


	// write a command to LCD
	void Write (int cmd, int mode=0)
	{
		WriteFourBits (mode | (cmd & 0xF0));
		WriteFourBits (mode | ((cmd << 4) & 0xF0));
	}

	// turn on/off the LCD backlight
	void Backlight (bool state)
	{
		if (state)
		{
			i2c_Device.Write (LCD_BACKLIGHT);
		}
		else
		{
			i2c_Device.Write (LCD_NOBACKLIGHT);
		}
	}

	// put string function
	bool DisplayString (char const *string, int line)
	{
		switch (line)
		{
		case 0:		// Leave on current line
			break;

		case 1:
			Write (0x80);
			break;

		case 2:
			Write (0xC0);
			break;

		case 3:
			Write (0x94);
			break;

		case 4:
			Write (0xD4);
			break;

		default:
			return false;
		}

		while (char ch = *string++)
		{
			Write (ch, Rs);
		}

		return true;
	}

	// clear LCD and set to home
	void Clear (void)
	{
		Write (LCD_CLEARDISPLAY);
		Write (LCD_RETURNHOME);
	}

private:
	// commands
	static const int LCD_CLEARDISPLAY = 0x01;
	static const int LCD_RETURNHOME = 0x02;
	static const int LCD_ENTRYMODESET = 0x04;
	static const int LCD_DISPLAYCONTROL = 0x08;
	static const int LCD_CURSORSHIFT = 0x10;
	static const int LCD_FUNCTIONSET = 0x20;
	static const int LCD_SETCGRAMADDR = 0x40;
	static const int LCD_SETDDRAMADDR = 0x80;

	// flags for display entry mode
	static const int LCD_ENTRYRIGHT = 0x00;
	static const int LCD_ENTRYLEFT = 0x02;
	static const int LCD_ENTRYSHIFTINCREMENT = 0x01;
	static const int LCD_ENTRYSHIFTDECREMENT = 0x00;

	// flags for display on/off control
	static const int LCD_DISPLAYON = 0x04;
	static const int LCD_DISPLAYOFF = 0x00;
	static const int LCD_CURSORON = 0x02;
	static const int LCD_CURSOROFF = 0x00;
	static const int LCD_BLINKON = 0x01;
	static const int LCD_BLINKOFF = 0x00;

	// flags for display/cursor shift
	static const int LCD_DISPLAYMOVE = 0x08;
	static const int LCD_CURSORMOVE = 0x00;
	static const int LCD_MOVERIGHT = 0x04;
	static const int LCD_MOVELEFT = 0x00;

	// flags for function set
	static const int LCD_8BITMODE = 0x10;
	static const int LCD_4BITMODE = 0x00;
	static const int LCD_2LINE = 0x08;
	static const int LCD_1LINE = 0x00;
	static const int LCD_5x10DOTS = 0x04;
	static const int LCD_5x8DOTS = 0x00;

	// flags for backlight control
	static const int LCD_BACKLIGHT = 0x08;
	static const int LCD_NOBACKLIGHT = 0x00;

	static const int En = 0b00000100; // Enable bit;
	static const int Rw = 0b00000010; // Read/Write bit;
	static const int Rs = 0b00000001; // Register select bit;

private:
	static const int MSEC_200 = 200*1000;	// In usec

	I2C i2c_Device;
};

// Singleton
extern LCD lcd;

#endif /* LCD_H_ */
