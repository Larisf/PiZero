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

unsigned int r = 255;
unsigned int g = 0;
unsigned int b = 255;
unsigned int counter = 0;
int pressed = 0;

void herunterfahren()
{
 if(digitalRead(TASTER) == 0)
{
 int i;
 for(i = 0; i < 11; i++)
 {
  if(digitalRead(TASTER) == 0)
  {
   sleep(1);
   if(i == 10)
    system("sudo shutdown -h now");
  }
  else
   break;
 }
 }
}

void abbruch(int signal)
{
    char buffer[BITS_LED] = {0};
    memset(buffer, 0, sizeof(buffer));
    wiringPiSPIDataRW(0, buffer, sizeof(buffer));
    usleep(1000);
    memset(buffer, 0, sizeof(buffer));
    wiringPiSPIDataRW(1, buffer, sizeof(buffer));
    usleep(1000);
    exit(0);
}
void lauflicht(char *buffer, int size)
{
   int x,y;
      for(x=0; x < size;x+=3)
      {
        buffer[x] = 255;
        buffer[x+1] = 0;
        buffer[x+2] = 255;
        wiringPiSPIDataRW(1, buffer, size);
        usleep(WAIT);
        if(counter != 0)
        break;
      }

      for(y = size; y >= 0; y-=3)
      {
        buffer[y] = 255;
        buffer[y+1] = 0;
        buffer[y+2] = 255;
        wiringPiSPIDataRW(1, buffer, size);
        usleep(WAIT);
        if(counter != 0)
        break;
      }
}
void geschaltet(char *buffer, int size)
{
int i;
         switch(counter)
      {
      case 1: //Rot
       memset(buffer, 0, size);
       for (i = 0; i < size; i+=3)
       buffer[i] = 255;

       break;

      case 2: //Gr�n
       memset(buffer, 0, size);
       for (i = 1; i < size; i+=3)
       buffer[i] = 255;
       break;

      case 3: //Blau
       memset(buffer, 0, size);
       for (i = 2; i < size; i+=3)
       buffer[i] = 255;
       break;

      case 4: //wei�
       memset(buffer, 255, size);
       break;

      case 5: //Einstellbar
       memset(buffer, 0, size);
       for (i = 0; i < size; i+=3)
        {
          buffer[i] = r;
          buffer[i+1] = g;
          buffer[i+2] = b;
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

void interrupt_0(void)
{
  if(pressed == 0 && digitalRead(TASTER) == 1)
  {
    pressed = 1;
    wait(0.2);
    counter++;
    printf("%d\n",counter);
  }
}

int main()
{
   char buffer[BITS_LED] = {0};
   signal(SIGINT, abbruch);

   wiringPiSetupGpio();
   piHiPri(99);
   pinMode(TASTER,INPUT);
   if (wiringPiSPISetup(0, 20000) < 0)
   {
      fprintf(stderr, "Error setting up SPI 0\n");
      return -ENOTTY;
   }
   if (wiringPiSPISetup(1, 20000) < 0)
   {
      fprintf(stderr, "Error setting up SPI 1\n");
      return -ENOTTY;
   }
   wiringPiISR (TASTER, INT_EDGE_RISING, interrupt_0) ;

   for(;;)
   {
    if(counter==0)
    {
       lauflicht(buffer, sizeof(buffer));

     }
     else
     {
        geschaltet(buffer, sizeof(buffer));
        wiringPiSPIDataRW(1, buffer, sizeof(buffer));
        pressed = 0;
        usleep(WAIT);
     }
   }
   return 0;
}
