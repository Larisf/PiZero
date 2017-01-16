#ifndef MAIN_H_
#define MAIN_H_

//System
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>


//WiringPi
#include "wiringPi.h"
#include "wiringPiSPI.h"

//Eigene Klassen
#include "switch.h"

//Definitionen
#define N_LEDS 8
#define BITS_LED N_LEDS*3
#define TASTER 4
#define WAIT 250000
#define AUS_TASTER 20

#endif
