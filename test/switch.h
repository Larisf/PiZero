#ifndef SWITCH_H_
#define SWITCH_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>


#include "wiringPi.h"
#include "wiringPiSPI.h"

#define N_LEDS 8
#define BITS_LED N_LEDS*3
#define TASTER 4
#define WAIT 250000
#define AUS_TASTER 20

extern unsigned int r;
extern unsigned int g;
extern unsigned int b;
extern unsigned int counter;
extern int pressed;


void interrupt_0(void);
void abbruch(int signal);
void herunterfahren(void);
#endif
