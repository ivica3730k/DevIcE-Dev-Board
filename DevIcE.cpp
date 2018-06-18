
#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include <Wire.h>
#include "RTClib.h"
#include "device.h"
#define atmega_adr 10


char buffer[24];

float adc_data[6]; // drzi adc podatke primljene sa atmega chipa
unsigned int pwm_data[6];

Adafruit_MCP23017 mcp1;
RTC_DS1307 rtc;



int godina,mjesec,dan,sat,minuta,sekunda = 0;



void i2c_read()
{
 
  Wire.requestFrom(atmega_adr, 24);
  while (Wire.available())
  {
    for(int i = 0;i<24;i++){
      buffer[i] = Wire.read();
   
      }
  }
  
}


 unsigned int ADC_read(int pin)
{

    i2c_read();

    
char buffer_adc1[4];
buffer_adc1 [0] = buffer[0];
buffer_adc1 [1] = buffer[1];
buffer_adc1 [2] = buffer[2];
buffer_adc1 [3] = buffer[3];
adc_data [0] = *(float *)&buffer_adc1;


char buffer_adc2[4];
int ofset = 4;
buffer_adc2 [0] = buffer[0+ofset];
buffer_adc2 [1] = buffer[1+ofset];
buffer_adc2 [2] = buffer[2+ofset];
buffer_adc2 [3] = buffer[3+ofset];
adc_data [1] = *(float *)&buffer_adc2;

char buffer_adc3[4];
 ofset = 8;
buffer_adc3 [0] = buffer[0+ofset];
buffer_adc3 [1] = buffer[1+ofset];
buffer_adc3 [2] = buffer[2+ofset];
buffer_adc3 [3] = buffer[3+ofset];
adc_data [2] = *(float *)&buffer_adc3;

char buffer_adc4[4];
 ofset = 12;
buffer_adc4 [0] = buffer[0+ofset];
buffer_adc4 [1] = buffer[1+ofset];
buffer_adc4 [2] = buffer[2+ofset];
buffer_adc4 [3] = buffer[3+ofset];
adc_data [3] = *(float *)&buffer_adc4;


char buffer_adc5[4];
 ofset = 16;
buffer_adc5 [0] = buffer[0+ofset];
buffer_adc5 [1] = buffer[1+ofset];
buffer_adc5 [2] = buffer[2+ofset];
buffer_adc5 [3] = buffer[3+ofset];
adc_data [4] = *(float *)&buffer_adc5;

char buffer_adc6[4];
 ofset = 20;
buffer_adc6 [0] = buffer[0+ofset];
buffer_adc6 [1] = buffer[1+ofset];
buffer_adc6 [2] = buffer[2+ofset];
buffer_adc6 [3] = buffer[3+ofset];
adc_data [5] = *(float *)&buffer_adc6;



    unsigned int val =  adc_data[(pin - 1)];
    return val;
}

unsigned int IO_read(int pin)
{
    int x;
    unsigned int state;
  

        if (pin <= 8) {
            x = map(pin, 1, 8, 8, 15);
            mcp1.pinMode(x, INPUT_PULLUP);
            state = mcp1.digitalRead(x);
        }

        if (pin > 8) {
            x = map(pin, 8, 16, 7, 0);
            mcp1.pinMode(x, INPUT_PULLUP);
            state = mcp1.digitalRead(x);
        }

        return (state);
    }


void IO_write(int pin, int state)
{

  
    int x;

   

        if (pin <= 8) {
            x = map(pin, 1, 8, 8, 15);
            mcp1.pinMode(x, OUTPUT);
            mcp1.digitalWrite(x, state);
        }

        if (pin > 8) {
            x = map(pin, 8, 16, 7, 0);
            mcp1.pinMode(x, OUTPUT);
            mcp1.digitalWrite(x, state);
        }
    
}

void send_pwm(){
   byte vals[6] = {pwm_data[0],pwm_data[1],pwm_data[2],pwm_data[3],pwm_data[4],pwm_data[5]};     
              Wire.beginTransmission(atmega_adr);
              Wire.write(vals,6);
              Wire.endTransmission();
  }

void PWM_write(int pin,int val){
  
  pin = pin-1; //uzima pwm vrijednost od korisnika preko esp cipa i salje,preko funkcije send_pwm na atmega chip
  pwm_data[pin] = val;
  send_pwm();

  
  }

void read_time(){
  
    DateTime now = rtc.now();
    godina = now.year();
    mjesec = now.month();
    dan = now.day();
    sat = now.hour();
    minuta = now.minute();
    sekunda = now.second();
  }

String vrati_mjesec(){
    DateTime now = rtc.now();
    int mjesec = now.month();
    String vrati;
    if(mjesec <10){
      vrati += "0";
      vrati += mjesec;
      return(vrati);
      }
      else{
      vrati += mjesec;
      return(vrati);
      }
  }

String vrati_dan(){
    DateTime now = rtc.now();
    int dan = now.day();
    String vrati;
    if(dan <10){
      vrati += "0";
      vrati += dan;
      return(vrati);
      }
      else{
      vrati += dan;
      return(vrati);
      }
  }

String vrati_godinu(){
    DateTime now = rtc.now();
    int godina = now.year();
    String vrati;
    vrati += godina;
    return(vrati);
      }


String vrati_sekunde(){
    DateTime now = rtc.now();
    int sekunda = now.second();
    String vrati;
    if(sekunda <10){
      vrati += "0";
      vrati += sekunda;
      return(vrati);
      }
      else{
      vrati += sekunda;
      return(vrati);
      }
  }

  String vrati_minute(){
    DateTime now = rtc.now();
    int minuta = now.minute();
    String vrati;
    if(minuta <10){
      vrati += "0";
      vrati += minuta;
      return(vrati);
      }
      else{
      vrati += minuta;
      return(vrati);
      }
  }

   String vrati_sate(){
    DateTime now = rtc.now();
    int sati = now.hour();
    String vrati;
    if(sati <10){
      vrati += "0";
      vrati += sati;
      return(vrati);
      }
      else{
      vrati += sati;
      return(vrati);
      }
  }


int vrati_sekunde_asInt(){
   DateTime now = rtc.now();
    int sekunda = now.second();
    return sekunda;
  }

  void DevIcE_init(void)
{
  Wire.begin();
  mcp1.begin(0);
  for (int z = 1; z <= 16; z++){
    
    IO_write(z,INPUT_PULLUP);
    
    if(z <= 5){
     PWM_write(z,0);
    }
  }
}
 

  



