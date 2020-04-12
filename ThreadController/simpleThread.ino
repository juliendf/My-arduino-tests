#include <Thread.h>
#include <ThreadController.h>
#include <Unistep2.h>

int ledPin = 13;
int potPin = 0;
int potValue = 0;
int potValueMap = 0;
int cycle = 0;
static bool clock = true;

// Define some steppers and the pins they will use
Unistep2 stepperX(8, 9, 10, 11, 4096, 900); 

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

//My Thread
Thread myThread = Thread();
//His Thread
Thread hisThread = Thread();
//Blink Led Thread
Thread blinkLedThread = Thread();
//ThreadController, that will be added to controll
ThreadController groupOfThreads = ThreadController();

// callback for myThread
void niceCallback(){

	if (clock == true){
		cycle = potValueMap;
	}
	else {
		cycle = -potValueMap;
	}

	//Serial.print("COOL! I'm running on: ");
	//Serial.println(millis());
	stepperX.run();
	Serial.print("Value currentPosition : ");
	Serial.println(stepperX.currentPosition());
	Serial.print("Value stepsToGo : ");
	Serial.println(stepperX.stepsToGo());
	
 	if ( stepperX.stepsToGo() == 0 ){
    	stepperX.move(cycle);
		clock = !clock;
  	}

}
// callback for hisThread
void boringCallback(){
	stepperX.run();
    potValue = analogRead(potPin);
    potValueMap = map(potValue,0,1024,0,4096);
	Serial.print("Value Potentiometre : ");
    Serial.println(potValueMap);
	

}

// callback for blinkLedThread
void blinkLed(){
	stepperX.run();
	static bool ledStatus = false;
	ledStatus = !ledStatus;
	digitalWrite(ledPin, ledStatus);

}

void setup(){
	Serial.begin(9600);

	pinMode(ledPin, OUTPUT);

	// Configure myThread
	myThread.onRun(niceCallback);
	myThread.setInterval(1);

	// Configure hisThread
	hisThread.onRun(boringCallback);
	hisThread.setInterval(1);
	
	// Configure blinkLedThread
	blinkLedThread.onRun(blinkLed);
	blinkLedThread.setInterval(250);

	// Adds myThread to the controll
	controll.add(&myThread);

	// Adds hisThread and blinkLedThread to groupOfThreads
	groupOfThreads.add(&hisThread);
	groupOfThreads.add(&blinkLedThread);

	// Add groupOfThreads to controll
	controll.add(&groupOfThreads);
	
}

void loop(){
	// run ThreadController
	// this will check every thread inside ThreadController,
	// if it should run. If yes, he will run it;
	controll.run();


}
