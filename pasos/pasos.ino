int motor[] = {7,6,5,4};
int pasos = 512;
int Direction = 0;
int tiempo_espera = 11;
int medioPasoSec[8][4] = {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,1,1},{0,0,0,1},{1,0,0,1}};
void setup()
{
Serial.begin(9600);
pinMode(motor[0], OUTPUT);
pinMode(motor[1], OUTPUT);
pinMode(motor[2], OUTPUT);
pinMode(motor[3], OUTPUT);
// delay(1000);
}
void loop()
{
  pasoSimple();
  apagarMotor();
  delay(4000);
  pasoDoble();
  apagarMotor();
  delay(4000);
  medioPaso();
  apagarMotor();
  delay(4000);
}
void pasoSimple(int sent){
  if(sent == 1){
    for(int i = 0 ; i < pasos ; i ++){
    apagarMotor();
    for(short j = 0 ; j < 4 ; j++){
        if(j == 0) digitalWrite(motor[j],1);
        else{
          digitalWrite(motor[j],1);
          digitalWrite(motor[j-1],0);
        }
        delay(tiempo_espera);
    }
  }
    }
  
}

void pasoDoble(){
  for(int i = 0 ; i < pasos ; i++){
    apagarMotor();
    for(int j = 0 ; j < 4 ; j++){
      if(j == 3){
        digitalWrite(motor[j],1);
        digitalWrite(motor[0],1);
        digitalWrite(motor[2],0);
        delay(tiempo_espera);
        break;
      }
      if(j > 0){
        digitalWrite(motor[j-1],0);
      }
      digitalWrite(motor[j],1);
      digitalWrite(motor[j+1],1);
      delay(tiempo_espera);
    }
  }
}

void medioPaso(){
  for(int i = 0 ; i < pasos ; i++){
    apagarMotor();
      for(int j = 0 ; j < 8 ; j++){
        for(int k = 0 ; k < 4 ; k++){
          digitalWrite(motor[k],medioPasoSec[j][k]);
        }
        delay(tiempo_espera);
    }
  }
}

void apagarMotor(){
  for(int i = 0 ; i < 4 ; i++)
    digitalWrite(motor[i],0);
}
