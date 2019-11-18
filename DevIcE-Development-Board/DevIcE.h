
#define Q0 D0  
#define Q1 D3
#define Q2 D4 
#define Q3 D5
void DevIcE_init(void);

int vrati_sekunde_asInt(void);

String vrati_sate(void);

String vrati_minute(void);

String vrati_sekunde(void);


String vrati_dan(void);

String vrati_mjesec(void);

String vrati_godinu(void);

void PWM_write(int pin,int val);

unsigned int ADC_read(int pin);

unsigned int IO_read(int pin);

void IO_write(int pin,int val);

