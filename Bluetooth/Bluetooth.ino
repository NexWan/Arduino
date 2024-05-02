#include <SoftwareSerial.h>

#define A 8
#define B 9
#define C 10
#define D 11

int MOTOR[] = {A, B, C, D};
int pasos = 512;
int direction = 0;
#define WAIT 5
int medioPasoSec[8][4] = {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0},
                           {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}};
int pasoSimpleSec[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
int pasoDobleSec[4][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {1, 0, 0, 1}};

SoftwareSerial mySerial(3, 2);
bool showPrompt = true;

int state = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Initializing...");
  Serial.println("Waiting for pairing...");
  mySerial.println("Teclee cualquier letra para comenzar");
  for (int i = 0; i < 4; i++) {
    pinMode(MOTOR[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
  }
  if (mySerial.available()) {
    mySerial.println("Bienvenido!");
    mySerial.println("Introduzca una de las siguientes opciones: \n");
    mySerial.println("1) Paso simple \n 2) Paso simple inverso \n 3) Paso doble \n 4) Paso doble inverso \n 5) Medio paso \n 6) Medio paso inverso");
    String ch;
    ch = mySerial.readString();
    ch.trim();

    // Verificar si ch contiene solo dígitos
    bool esDigito = true;
    for (int i = 0; i < ch.length(); i++) {
      if (!isDigit(ch.charAt(i))) {
        esDigito = false;
        break;
      }
    }

    if (!esDigito) {
      if (showPrompt) mySerial.println("Opcion invalida! \n");
      showPrompt = false;
      return;
    }
    mySerial.println("Su opcion fue: " + ch + "\n");

    // Convertir ch a entero solo si es un número
    int opcion = ch.toInt();
    switch (opcion) {
      case 1:
        pasoSimple(1);
        break;
      case 2:
        pasoSimple(0);
        break;
      case 3:
        pasoDoble(1);
        break;
      case 4:
        pasoDoble(0);
        break;
      case 5:
        medioPaso(1);
        break;
      case 6:
        medioPaso(0);
        break;
      default:
        mySerial.println("Opcion incorrecta!");
    }
    apagarMotor();
  }
  delay(20);
}

void apagarMotor() {
  pinMode(A, LOW);
  pinMode(B, LOW);
  pinMode(C, LOW);
  pinMode(D, LOW);
}

void pasoSimple(int mode){
  if(mode == 1){
    for(int x = 0 ; x < pasos ; x++){
      for(int i = 0 ; i < 4 ; i++){
        apagarMotor();
        for(int j = 0 ; j < 4 ; j++) digitalWrite(MOTOR[j], pasoSimpleSec[i][j]);
        delay(WAIT);
      }
    }
  }else{
    for(int x = 0 ; x < pasos ; x++){
      for(int i = 4 ; i >= 0 ; i--){
        apagarMotor();
        for(int j = 0 ; j < 4 ; j++) digitalWrite(MOTOR[j], pasoSimpleSec[i][j]);
        delay(WAIT);
      }
    }
  }
}

void pasoDoble(int mode){
  if(mode == 1){
    for(int x = 0 ; x < pasos ; x++){
      for(int i = 0 ; i < 4 ; i++){
        apagarMotor();
        for(int j = 0 ; j < 4 ; j++) digitalWrite(MOTOR[j], pasoDobleSec[i][j]);
        delay(WAIT);
      }
    }
  }else{
    for(int x = 0 ; x < pasos ; x++){
      for(int i = 4 ; i >= 0 ; i--){
        apagarMotor();
        for(int j = 0 ; j < 4 ; j++) digitalWrite(MOTOR[j], pasoDobleSec[i][j]);
        delay(WAIT);
      }
    }
  }
}

void medioPaso(int mode){
  if(mode == 1){
    for(int x = 0 ; x < pasos ; x++){
      for(int i = 0 ; i < 8 ; i++){
        apagarMotor();
        for(int j = 0 ; j < 4 ; j++) digitalWrite(MOTOR[j], medioPasoSec[i][j]);
        delay(WAIT);
      }
    }
  }else{
    for(int x = 0 ; x < pasos ; x++){
      for(int i = 8 ; i >= 0 ; i--){
        apagarMotor();
        for(int j = 0 ; j < 4 ; j++) digitalWrite(MOTOR[j], medioPasoSec[i][j]);
        delay(WAIT);
      }
    }
  }
}
