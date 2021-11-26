/*
 * I2C.h
 *
 *  Created on: May 21, 2020
 *      Author: jack
 *
 *  This is a C++ wrapper for wiringPiI2C.  The only thing that is kept
 *  in instances of I2C is the device identifier.
 *
 *  In that by being entirely in a header file, optimization on code using
 *  it should be able to be extensive.
 */

#ifndef I2C_H_
#define I2C_H_

#include "wiringPiI2C.h"

class I2C
{
public:
	/*
	 * Public methods
	 */
	// Constructor
	I2C (void)
	{
		fd       = -1;
	}

	void Init (int newDeviceID)
	{
		fd = wiringPiI2CSetup (newDeviceID);
	}

	int Read (void)
	{
		return wiringPiI2CRead (fd);
	}

	int ReadReg8 (int reg)
	{
		return wiringPiI2CReadReg8 (fd, reg);
	}

	int ReadReg16 (int reg)
	{
		return wiringPiI2CReadReg16 (fd, reg);
	}

	int Write (int data)
	{
		return wiringPiI2CWrite (fd, data);
	}

	int WriteReg8 (int reg, int data)
	{
		return wiringPiI2CWriteReg8 (fd, reg, data);
	}

	int WriteReg16 (int reg, int data)
	{
		return wiringPiI2CWriteReg16 (fd, reg, data);
	}

private:
	/*
	 * Private data
	 */
	int fd;
};

#endif /* I2C_H_ */
