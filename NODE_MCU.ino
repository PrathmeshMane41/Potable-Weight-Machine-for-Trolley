#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "iPhone";            // your network SSID (name)
const char* password = "09876543";  // your network password

WiFiClient client;

unsigned long myChannelNumber = 2499607;
const char* myWriteAPIKey = "E99808BXIASNTEVT";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

int temp = 0;
int i = 0;
char str[5];

float te, tmp;
float l;


String t;

void setup() {
  Serial.begin(9600);  //Initialize serial
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  if ((millis() - lastTime) > timerDelay) {
    // Connect or reconnect to WiFi
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect");
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(5000);
      }
      Serial.println("\nConnected.");
    }
    ThingSpeak.setField(1, l);
    
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
    if (x == 200) {
      Serial.println("Channel update successful.");
    } else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}


void serialEvent() 
{
  while (Serial.available() == 0) 
  {
    if (Serial.find("T"));
  }
  String teststr = Serial.readString();  //read until timeout
  tmp = teststr.toDouble();

    l = tmp;
}
