//Farbcodes: https://www.mediaevent.de/tutorial/farbcodes.html
#include "led.h"
void lauflicht(char *buffer, int size)
{
   int i, dimm;
   dimm = ain3();
      for(i=0; i < size;i+=3)
      {
        buffer[i] = 255-dimm;
        buffer[i+1] = 0;
        buffer[i+2] = 255-dimm;
        wiringPiSPIDataRW(1, buffer, size);
        usleep(WAIT);
        if(counter != 0)
        break;
      }

      for(i = size; i >= 0; i-=3)
      {
        buffer[i] = 255-dimm;
        buffer[i+1] = 0;
        buffer[i+2] = 255-dimm;
        wiringPiSPIDataRW(1, buffer, size);
        usleep(WAIT);
        if(counter != 0)
        break;
      }
}
void geschaltet(char *buffer, int size)
{
int i,r,g,b, dimm;
dimm = ain3();
         switch(counter)
      {
      case 1: //Rot
       memset(buffer, 0, size);
       for (i = 0; i < size; i+=3)
       buffer[i] = 255-dimm;

       break;

      case 2: //Grün
       memset(buffer, 0, size);
       for (i = 1; i < size; i+=3)
       buffer[i] = 255-dimm;
       break;

      case 3: //Blau
       memset(buffer, 0, size);
       for (i = 2; i < size; i+=3)
       buffer[i] = 255-dimm;
       break;

      case 4: //weiß
       memset(buffer, 255-dimm, size);
       break;

      case 5: //Einstellbar
       r = ain0();
       g = ain1();
       b = ain2();
       memset(buffer, 0, size);
       for (i = 0; i < size; i+=3)
        {
          buffer[i] = r-dimm;
          buffer[i+1] = g-dimm;
          buffer[i+2] = b-dimm;
        }
       break;

      case 6: //Aus
       memset(buffer, 0, size);
       usleep(WAIT);
       break;

      default:
       counter = 0;
       pressed = 0;
       break;
      }
}
