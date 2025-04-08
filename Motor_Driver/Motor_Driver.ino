#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <L298NX2.h>
#include <IRremote.hpp>

// POWER MOTOR
int enA = 9;
int in1 = 8;
int in2 = 7;

//int in3 = 8;
//int in4 = 7;
//int enB = 6;

// ENCODER MOTOR
int encA = 2;
int encAA = 3;
//int encB = 18;
//int encBB = 19;

// Internal Position count
int posA = 0;
int posB = 0;

L298NX2 MOTORS(enA, in1, in2, enB, in3, in4);


void setup() {
  Serial.begin(115200);
  
  MOTORS.stop();
  attachInterrupt(digitalPinToInterrupt(encA), readEncoderA, RISING);
  attachInterrupt(digitalPinToInterrupt(encB), readEncoderB, RISING);
  
}


void loop()
{  
  MOTORS.setSpeedA(40);
  MOTORS.setSpeedB(40);

  MOTORS.forward();

  // Alternative method:
  // motors.run(L298N::FORWARD);

  //print the motor status in the serial monitor
  printSomeInfo();

  delay(3000);

  // Stop
  MOTORS.stop();

  // Alternative method:
  // motors.run(L298N::STOP);

  printSomeInfo();

  delay(3000);

  // Change individual speeds
  MOTORS.setSpeedA(0);
  MOTORS.setSpeedB(0);

  // Tell motor A to go back (may depend by your wiring)
  MOTORS.backwardA();

  // Alternative method:
  // motors.runA(L298N::BACKWARD);

  // Tell motor B to go forward (may depend by your wiring)
  MOTORS.backwardB();

  // Alternative method:
  // motors.runB(L298N::FORWARD);

  printSomeInfo();

  delay(3000);

  // Stop
  MOTORS.stop();

  printSomeInfo();

  // Change individual speeds
  MOTORS.setSpeedA(0);
  MOTORS.setSpeedB(0);

  delay(3000);
}

void printSomeInfo()
{
  Serial.print("Motor A is moving = ");
  Serial.print(MOTORS.isMovingA() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(MOTORS.getSpeedA());
  Serial.print("Motor B is moving = ");
  Serial.print(MOTORS.isMovingB() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(MOTORS.getSpeedB());
}

void readEncoderA() {
  int b = digitalRead(encAA);;
  if(b>0){
    posA++;;
  } else {
    posA--;
  }
}

void readEncoderB() {
  int b = digitalRead(encBB);
  if(b>0){
    posB--;
  } else {
    posB++;
  }
}
