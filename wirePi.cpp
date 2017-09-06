/*
 *  WirePi class definitions
 */

#include <unistd.h>
#include <cinttypes>
#include <wiringPiI2C.h>
#include "Wire.h"

//#define DEBUG

void WirePi::begin()
{
	// nothing to do
}

void WirePi::beginTransmission(uint8_t i2cAddress)
{
	if (fd != -1)
	{
		close(fd);
	}
	fd = wiringPiI2CSetup(i2cAddress);
	writeBufferIdx = 0;
}

uint8_t WirePi::write(uint8_t dataByte)
{
	writeBuffer[writeBufferIdx++] = dataByte;

	return writeBufferIdx;
}

uint8_t WirePi::endTransmission()
{
	int i;
	int status;

	if (writeBufferIdx == 1)
	{
		if ((status = wiringPiI2CWrite(fd, writeBuffer[0])) < 0)
		{
			return status;
		}
#ifdef DEBUG
		printf("I2C write: %02x\n", writeBuffer[0]);
#endif
	}
	else
	{
		uint8_t reg = writeBuffer[0];
		for (i = 1; i < writeBufferIdx; i++)
		{
			if ((status = wiringPiI2CWriteReg8(fd, reg++, writeBuffer[i])) < 0)
			{
				return status;
			}
#ifdef DEBUG
			printf("I2C write: %02x %02x\n", reg-1, writeBuffer[i]);
#endif
		}
	}

	return 0;
}

uint8_t WirePi::requestFrom(unsigned i2cAddress, int count)
{
	int i;

	if (fd != -1)
	{
		close(fd);
	}
	fd = wiringPiI2CSetup(i2cAddress);
	readBufferIdx = 0;
	for (i = 0; i < count; i++)
	{
		readBuffer[readBufferIdx++] = wiringPiI2CRead(fd);
#ifdef DEBUG
		printf("I2C read: %02x\n", readBuffer[readBufferIdx-1]);
#endif
	}

	return readBufferIdx;
}

uint8_t WirePi::available()
{
	return readBufferIdx;
}

uint8_t WirePi::read()
{
	readBufferIdx = 0;
	return readBuffer[readBufferIdx++];
}

void WirePi::clearWriteError()
{
}

