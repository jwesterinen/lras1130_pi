/*
 *    This is the PI Arduino framework.  It includes a main function.
 */

#include <time.h>
#include <cinttypes>
#include "Wire.h"

void setup();
void loop();

/*
 *  RPi version of Arduino random(int n) function that returns a random number
 *  between 0 to (n-1)
 */
uint8_t random(int n)
{
	return (uint8_t)random() % n;
}

// the one and only WirePi and SerialPi objects
WirePi Wire;
SerialPi Serial;

int main(int argc, char** argv)
{
	// seed the random number generator
	srandom(time(NULL));

        setup();
        while (1)
        {
                loop();
        }
}

