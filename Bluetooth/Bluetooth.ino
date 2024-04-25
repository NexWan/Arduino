#define ledPin 8

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

int state = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing...");
  Serial.println("Waiting for pairing...");

  pinMode(ledPin,INPUT);

}

void loop() {
  if(Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  if(mySerial.available()) 
  {
    String ch;
    ch = mySerial.readString();
    ch.trim();
    Serial.println(ch);
    if(ch == "on" || ch == "ON"){
      digitalWrite(ledPin,true);
      mySerial.write("Led prendido");
    }else if(ch == "off" || ch == "OFF"){
      digitalWrite(ledPin,false);
      mySerial.write("Led apagado");
    }
  }
  delay(20);
}