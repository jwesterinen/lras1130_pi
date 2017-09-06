/*
 *  Class: WirePi
 *
 *  Description:
 *    A RPi replacement for the Arduino WirePi library.
 *
 */

#ifndef __WIRE_H
#define __WIRE_H

class WirePi
{
public:
	WirePi() : fd(-1), writeBufferIdx(0), readBufferIdx(0)
	{}
	~WirePi()
	{}

	// Initiate the WirePi library and join the I2C bus as a master or slave.
	void begin();

	// Begin a transmission to the I2C slave device with the given address. 
	// Subsequently, queue bytes for transmission with the write() function 
	// and transmit them by calling endTransmission().
	void beginTransmission(uint8_t i2cAddress);

	// Writes data from a slave device in response to a request from a 
	// master, or queues bytes for transmission from a master to slave 
	// device (in-between calls to beginTransmission() and endTransmission()). 
	// Returns a byte, the number of bytes written.
	uint8_t write(uint8_t dataByte);

	// Ends a transmission to a slave device that was begun by 
	// beginTransmission() and transmits the bytes that were queued by write(). 
	// Returns a byte, the status of the transmission, success = 0.
	uint8_t endTransmission();

	// Used by the master to request bytes from a slave device. The bytes 
	// may then be retrieved with the available() and read() functions.
	// Returns a byte, the number of bytes returned from the slave device.
	uint8_t requestFrom(unsigned i2cAddress, int count);

	// Returns the number of bytes available for retrieval with read(). This 
	// should be called on a master device after a call to requestFrom() or 
	// on a slave inside the onReceive() handler.
	// 
	uint8_t available();

	// Reads a byte that was transmitted from a slave device to a master 
	// after a call to requestFrom() or was transmitted from a master to a 
	// slave. read() inherits from the Stream utility class.
	// Returns the next byte received.
	uint8_t read();

	// Clears the last write error
	void clearWriteError();

private:
	int fd;
        uint8_t writeBuffer[200];
	int writeBufferIdx;
	uint8_t readBuffer[200];
	int readBufferIdx;

};

#endif // __WIRE_H

#include "Arduino.h"

