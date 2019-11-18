#include <Wire.h>
long millisa, millisb = 0;
byte pwm_data[6];
float adc1,adc2,adc3,adc4,adc5,adc6;
char buffer [sizeof(adc1+adc2+adc3+adc4+adc5+adc6)];

void setup()

{    
  analogReference(EXTERNAL);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    
    pinMode(A3, INPUT);
    pinMode(A6, INPUT);
    pinMode(A7, INPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
      pinMode(8,OUTPUT);
      //analogWrite(3,127);
    Wire.begin(10);
    Wire.onRequest(reqEvent);
    Serial.begin(9600);
    Wire.onReceive(receiveEvent);
}

void loop(){
  
millisa = millis();
if(millisa-millisb >= 100){

  adc1 = analogRead(A0);
  adc2 =analogRead(A1);
  adc3 =analogRead(A2);
  adc4=analogRead(A3);
  adc5=analogRead(A6);
  adc6=analogRead(A7);



memcpy(&buffer[0],&adc1,sizeof(adc1));
memcpy(&buffer[4],&adc2,sizeof(adc2));

memcpy(&buffer[8],&adc3,sizeof(adc3));
memcpy(&buffer[12],&adc4,sizeof(adc4));


memcpy(&buffer[16],&adc5,sizeof(adc5));
memcpy(&buffer[20],&adc6,sizeof(adc6));

  millisb = millis();
  
  }

}


void reqEvent()
{


  for(int i = 0;i<24;i++){
  Wire.write(buffer[i]);

  }

}

void receiveEvent()
{
    while (Wire.available()) { 
        for (byte i = 0; i < 6; i++) {
            pwm_data[i] = Wire.read(); 
        }
    }
    
analogWrite(3, pwm_data[0]);
analogWrite(5, pwm_data[1]);
analogWrite(6, pwm_data[2]);
analogWrite(9, pwm_data[3]);
analogWrite(10, pwm_data[4]);
analogWrite(11, pwm_data[5]);

}

