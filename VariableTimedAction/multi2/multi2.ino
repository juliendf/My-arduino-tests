/*
 This class uses the VariableTimedAction library to emulate a clock. 
*/

// VariableTimedAction - Version: Latest 
#include <VariableTimedAction.h>

// include the library
#include <Unistep2.h>

// Define some steppers and the pins they will use
Unistep2 stepperX(8, 9, 10, 11, 4096, 1000); // pins for IN1, IN2, IN3, IN4, steps per rev, step delay(in micros)


const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor


int potPin = 0;
int potValue = 0;
int x = 0;


class Counter : public VariableTimedAction {
private:
  int count = 0;
  int var = 0;
  //this method will be called at your specified interval
  unsigned long run() {
    //increase the timer
    Serial.println("clockwise");
    stepperX.run();

    while (var < 1000) {
      Serial.println("toto");
      stepperX.move(1000);
      var++;
    }
    Serial.println("counterclockwise");

    count++;
    //return code of 0 indicates no change to the interval; if the interval must be changed, then return the new interval
    return 0;
  }

public:
  int getCount() {
    return count;
  }
};
Counter secondCounter;


class Counter2 : public VariableTimedAction {
private:
  int count = 0;
  //this method will be called at your specified interval
  unsigned long run() {
    //increase the timer
    Serial.print("Reading pot : ");
    potValue = analogRead(potPin);
    x = map(potValue,0,1024,1000,2000);
    Serial.println(x);
    count++;
    //return code of 0 indicates no change to the interval; if the interval must be changed, then return the new interval
    return 0;
  }

public:
  int getCount() {
    return count;
  }
};
Counter2 secondCounter2;


void setup() {
  Serial.begin (9600);
  //call the run method every 1000ms (or 1 sec)

   // set the speed at 60 rpm:
  secondCounter.start(5000);
  secondCounter2.start(100);

}

void loop() {
  
  //check if any actions must be executed
  VariableTimedAction::updateActions();
}