
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);// RS,E,D4,D5,D6,D7

#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7);
SoftwareSerial esp(3, 4);

unsigned int HighByte = 0;
unsigned int LowByte  = 0;
unsigned int Len  = 0;
int l, load;
void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  delay(500);
  lcd.begin(16, 2);// LCD 16X2
  lcd.print("Load Measurement");
}

void loop()
{
  mySerial.begin(9600);
  mySerial.flush();
  mySerial.write(0X55);                           // trig US-100 begin to measure the distance
  delay(500);                                  
  if (mySerial.available() >= 2)                  // check receive 2 bytes correctly
  {
    HighByte = mySerial.read();
    LowByte  = mySerial.read();
    Len  = HighByte * 256 + LowByte;          // Calculate the distance
    l = Len;
  }
  lcd.clear();
  lcd.print("Dist=");
  lcd.print(Len);
  lcd.print("mm");
  if(l >=178)
  {
    load = 0;
  }
  if(l < 178 && l >= 165)
  {
    load = 5;
  }
  if(l < 165 && l >= 155)
  {
    load = 10;
  }
  if(l < 155 && l >= 150)
  {
    load = 15;
  }
  if(l < 150 && l >= 145)
  {
    load = 25;
  }
  if(l < 145 && l >= 140)
  {
    load = 35;
  }
  lcd.setCursor(0, 1);
  lcd.print("Load: ");
  lcd.print(load);
  lcd.print("Kg");
  if(l< 140)
  {
    lcd.setCursor(0, 1);
    lcd.print("Over Load");
  }
  if(l> 178)
  {
    lcd.setCursor(0, 1);
    lcd.print("No Load");
  }
  delay(100);
  Serial.println(load);
  esp.begin(9600);
  delay(500);
  esp.println(load);
  delay(200);
  
}
