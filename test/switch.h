#ifndef SWITCH_H_
#define SWITCH_H_

//Eigene Klassen
#include "main.h"

//Globale Variablen
extern unsigned int counter;
extern int pressed;

//Methoden
void interrupt_0(void);
void abbruch(int signal);
void herunterfahren(void);
#endif
