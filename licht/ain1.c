//Bit - Value - Comment
//
//15 - 1 - Start Conversion
//
//14:12 - 100 - Singled-ended input AIN0
//
//11:9 - 001 - FS 4.096 to cover the +3.3 supply voltage
//
//8 - 1 - No continuous conversion
//
//7:5 - 000 - 8 SPS
//
//4:2 - 000 - Not relevant
//
//1:0 - 11 - Disable comparator
//Quelle: http://openlabtools.eng.cam.ac.uk/Resources/Datalog/RPi_ADS1115/
//Datenblatt ads1115: https://cdn-shop.adafruit.com/datasheets/ads1115.pdf
#include "ain.h"

#include <stdio.h>

int ain1() {
  int ADS_address = 0x48;   // I2C Bus Adresse --> i2cdetect -y 1
  int I2CFile;
  
  uint8_t writeBuf[3];      // Buffer to store the 3 bytes that we write to the I2C device
  uint8_t readBuf[2];       // 2 byte buffer to store the data read from the I2C device
  
  int16_t val;              // Stores the 16 bit value of our ADC conversion
  
  I2CFile = open("/dev/i2c-1", O_RDWR);     // Open the I2C device
  
  ioctl(I2CFile, I2C_SLAVE, ADS_address);   // Specify the address of the I2C Slave to communicate with
      
  // These three bytes are written to the ADS1115 to set the config register and start a conversion 
  writeBuf[0] = 1;          // This sets the pointer register so that the following two bytes write to the config register
  writeBuf[1] = 0b11010011;       // This sets the 8 MSBs of the config register (bits 15-8) to 11000011
  writeBuf[2] = 0b00000011;       // This sets the 8 LSBs of the config register (bits 7-0) to 00000011
  
  // Initialize the buffer used to read data from the ADS1115 to 0
  readBuf[0]= 0;        
  readBuf[1]= 0;
      
  // Write writeBuf to the ADS1115, the 3 specifies the number of bytes we are writing,
  // this begins a single conversion
  write(I2CFile, writeBuf, 3);  

  // Wait for the conversion to complete, this requires bit 15 to change from 0->1
  while ((readBuf[0] & 0x80) == 0)  // readBuf[0] contains 8 MSBs of config register, AND with 10000000 to select bit 15
  {
      read(I2CFile, readBuf, 2);    // Read the config register into readBuf
  }

  writeBuf[0] = 0;                  // Set pointer register to 0 to read from the conversion register
  write(I2CFile, writeBuf, 1);
  
  read(I2CFile, readBuf, 2);        // Read the contents of the conversion register into readBuf

  val = readBuf[0] << 8 | readBuf[1];   // Combine the two bytes of readBuf into a single 16 bit result
  float val_fin = ((float)val*4.096/32767.0*(255/3.25));
  if(val_fin < 0)
   val_fin = 0;
  if(val_fin > 255)
   val_fin = 255;         
  close(I2CFile);
  return val_fin;

}


