#define PIN A0
#define FULL 7
#define MID 6
#define LOW 5

double val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(PIN);
  val = val * .0048;
  Serial.println(val);
  delay(100);
  if(val > 1.5)
    prenderLed(true,false,false);
  else if(val > 1.2 && val <= 1.5) 
    prenderLed(false,true,false);
  else if(val <= 1.2)
    prenderLed(false,false,true);
}

void prenderLed(bool x1, bool x2, bool x3){
  Serial.println(x1);
  Serial.println(x2);
  Serial.println(x3);
   digitalWrite(FULL,x1);
  digitalWrite(MID,x2);
  digitalWrite(LOW,x3);
}
