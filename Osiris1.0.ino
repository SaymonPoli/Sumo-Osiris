//Bibliotecas
#include <Easyuino.h>
#include <Drive.h>

using Easyuino::DistanceMeter; //Distancia
using Easyuino::DistanceMeterAccurate;// Distancia precisa
using Easyuino::TemperatureScale;//Escala de temperatura

/*
//calibrando motores
int Frente = 1000;
int Virando = 100;
int Recuo = 10;
*/

//Calibrando sensores
int CalInfra = 800;
int distanciaMaxima = 200;
int distanciaMinima = 100;

//Portas dos sensores 
int TriggerFront = 3;
int EchoFront = 2;
int TriggerBack = 13;
int EchoBack = 12;
int Infra = A0;
int InfraT = A1;

//Portas da ponteH
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
Drive drive(IN1, IN2, IN3, IN4);//Setando as saidas para a ponte H

float currentAirTemperature = 20.7f; //temperatura ambiente em °C
DistanceMeterAccurate distanceMeterACC(TriggerFront, EchoFront); //Objeto da API
DistanceMeter distanceMeter(TriggerBack, EchoBack); //Objeto da API

void setup()
{

  Serial.begin(9600);

  //Inicializando a biblioteca dos ultrassonicos 
  distanceMeter.begin();
  distanceMeterACC.begin();

  //definindo pinos
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(Infra, INPUT);
  pinMode(InfraT, INPUT);

  Serial.begin(9600);
}

void loop()
{
   distanceMeter.updateDistance();
   distanceMeterACC.updateDistanceNonBlock(currentAirTemperature, TemperatureScale::CELSIUS);

   float distanciaFrente = distanceMeterACC.getDistanceCentimeters();//retorna a distancia em cm
   float distanciaAtras = distanceMeter.getDistanceCentimeters();//retorna a distancia traseira em cm
   
  
   Serial.print("centimetros Frente: ");
   Serial.print(distanciaFrente);
   Serial.print("   centimetros: ");
   Serial.print(distanciaAtras);
   Serial.print(" Ultra:");   
   Serial.println(analogRead(Infra));

  if (analogRead(Infra) >= CalInfra){
    
    volta();
    
  }
  
  if (float distanciaFrente = distanceMeter.getDistanceCentimeters() <= distanciaMinima){
    
   ataca();
    
  }else if (float distanciaFrente = distanceMeter.getDistanceCentimeters() >= distanciaMaxima){
    
    busca();
    
  }

}

void ataca(){

  distanceMeter.updateDistance();
  distanceMeterACC.updateDistanceNonBlock(currentAirTemperature, TemperatureScale::CELSIUS);

  float distanciaFrente = distanceMeterACC.getDistanceCentimeters();//retorna a distancia em cm
  float distanciaAtras = distanceMeter.getDistanceCentimeters();//retorna a distancia traseira em cm

  do{
    distanceMeter.updateDistance();
    distanceMeterACC.updateDistanceNonBlock(currentAirTemperature, TemperatureScale::CELSIUS);

    drive.moveForward(500);
    
  }while(distanciaFrente < 10);

}

void busca(){
  float distanciaFrente = distanceMeterACC.getDistanceCentimeters();//retorna a distancia em cm
  float distanciaAtras = distanceMeter.getDistanceCentimeters();//retorna a distancia traseira em cm

 
  do{
    distanceMeter.updateDistance();
    distanceMeterACC.updateDistanceNonBlock(currentAirTemperature, TemperatureScale::CELSIUS);

    drive.turnRight(500);
   
  }while(distanciaFrente > 10);

}

void volta(){ //Ta caindo

  drive.moveBackward(500);

  delay(1000);  

  drive.turnRight(500);

  drive.moveForward(500);
  
  Serial.println("Volta");

}//Não ta mais

void Esquivo(){

  drive.moveForward(500);
  drive.turnLeft(100);

}
