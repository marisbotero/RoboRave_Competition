#include<Servo.h>
#include <Exbot.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
int IRPIN=10; //sensor de la compuerta
int Vel=200;//0-255
int VG=200;

int VelFirst=200;    //Primera Vez 200
int VGFirst=200;    //Primera Vez 200

int VelRegreso=200;
int VGRegreso=200;

int TiempoPuertas=5900000000; //Variable para el tiempo

int TiempoFirst=100;  //Variable para el tiempo la primera vez 11000
int TiempoElResto=100; //Variable para en las otras trayectorias 11000

int UmbralLinea=124;  //296
int UmbralLateral=280;//0-2000
int Swt=11;



int T=0;
int State=0;
int MotorPelotas=8;
Servo myservo;
int FlagAtras=0; 
unsigned long Tiempo=0;
ZumoReflectanceSensorArray reflectanceSensors;

// Define an array for holding sensor values.
#define NUM_SENSORS 6
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
   
    pinMode(MotorPelotas,OUTPUT);
    reflectanceSensors.init();
    
    pinMode(Swt,INPUT);
    digitalWrite(Swt,HIGH);//HIGH
    
    //IniciarSensoresLinea(); //Invierte el sentido de los ADC
   
  //   unsigned char emitterPin = ZUMO_SENSOR_ARRAY_DEFAULT_EMITTER_PIN;
  //  unsigned char sensorPins[] = { A5, A4, A3, A2, A1, A0 };
  //  reflectanceSensors.init(sensorPins, sizeof(sensorPins), 2000, emitterPin);
   
   Serial.begin(9600);
  
   myservo.attach(9); //sto era 9
   myservo.write(0);  //esto era 180
   
  if(digitalRead(Swt)==HIGH){ //Swt ==HIGH
  
    Vel=VelFirst;  //Primera vez
    VG=VGFirst;    //Primera vez
    
  }else{
    //Deje las velocidades iguales
  } 
   
}

void loop()
{
  
  reflectanceSensors.read(sensorValues);

  for (byte i = 0; i < NUM_SENSORS; i++)
  {
   Serial.print(sensorValues[i]);
   Serial.print("\t");
  }
  Serial.println("");
  
 
 
 //Detección de T1 y T2.
 if(ExisteT(UmbralLinea)){
 //Se ha detectado la T entonces se debe avanzar un poco hacia adelante 
Parar(0); //Se para el Robot
//Se toma una decisión de acuerdo a si es la primera o la segunda T
 switch(T){
     case 0:
     Parar(100);
      TDerecha(UmbralLinea,VG,130);
    //  T=1;
     break;

     case 2:
      YIzquierda(UmbralLinea, VG,300);
     //T=3;
     break;
 }
 
 }

//------Detector de Torre
if(digitalRead(IRPIN)==LOW){  //LOW
    if(State==0){
    //Depositar un Ping-Pong
      
         if(digitalRead(Swt)==HIGH){ //HIGH
          TiempoPuertas=TiempoFirst;  //Primera vez      
        }else{
          TiempoPuertas=TiempoElResto;
        } 
            
      
      Parar(0);
      
       myservo.write(70); //esto era 70
      digitalWrite(MotorPelotas,HIGH);
      Tiempo=millis();
      
      
      
      
      while(millis()-Tiempo<TiempoPuertas){
         //Adelante(255,255,50);
         //Atras(255,255,50);
      }
      myservo.write(180);  //este era 180
      digitalWrite(MotorPelotas,LOW);//Este era LOW
      Parar(0);
      
      GiroHaciaAtras(UmbralLinea,Vel,300);
      VG=VGRegreso;
      Vel=VelRegreso;     
    }else{
    //Depositar todos las pelotas.
    myservo.write(90); //este era 90
    digitalWrite(MotorPelotas,HIGH);
    delay(100);
    }
   
  FlagAtras=1; 
  T=2; 
}

//---------Fin Torre---------


//Seguir Linea 
//SeguidordeLinea(UmbralLinea,Vel);
//SeguidordeLineaCentrales(200,Vel);
// reflectanceSensors.read(sensorValues);
SeguidorLinea4Sensores(UmbralLateral,UmbralLinea,Vel);
//Seguir Linea--------------  
  
}
//Seguidor de Linea

//Funciones 
void SeguidordeLinea(int Umbral, int Vel){
  if (sensorValues[1]>Umbral)
  {
    Izquierda(Vel,Vel,1);
  }
  else if (sensorValues[4]>Umbral)//lo cambie era 4
  {
    Derecha(Vel,Vel,1);     
  }
  else
  {
    Adelante(Vel,Vel,1);
  } 

}

void SeguidorLinea4Sensores(int UmbralLateral,int UmbralCentral, int Vel){
  if(sensorValues[0]>284){  //este valor cambia
    Atras(Vel,Vel,80);
    Izquierda(Vel,Vel,110);
  }else  if(sensorValues[5]>284){ //este valor cambia
    Atras(Vel,Vel,80);
    Derecha(Vel,Vel,110);
  }
   else if (sensorValues[0]>UmbralLateral || sensorValues[1]>UmbralCentral)
  {
    Izquierda(Vel,Vel,1);
  }
  else if (sensorValues[5]>UmbralLateral || sensorValues[4]>UmbralCentral)
  {
    Derecha(Vel,Vel,1);     
  }
  else
  {
    Adelante(Vel,Vel,1);
  } 
  
}


void SeguidorLinea6Sensores(int UmbralLateral,int UmbralCentral, int Vel){
  if(sensorValues[0]>UmbralCentral){
    Atras(Vel,Vel,80);
    Izquierda(Vel,Vel,110);
  }else if(sensorValues[5]>UmbralCentral){
    Atras(Vel,Vel,80);
    Derecha(Vel,Vel,120);
  }else
  if(sensorValues[1]>284){ //se cambia
    Atras(Vel,Vel,80);
    Izquierda(Vel,Vel,110);
  }else  if(sensorValues[4]>284){ //se cambia
    Atras(Vel,Vel,80);
    Derecha(Vel,Vel,110);
  }
   else if (sensorValues[1]>UmbralLateral || sensorValues[2]>UmbralCentral)
  {
    Izquierda(Vel,Vel,1);
  }
  else if (sensorValues[4]>UmbralLateral || sensorValues[3]>UmbralCentral)
  {
    Derecha(Vel,Vel,1);     
  }
  else
  {
    Adelante(Vel,Vel,1);
  } 
  
}


void SeguidordeLineaCentrales(int Umbral, int Vel){
  if (sensorValues[2]>Umbral)
  {
    Izquierda(Vel,Vel,1);
  }
  else if (sensorValues[4]>Umbral) // aca estaba el 3
  {
    Derecha(Vel,Vel,1);     
  }
  else
  {
    Adelante(Vel,Vel,1);
  } 

}

void GiroHaciaAtras(int Umbral,int Vel,int del){
     Parar(0);    
     Atras(Vel,Vel,del);
     while(sensorValues[5]>Umbral){
     reflectanceSensors.read(sensorValues);
     };
     //Giro
     Izquierda(Vel,Vel,10);
     while(sensorValues[5]<Umbral){
     reflectanceSensors.read(sensorValues);
     };
     while(sensorValues[5]>Umbral){
     reflectanceSensors.read(sensorValues);
     };
      while(sensorValues[4]<Umbral){
     reflectanceSensors.read(sensorValues);
     }
}
//          -------
//             |
//             |
void TIzquierda(int Umbral,int Vel,int del){
 Adelante(Vel,Vel,del);
 reflectanceSensors.read(sensorValues);
 Izquierda(Vel,Vel,20);
 while(sensorValues[3]<Umbral&&sensorValues[4]<Umbral&&sensorValues[5]<Umbral){
 reflectanceSensors.read(sensorValues);
 }
 Parar(del);
 
}
//          -------
//             |
//             |
void TDerecha(int Umbral,int Vel,int del){

    Adelante(Vel,Vel,del);
    reflectanceSensors.read(sensorValues);
    Derecha(Vel,Vel,20);
    while(sensorValues[2]<Umbral&&sensorValues[1]<Umbral&&sensorValues[0]<Umbral){
    reflectanceSensors.read(sensorValues);
 }
 Parar(del);
}

//             |
//             ----
//             |

void YIzquierda(int Umbral, int Vel, int del){
 Adelante(Vel,Vel,del);
 while(sensorValues[0]>Umbral){
 reflectanceSensors.read(sensorValues);
 };
 //Giro
 Izquierda(Vel,Vel,10);
 while(sensorValues[0]<Umbral){
 reflectanceSensors.read(sensorValues);
 };
 while(sensorValues[0]>Umbral){
 reflectanceSensors.read(sensorValues);
 };
  while(sensorValues[2]<Umbral&&sensorValues[1]<Umbral&&sensorValues[0]<Umbral){
 reflectanceSensors.read(sensorValues);
 }

}

void YDerecha(int Umbral, int Vel, int del){

 Adelante(Vel,Vel,del);
 while(sensorValues[5]>124){ //se  cambia
 reflectanceSensors.read(sensorValues);
 };
 //Giro
 Derecha(Vel,Vel,10);
 while(sensorValues[5]<124){ //se  cambia
 reflectanceSensors.read(sensorValues);
 };
 while(sensorValues[5]>124){  //se cambia
 reflectanceSensors.read(sensorValues);
 };
  while(sensorValues[3]<Umbral&&sensorValues[4]<Umbral&&sensorValues[5]<Umbral){
 reflectanceSensors.read(sensorValues);
 }
}

void IniciarSensoresLinea(){
 
  unsigned char emitterPin = ZUMO_SENSOR_ARRAY_DEFAULT_EMITTER_PIN;
 unsigned char sensorPins[] = { A5, A4, A3, A2, A1, A0 };
 reflectanceSensors.init(sensorPins, sizeof(sensorPins), 2000, emitterPin);
 
}

byte ExisteT(int Umbral){
//Condiciones de T
  if( 
      sensorValues[0]>Umbral&&sensorValues[1]>Umbral||
      sensorValues[0]>Umbral&&sensorValues[2]>Umbral||
      sensorValues[0]>Umbral&&sensorValues[3]>Umbral||
      sensorValues[0]>Umbral&&sensorValues[4]>Umbral||
      
      sensorValues[0]>Umbral&&sensorValues[5]>Umbral||
      
      sensorValues[5]>Umbral&&sensorValues[1]>Umbral||
      sensorValues[5]>Umbral&&sensorValues[2]>Umbral||
      sensorValues[5]>Umbral&&sensorValues[3]>Umbral||
      sensorValues[5]>Umbral&&sensorValues[4]>Umbral
      
  ){
  return 1;
  }else{
   return 0;
  }

}

