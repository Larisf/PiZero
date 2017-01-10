#ifndef LED_H_
#define LED_H_

//Eigene Klassen
#include "switch.h"

//Globale Variablen
extern unsigned int r;
extern unsigned int g;
extern unsigned int b;

//Methoden
void lauflicht(char *buffer, int size);
void geschaltet(char *buffer, int size);
#endif

