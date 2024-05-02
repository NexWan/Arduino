#define A 8

void setup() {
  // put your setup code here, to run once:
  pinMode(A,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A,true);
  delay(500);
  digitalWrite(A,false);
  delay(500);
}
