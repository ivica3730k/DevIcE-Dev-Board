#include <DevIcE.h>

void setup()
{
    // put your setup code here, to run once:
    DevIcE_init();
    Serial.begin(115200);
}

void loop()
{

    for (int i = 1; i <= 6; i++) {
        Serial.print("ADC");
        Serial.print(i);
        Serial.print("==");
        Serial.println(ADC_read(i));
    }
    delay(1000);
    for (int k = 1; k <= 16; k++) {
        Serial.print("IO_");
        Serial.print(k);
        Serial.print("==");
        Serial.println(IO_read(k));
    }

    for (int j = 1; j <= 5; j++) {
        int val = random(0, 255);
        Serial.print("PWM_");
        Serial.print(j);
        Serial.print("==");
        Serial.println(val);
        PWM_write(j, val);
    }

    delay(500);
}
