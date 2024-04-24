#define ledPin 7

#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);

int state = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing...");
  Serial.println("Waiting for pairing...");

}

void loop() {
  if(Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  if(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
  delay(20);
}