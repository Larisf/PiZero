#ifndef AIN_H_
#define AIN_H_

#include "main.h"

#include <fcntl.h>     // open
#include <inttypes.h>  // uint8_t, etc
#include <linux/i2c-dev.h> // I2C bus definitions

int ain0();
int ain1();
int ain2();
int ain3();

#endif
