//www.elegoo.com
//2017.12.12

/************************
Exercise the motor using
the L293D chip
************************/
#include "SR04.h"
#define ENABLE 5  //left wheel
#define EN 8      //right wheel
#define DIRA 3
#define DIRB 4
#define DIRC 6
#define DIRD 7
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
int i;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(EN,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(DIRC,OUTPUT);
  pinMode(DIRD,OUTPUT);
  Serial.begin(9600);
}
void car_reverse_halfspeed(){
  Serial.println("car moving reverse halfspeed");
  analogWrite(ENABLE,180);
  analogWrite(EN,180);
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRC,HIGH); //one way
  digitalWrite(DIRD,LOW);

}
 void carstop(){
  Serial.println("car stopped");
  digitalWrite(DIRA,LOW); //one way
  digitalWrite(DIRB,LOW);
  digitalWrite(DIRC,LOW); //one way
  digitalWrite(DIRD,LOW);
}
void car_moves_right(){
  Serial.println("car moves right");
  analogWrite(ENABLE,250);
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,HIGH);
}
void car_moves_left(){
  Serial.println("car moves left");

  analogWrite(EN,250);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,HIGH);
}
void car_halfspeed_forward(){
  Serial.println("car moving forward halfspeed");
  analogWrite(ENABLE,180);
  analogWrite(EN,180);
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,HIGH);
  digitalWrite(DIRC,LOW);
  digitalWrite(DIRD,HIGH);
 }
void distance_measurement(){
  a=sr04.Distance();
  Serial.print(a);
  Serial.println("cm");
  delay(1000);
  }
  





void loop(){




}


 
   
