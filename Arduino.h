#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "serialPi.h"

// this filters out the Arduino string formatting
#define F(s) (s)

// transform Arduino random(n) to linux random
uint8_t random(int n);

// transform Arduino delay to linux
#define delay(msec) usleep((msec) * 1000)

// the one and only Serial and Wire objects references
extern WirePi Wire;
extern SerialPi Serial;

