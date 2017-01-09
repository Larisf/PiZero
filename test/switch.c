#include "switch.h"
herunterfahren(void)
{
 if(digitalRead(AUS_TASTER) == 0)
{
 int i,aus_counter;
 for(i = 0; i < 11; i++)
 {
  if(digitalRead(AUS_TASTER) == 0)
  {
   sleep(1);
   printf("AUS: %d,\n",i);
   if(i == 10)
   {
    char buffer[BITS_LED] = {0};
    memset(buffer, 0, sizeof(buffer));
    wiringPiSPIDataRW(0, buffer, sizeof(buffer));
    usleep(1000);
    memset(buffer, 0, sizeof(buffer));
    wiringPiSPIDataRW(1, buffer, sizeof(buffer));
    usleep(1000);
    aus_counter = 1;
    wait(1);
    if(aus_counter == 1)
    system("sudo shutdown -h now");
    }
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

void interrupt_0(void)
{
  if(pressed == 0 && digitalRead(TASTER) == 0)
  {
    pressed = 1;
    wait(0.2);
    counter++;
    printf("%d\n",counter);
  }
}
