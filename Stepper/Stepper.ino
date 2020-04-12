
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int potPin = 0;
int potValue = 0;
int x = 0;


void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(potPin);
  x = map(potValue,0,1024,1000,2000);
  // step one revolution  in one direction:
  Serial.println("clockwise");
  Serial.println(x);
  myStepper.step(x);
  delay(500);
  

  potValue = analogRead(potPin);
  x = map(potValue,0,1024,1000,2000);
  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  Serial.println(x);
  myStepper.step(-x);
  delay(500);
}