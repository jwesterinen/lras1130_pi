#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "serialPi.h"

SerialPi::SerialPi()
{}

void SerialPi::begin(int baudrate)
{}

int SerialPi::print(const char* msg)
{
	return printf("%s", msg);
}

int SerialPi::print(unsigned value, enum Format format)
{
	switch (format)
	{
		case DEC:
			return printf("%d", value);
		case HEX:
			return printf("%x", value);
		case OCT:
			return printf("%o", value);
		default:
			break;
	}
	return 0;
}

int SerialPi::println(const char* msg)
{
	return printf("%s\n", msg);
}

int SerialPi::println(unsigned value, enum Format format)
{
	switch (format)
	{
		case DEC:
			return printf("%d\n", value);
		case HEX:
			return printf("%x\n", value);
		case OCT:
			return printf("%o\n", value);
		default:
			break;
	}
	return 0;
}

void SerialPi::flush()
{}
