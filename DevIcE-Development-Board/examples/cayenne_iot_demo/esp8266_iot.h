
#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include <Wire.h>
#define master_adr 0
#define atmega_adr 1

int dan, mjesec, sat, minuta, sekunde;

byte i2c_data[12];
int pwm_data[6];

Adafruit_MCP23017 mcp1;


void esp8266_iot_init()
{
    mcp1.begin(0);
    Wire.begin(master_adr);
  
}

void i2c_read()
{

    Wire.requestFrom(atmega_adr, 6); // request 2 bytes from slave device #8

    while (Wire.available()) { //check if data is available
        for (byte i = 0; i < 6; i++) {
            i2c_data[i] = Wire.read(); // it assigne the data to the array
        }
    }
}


 float adc_read(int pin)
{

    i2c_read();
    float val =  i2c_data[(pin - 1)];
    return val;
}

unsigned int IO_read(int pin)
{
    int x;
    int state;
  

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
              Wire.beginTransmission(1);
              Wire.write(vals,6);
              Wire.endTransmission();
  }

void pwm_write(int pin,int val){
  
  pin = pin-1;
  pwm_data[pin] = val;
  send_pwm();

  
  }



