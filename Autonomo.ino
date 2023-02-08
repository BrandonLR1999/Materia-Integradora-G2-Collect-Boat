#define motor1 8 //motor izquierda
#define motor2 7 //motor derecha
#define motor3 10 //banda transportadora
#define pinEco 4
#define pinGatillo 5
#define pinEco2 2
#define pinGatillo2 3
int hcsr01a = 0;
int hcsr01b = 0;
void borde(int hcsr01a, int hcsr01b);
void funcioninterior(int hcsr01a, int hcsr01b);
int contadorBorde=0;

//esta funcion lee distancia
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  Serial.begin(115200);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
}

void loop() {
  //Calculamos la distancia en cm
  hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
  hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
  borde(hcsr01a,hcsr01b);
  funcioninterior(hcsr01a, hcsr01b);
}

void borde(int hcsr01a, int hcsr01b){
  //HIGH AVANCE LOW RETROCESO
  int contadorBorde=0;
  while (contadorBorde<6){
    hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
    hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
    delante();
    while (!((hcsr01a<20)&&(hcsr01b<20))){
      hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
      hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
      delante();
    }
    contadorBorde+=1;
    derecha90();
    hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
    hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
    if ((hcsr01a<20)&&(hcsr01b<20)){
      izquierda180();
      delante();
    }
  }
}


void delante(){//HIGH: giro adelante LOW: giro retroceso
  digitalWrite(motor3,HIGH);
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,HIGH);
}
void derecha90(){
  digitalWrite(motor3,LOW);
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,LOW);
  delay(4000);//gira 90° en 4 segundos
  digitalWrite(motor2,HIGH);
}
void izquierda90(){
  digitalWrite(motor3,LOW);
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,HIGH);
  delay(4000);//gira 90° en 4 segundos
  digitalWrite(motor1,HIGH);
}
void izquierda180(){
  digitalWrite(motor3,LOW);
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,HIGH);
  delay(10000);//gira 180° en 10 segundos
  digitalWrite(motor1,HIGH);
}

void funcioninterior(int hcsr01a, int hcsr01b){
  int contIzquierda = 0;
  int contDerecha = 0;
  int contInterior = 0;
  delante();
  hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
  hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
  while(!((hcsr01a<20)&&(hcsr01b<20))){
    hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
    hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
    delante();
    contIzquierda=0;
  }
  derecha90();
  hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
  hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
  if((hcsr01a<20)&&(hcsr01b<20)){
    if(contIzquierda>0){
      contIzquierda+=1;
      contDerecha=0;
      izquierda180();
    }
    else{
      izquierda180();
    }
    delante();
  }
  else{
    contIzquierda=0;
    contDerecha+=1;
    hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
    hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
    delante();
    delay(5000);
    derecha90();
    hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
    hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
    while(!((hcsr01a<20)&&(hcsr01b<20))&&!(contDerecha>=2)){
      hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
      hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
      contDerecha+=1;//o
      delante();
    }
    izquierda90();
    hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
    hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
    if(((hcsr01a<20)&&(hcsr01b<20))){
      contInterior+=1;
      contDerecha=0;
      izquierda180();
      if(contInterior==2){
        borde(hcsr01a, hcsr01b);
        end;
      }
      else{
        delante();//inicio
      }
    }
    else{
      contIzquierda+=1;
      contDerecha=0;
      delante();
      delay(5000);
      izquierda90();
    }
    hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
    hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
    while (!((hcsr01a<20)&&(hcsr01b<20))&&!(contIzquierda>=2)){
      hcsr01a = 0.01723 * readUltrasonicDistance(pinGatillo, pinEco);
      hcsr01b = 0.01723 * readUltrasonicDistance(pinGatillo2, pinEco2);
      contIzquierda+=1;
      delante();
    }
    derecha90();
  }
}
