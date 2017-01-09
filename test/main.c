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
   wiringPiISR (TASTER, INT_EDGE_FALLING, interrupt_0) ;
   wiringPiISR(AUS_TASTER, INT_EDGE_FALLING, herunterfahren);
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
