#include <DevIcE.h>

void setup() {
  // put your setup code here, to run once:
  DevIcE_init();//init. the board
  pinMode(Q2,OUTPUT); //set pin q2 as output,remember 3V3 ONLY!!!
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(Q2,LOW); 
}
