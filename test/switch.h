#define N_LEDS 8
#define BITS_LED N_LEDS*3
#define TASTER 4
#define WAIT 250000
#define AUS_TASTER 20

unsigned int r = 255;
unsigned int g = 0;
unsigned int b = 255;
unsigned int counter = 0;
int pressed = 0;

void interrupt_0(void);
void abbruch(int signal);
void herunterfahren(void);
#endif
