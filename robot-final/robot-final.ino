/********************************************************************************************
*********************************************************************************************
Lab 3
April 8, 2024
Prathiba
Cheryl
Salvador
This code will combine the dc motor code and fft code we've been working on
to make a two wheeled robot move around a trash can
and make the robot stop when it detects a certain peak frequency
and make the robot start when it detects another specific peak frequency
*********************************************************************************************
*********************************************************************************************/
// including to use object detecting sensor
#include "SR04.h"
// Goes to control of motor connected to robot's front facing left wheel
#define ENABLE_LEFT_WHEEL 5
// DIR_A LOW and DIR_B HIGH makes wheel move forward, use opposite logic to move backward
#define DIR_A 3
#define DIR_B 4
// Goes to control of motor connected to robot's front facing right wheel
#define ENABLE_RIGHT_WHEEL 8
// DIR_C LOW and DIR_D HIGH makes wheel move forward, use opposite logic to move backward
#define DIR_C 6
#define DIR_D 7

// used for object detecting and measuring distance from object
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

long a;
int i;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE_LEFT_WHEEL, OUTPUT);
  pinMode(ENABLE_RIGHT_WHEEL, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  pinMode(DIR_C, OUTPUT);
  pinMode(DIR_D, OUTPUT);
  Serial.begin(9600);
}

// both motors 100% duty cycle
void motor_duty_cycle_100() {
  analogWrite(ENABLE_LEFT_WHEEL, 255);
  analogWrite(ENABLE_RIGHT_WHEEL, 255);
}

// both motors 75% duty cycle
void motor_duty_cycle_75() {
  analogWrite(ENABLE_LEFT_WHEEL, 190);
  analogWrite(ENABLE_RIGHT_WHEEL, 190);
}

// both motors 50% duty cycle
void motor_duty_cycle_50() {
  analogWrite(ENABLE_LEFT_WHEEL, 127);
  analogWrite(ENABLE_RIGHT_WHEEL, 127);
}

// both motors 25% duty cycle
void motor_duty_cycle_25() {
  analogWrite(ENABLE_LEFT_WHEEL, 64);
  analogWrite(ENABLE_RIGHT_WHEEL, 64);
}

// left motor 100% duty cycle, right motor 25% duty cycle
void motor_duty_cycle_100_25() {
  analogWrite(ENABLE_LEFT_WHEEL, 255);
  analogWrite(ENABLE_RIGHT_WHEEL, 64);
}

// left motor 100% duty cycle, right motor 50% duty cycle
void motor_duty_cycle_100_50() {
  analogWrite(ENABLE_LEFT_WHEEL, 255);
  analogWrite(ENABLE_RIGHT_WHEEL, 127);
}

// left motor 100% duty cycle, right motor 75% duty cycle
void motor_duty_cycle_100_75() {
  analogWrite(ENABLE_LEFT_WHEEL, 255);
  analogWrite(ENABLE_RIGHT_WHEEL, 190);
}

// left motor 25% duty cycle, right motor 100% duty cycle
void motor_duty_cycle_25_100() {
  analogWrite(ENABLE_LEFT_WHEEL, 64);
  analogWrite(ENABLE_RIGHT_WHEEL, 255);
}

// left motor 50% duty cycle, right motor 100% duty cycle
void motor_duty_cycle_50_100() {
  analogWrite(ENABLE_LEFT_WHEEL, 127);
  analogWrite(ENABLE_RIGHT_WHEEL, 255);
}

// left motor 75% duty cycle, right motor 100% duty cycle
void motor_duty_cycle_75_100() {
  analogWrite(ENABLE_LEFT_WHEEL, 190);
  analogWrite(ENABLE_RIGHT_WHEEL, 255);
}

// right wheel will go cw and left wheel will go ccw
void wheels_forward() {
  digitalWrite(DIR_A, LOW);
  digitalWrite(DIR_B, HIGH);
  digitalWrite(DIR_C, LOW);
  digitalWrite(DIR_D, HIGH);
}

// right wheel will go ccw and left wheel will cw
void wheels_reverse() {
  digitalWrite(DIR_A, HIGH);
  digitalWrite(DIR_B, LOW);
  digitalWrite(DIR_C, HIGH);
  digitalWrite(DIR_D, LOW);
}

// both wheels will go cw
void wheels_clockwise() {
  digitalWrite(DIR_A, HIGH);
  digitalWrite(DIR_B, LOW);
  digitalWrite(DIR_C, LOW);
  digitalWrite(DIR_D, HIGH);
}

// both wheels will go ccw
void wheels_counter_clockwise() {
  digitalWrite(DIR_A, LOW);
  digitalWrite(DIR_B, HIGH);
  digitalWrite(DIR_C, HIGH);
  digitalWrite(DIR_D, LOW);
}

// robot will move forward at the predetermined acceptable speeds
void car_forward(int duty_cycle) {
  switch (duty_cycle) {
    case 100:
      // full power forward
      motor_duty_cycle_100();
      wheels_forward();
    case 75:
      // 3/4 power forward
      motor_duty_cycle_75();
      wheels_forward();
    case 50:
      // 1/2 power forward
      motor_duty_cycle_50();
      wheels_forward();
    case 25:
    // full speed forward
      motor_duty_cycle_25();
      wheels_forward();
  }
}

// car will move backward at the predetermined acceptable speeds
void car_reverse(int duty_cycle) {
  switch (duty_cycle) {
    case 100:
      // full power forward
      motor_duty_cycle_100();
      wheels_reverse();
    case 75:
      // 3/4 power forward
      motor_duty_cycle_75();
      wheels_reverse();
    case 50:
      // 1/2 power forward
      motor_duty_cycle_50();
      wheels_reverse();
    case 25:
    // full speed forward
      motor_duty_cycle_25();
      wheels_reverse();
  }
}

// car will stop by forcing logic out pins to motor drivers low
 void car_stop(){
  digitalWrite(DIR_A,LOW);
  digitalWrite(DIR_B,LOW);
  digitalWrite(DIR_C,LOW);
  digitalWrite(DIR_D,LOW);
}

// both wheels move forward, and they can move at diffeerent speeds to cause tilt with different duty cycles
// you can also move the car forward with not tilt and at different speeds by using the same duty cycle for both ints
void car_forward_tilt (int left_duty_cycle, int right_duty_cycle) {
  if (left_duty_cycle >= 0 && left_duty_cycle <= 255 && right_duty_cycle >= 0 && right_duty_cycle <= 255) {
    analogWrite(ENABLE_LEFT_WHEEL, left_duty_cycle);
    analogWrite(ENABLE_RIGHT_WHEEL, right_duty_cycle);
    wheels_forward();
  }
}

// both wheels move backward, and they can move at diffeerent speeds to cause tilt with different duty cycles
// you can also move the car backward with not tilt and at different speeds by using the same duty cycle for both ints
void car_backward_tilt (int left_duty_cycle, int right_duty_cycle) {
  if (left_duty_cycle >= 0 && left_duty_cycle <= 255 && right_duty_cycle >= 0 && right_duty_cycle <= 255) {
    analogWrite(ENABLE_LEFT_WHEEL, left_duty_cycle);
    analogWrite(ENABLE_RIGHT_WHEEL, right_duty_cycle);
    wheels_reverse();
  }
}

// wheels move clockwise at given duty cycles to turn robot left 
void car_turn_left (int left_duty_cycle, int right_duty_cycle) {
  if (left_duty_cycle >= 0 && left_duty_cycle <= 255 && right_duty_cycle >= 0 && right_duty_cycle <= 255) {
    analogWrite(ENABLE_LEFT_WHEEL, left_duty_cycle);
    analogWrite(ENABLE_RIGHT_WHEEL, right_duty_cycle);
    wheels_clockwise();
  }
}

// wheels move counter clockwise at given duty cycles to turn robot right 
void car_turn_right (int left_duty_cycle, int right_duty_cycle) {
  if (left_duty_cycle >= 0 && left_duty_cycle <= 255 && right_duty_cycle >= 0 && right_duty_cycle <= 255) {
    analogWrite(ENABLE_LEFT_WHEEL, left_duty_cycle);
    analogWrite(ENABLE_RIGHT_WHEEL, right_duty_cycle);
    wheels_counter_clockwise();
  }
}

void distance_measurement() {
  a=sr04.Distance();
  Serial.print(a);
  Serial.println("cm");
  delay(1000);
  }

void loop() {

// TODO
// a finite state machine that constantly is checkinf distance from object and adjusting car and or individual wheel speeds to adjust and keep close to object
// detect two specific frequencies to start and stop car
// detect certain distances to finely adjust wheel speeds to stay within a range of object distance

}


 
   

