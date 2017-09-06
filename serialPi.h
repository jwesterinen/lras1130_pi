#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#ifndef __SERIAL_PI_H
#define __SERIAL_PI_H

enum Format{DEC, HEX, OCT};

class SerialPi
{
public:
	SerialPi();
	void begin(int baudrate);
	int print(const char* msg);
	int print(unsigned value, enum Format format);
	int println(const char* msg);
	int println(unsigned value, enum Format format);
	void flush();
};

#endif //  __SERIAL_PI_H

