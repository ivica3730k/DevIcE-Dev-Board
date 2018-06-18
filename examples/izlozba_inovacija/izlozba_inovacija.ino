#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DevIcE.h>
#include <Wire.h>
#include <lcd_I2C.h>

LCD_I2C lcd(0x00, 4, 20); //nadji adresu i2c displeja,sa interneta skini i2c scanner, 0x0A i 0x20 su od plocice

char auth[] = "be4f9f7635774e45a208a94427cfd63a";
char ssid[] = "IOT_TSSB"; //ovdje upisi ime i lozinku
char pass[] = "IOT_TSSB2018";
long mila, milb = 0;
int temp, hum = 0;

void setup()
{

    Serial.begin(9600);
    DevIcE_init();
    IO_write(1, HIGH); //releji su invertirani
    IO_write(2, HIGH); //pri paljenju isključi
    IO_write(3, HIGH); //sve kanale
    IO_write(4, HIGH); //na relejima
    Blynk.begin(auth, ssid, pass); //spoji se na cloud
    lcd.clear();
    lcd.print("Spojeno");
}

void loop()
{
    Blynk.run();
    mila = millis();
    if (mila - milb >= 1000) {
        //ovdje pises ono sto zelis da se izvodi svake sekunde

        milb = millis();
    }
}

BLYNK_WRITE(V0)
{ //informaciju na kanalu V0
    //zaprimi u integer
    //invertiraj i pošalji na
    //IO1 priključnicu
    int i = param.asInt();
    String k;
    if (i == 1)
        k += "Ukljuceno";
    else
        k += "Iskljuceno";
    lcd.clear();
    lcd.cursorXY(0, 0);
    lcd.print("Prvo svjetlo je ");
    lcd.print(k);
    IO_write(1, i);
}
BLYNK_WRITE(V1)
{
    int j = param.asInt();
    String k;
    if (j == 1)
        k += "Ukljuceno";
    else
        k += "Iskljuceno";

    lcd.clear();
    lcd.cursorXY(0, 0);
    lcd.print("Drugo svjetlo je ");
    lcd.print(k);
    IO_write(2, j);
}
BLYNK_WRITE(V2)
{
    int i = param.asInt();
    String k;
    if (i == 1)
        k += "Ukljuceno";
    else
        k += "Iskljuceno";
    lcd.clear();
    lcd.cursorXY(0, 0);
    lcd.print("Trece svjetlo je ");
    lcd.print(k);
    IO_write(3, i);
}

BLYNK_WRITE(V3)
{
    int l = param.asInt();
    String k;
    if (l == 1)
        k += "Ukljuceno";
    else
        k += "Iskljuceno";
    lcd.clear();
    lcd.cursorXY(0, 0);
    lcd.print("Cetvrto svjetlo je "); //mozda ces string k morat stavit u 2 red
    lcd.print(k);
    IO_write(4, l);
}

