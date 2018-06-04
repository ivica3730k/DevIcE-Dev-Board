//include all needed libraries

#include <DevIcE.h>
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>

//cayenne data obtained from dashboard
char ssid[] = "";
char wifiPassword[] = "";

char username[] = "";
char password[] = "";
char clientID[] = "";

long millisa, millisb = 0;

void setup()
{

    DevIcE_init(); //init. the board
    Cayenne.begin(username, password, clientID, ssid, wifiPassword); //start cayenne
    Serial.begin(115200);
}

void loop()
{

    Cayenne.loop();

    millisa = millis();
    if (millisa - millisb >= 500) { //every 0.5s post ADC voltage to dashboard

        float val1 = ADC_read(1) * 5.0 / 255.0;
        float val2 = ADC_read(2) * 5.0 / 255.0;
        float val3 = ADC_read(3) * 5.0 / 255.0;
        float val4 = ADC_read(4) * 5.0 / 255.0;

        Cayenne.virtualWrite(5, val1, TYPE_VOLTAGE, UNIT_VOLTS); // on channel 5
        Cayenne.virtualWrite(6, val2, TYPE_VOLTAGE, UNIT_VOLTS); // 6
        Cayenne.virtualWrite(7, val3, TYPE_VOLTAGE, UNIT_VOLTS); // 7
        Cayenne.virtualWrite(8, val4, TYPE_VOLTAGE, UNIT_VOLTS); // and 8

        millisb = millis();
    }
}

CAYENNE_IN(1)
{ //get the data from channel 1
    int val = getValue.asInt(); //save it to val
    val = val ^ 1; //invert it
    IO_write(1, val); //and send to port IO_1
}

CAYENNE_IN(2)
{
    int val = getValue.asInt();
    val = val ^ 1;
    IO_write(2, val);
}

CAYENNE_IN(3)
{
    int val = getValue.asInt();
    val = val ^ 1;
    IO_write(3, val);
}

CAYENNE_IN(4)
{
    int val = getValue.asInt();
    val = val ^ 1;
    IO_write(4, val);
}

CAYENNE_IN(9) 
{
    int val = getValue.asInt() / 4; //get the val from ch 9
    PWM_write(1, val); //and write it to PWM pin 1
    Serial.println(val);
}

