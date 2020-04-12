
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int toggleLEDPin =  13;      // the number of the LED pin

const int blinkLEDPin1 =  6;
const int blinkLEDPin2 =  7;
// include the library
#include <Unistep2.h>

// Define some steppers and the pins they will use
Unistep2 stepperX(8, 9, 10, 11, 4096, 1000); // pins for IN1, IN2, IN3, IN4, steps per rev, step delay(in micros)


unsigned long eventInterval = 100;
unsigned long previousTime = 0;



int blinkLEDState1 = LOW;
int blinkLEDState2 = LOW;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

long TimeOn1 = 400;
long TimeOn2 = 800;

long TimeOff1 = TimeOn1;
long TimeOff2 = TimeOn2;

int buttonDebounce = 20;
int ledToggle = LOW;
volatile int buttonFlag=0;
int previousState = HIGH;
unsigned int previousPress;

int cycle = 0;
bool direction = false;


void setup() {
  Serial.begin(9600);
  pinMode(blinkLEDPin1, OUTPUT);      
  pinMode(blinkLEDPin2, OUTPUT);
  pinMode(toggleLEDPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(buttonPin), button_ISR, CHANGE);   
}

void button_ISR()
{
  buttonFlag = 1;
}

void loop() {
  unsigned long currentTime = millis();
  stepperX.run();
  int tour = 200;
  // run every eventInterval time
  if (currentTime - previousTime >= eventInterval){
    Serial.println("ola");
    previousTime = currentTime;
    stepperX.run();

    if (direction == false){
      stepperX.move(tour);
    }
    else {
      stepperX.move(-tour);
    }
  }


 
  if((blinkLEDState1 == HIGH) && (currentTime - previousMillis1 >= TimeOn1))
  {
    stepperX.run();
    blinkLEDState1 = LOW;
    previousMillis1 = currentTime;
    digitalWrite(blinkLEDPin1, blinkLEDState1);
  }
  else if ((blinkLEDState1 == LOW) && (currentTime - previousMillis1 >= TimeOff1))
  {
    stepperX.run();
    blinkLEDState1 = HIGH;
    previousMillis1 = currentTime;
    digitalWrite(blinkLEDPin1, blinkLEDState1);
  }
  
  if((blinkLEDState2 == HIGH) && (currentTime - previousMillis2 >= TimeOn2))
  {
    stepperX.run();
    blinkLEDState2 = LOW;
    previousMillis2 = currentTime;
    digitalWrite(blinkLEDPin2, blinkLEDState2);
  }
  else if ((blinkLEDState2 == LOW) && (currentTime - previousMillis2 >= TimeOff2))
  {
    stepperX.run();
    blinkLEDState2 = HIGH;
    previousMillis2 = currentTime;
    digitalWrite(blinkLEDPin2, blinkLEDState2);
  }
  
  if(buttonFlag==1)
  {
    if((millis() - previousPress) > buttonDebounce && buttonFlag)
    {
      previousPress = millis();

      if(digitalRead(buttonPin) == LOW && previousState == HIGH)
      {
        ledToggle =! ledToggle;
        digitalWrite(toggleLEDPin, ledToggle);
        previousState = LOW;
        direction =! direction;
        cycle++;
        Serial.println(cycle);
      }
      else if(digitalRead(buttonPin) == HIGH && previousState == LOW)
      {
        previousState = HIGH;
      }
      buttonFlag = 0;
    }
  }
}