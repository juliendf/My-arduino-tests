/*
 This class uses the VariableTimedAction library to emulate a clock. 
*/

// VariableTimedAction - Version: Latest 
#include <VariableTimedAction.h>

class Counter : public VariableTimedAction {
private:
  int count = 0;
  //this method will be called at your specified interval
  unsigned long run() {
    //increase the timer
    Serial.println("counter1");
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
    Serial.println("counter2");
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
 
  secondCounter.start(1000);
  secondCounter2.start(500);

}

void loop() {
  
  //check if any actions must be executed
  VariableTimedAction::updateActions();
}