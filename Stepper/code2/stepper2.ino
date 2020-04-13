#include <Stepper.h>

const int stepsPerRevolution = 200;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int potPin = 0;
int potValue = 0;
int counter = 0;
#define ledGreen 3
#define ledBlue 2


void setup() {
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop(){
  potValue = analogRead(potPin);
  int speed = map(potValue,0,1024,50,115);
  
  if (speed > 0){
      myStepper.setSpeed(speed);
  }

  if (counter < 500){
    digitalWrite(ledBlue,HIGH); 
    digitalWrite(ledGreen,LOW);    
    myStepper.step(stepsPerRevolution / 100);
    
  } else {
      digitalWrite(ledBlue,LOW); 
      digitalWrite(ledGreen,HIGH);  
      myStepper.step(-stepsPerRevolution / 100);
  }
  if (counter == 0){
      Serial.println("Inspiration en cours");
  } else if (counter == 501){
      Serial.println("expiration en cours");
  }


  if (counter == 1000){
      counter = 0;
  } else {
      counter ++;
  }
}