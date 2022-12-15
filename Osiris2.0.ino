//Bibliotecas
#include <NewPing.h>
#include <Drive.h>

#define SONAR_NUM 2
#define MAX_DISTANCE 200

/*
//calibrando motores
int Frente = 1000;
int Virando = 100;
int Recuo = 10;
*/

//Calibrando sensores
int CalInfra = 800;
int distanciaMaxima = 50;
int distanciaMinima = 20;

//Portas dos sensores 
int TriggerFront = 10;
int EchoFront = 9;
int TriggerBack = 12;
int EchoBack = 11;
int Infra = A2;
int InfraT = A1;

NewPing sonar[SONAR_NUM] = {// Arrey do sensor
  NewPing(10, 9, MAX_DISTANCE), // pinos do trigger, echo, e a distancia máxima
  NewPing (TriggerBack, EchoBack, MAX_DISTANCE)  
};



//Portas da ponte H
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
Drive drive(IN1, IN2, IN3, IN4);//Setando as saidas para a ponte H
   

void setup()
{

  Serial.begin(9600);

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

    Serial.println();
    
    Serial.print("== Centimetros Frente: ");
    Serial.print(sonar[0].ping_cm());
    Serial.print("  |   centimetros: ");
    Serial.print(sonar[1].ping_cm());
    Serial.print("  |   Infra. Frontal: ");
    Serial.print(analogRead(Infra));
    Serial.println("    Loop ==");  
    
  
  if (sonar[0].ping_cm() <= distanciaMinima){
    
   ataca();
    
  }else if (sonar[0].ping_cm() >= distanciaMinima){
    
    busca();
    
  }

}

void ataca(){

  do{
   
   if (analogRead(Infra) <= CalInfra){
    
    volta();
    
  }

    drive.moveForward(1000);
  
    Serial.print("== Centimetros Frente: ");
    Serial.print(sonar[0].ping_cm());
    Serial.print("  |   centimetros: ");
    Serial.print(sonar[1].ping_cm());
    Serial.print("  |   Infra. Frontal: ");
    Serial.print(analogRead(Infra));
    Serial.println("    Ataca ==");    
    
  }while(sonar[0].ping_cm() <= distanciaMinima);

}

void busca(){
  
 
  do{
   if (analogRead(InfraT) <= CalInfra){
    
    voltaT();
    
  }
   if (analogRead(Infra) <= CalInfra){
    
    volta();
    
  }

    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    

    Serial.print("== Centimetros Frente: ");
    Serial.print(sonar[0].ping_cm());
    Serial.print("  |   centimetros: ");
    Serial.print(sonar[1].ping_cm());
    Serial.print("  |   Infra. Frontal: ");
    Serial.print(analogRead(Infra));
    Serial.println("    Busca ==");

  }while(sonar[0].ping_cm() >= distanciaMinima);

}

void volta(){ //Ta caindo

  Serial.println("============Volta==========");
  drive.moveBackward(1000);

  delay(3000);  

  drive.turnRight(1000);
  delay(100);
  drive.moveForward(500);
  
  

}//Não ta mais

void voltaT(){

  do{
    
    drive.moveForward(1000);
    Serial.println(analogRead(InfraT));

    }while(analogRead(InfraT) <= CalInfra);

    

}

void Esquivo(){
  Serial.print("    Esquivo");
  drive.turnLeft(100);
  drive.moveForward(500);
  
}
