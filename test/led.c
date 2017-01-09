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

      case 2: //Grün
       memset(buffer, 0, size);
       for (i = 1; i < size; i+=3)
       buffer[i] = 255;
       break;

      case 3: //Blau
       memset(buffer, 0, size);
       for (i = 2; i < size; i+=3)
       buffer[i] = 255;
       break;

      case 4: //weiß
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
