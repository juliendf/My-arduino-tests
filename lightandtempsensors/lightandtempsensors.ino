#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 pressure;
#define ALTITUDE 1655.0

//Any Arduino pins labeled:  SDA  SCL
//Uno, Redboard, Pro:        A4   A5
//Mega2560, Due:             20   21
//Leonardo:                   2    3

int rainPin = A1;
int tempPin = A0;
int redLED = 5;
int yellowLED = 4;
int greenLED = 3;



const float baselineTemp = 20.0;
int thresholdValue = 500;


void setup() {
  // put your setup code here, to run once:
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  pinMode(rainPin, INPUT);
  Serial.begin(9600);
  Serial.println("REBOOT");
  
  // init barometer capture
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // Is it Raining ?
  // read the input on analog pin 0:
  int rainSensorValue = analogRead(rainPin);
  if(rainSensorValue < thresholdValue){
    Serial.println(" - It's wet");
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
  }
  else {
    Serial.println(" - It's dry");
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  }
  delay(500);

  // what's the temp ?
  int tempSensorValue = analogRead(tempPin);
  //float voltage = (tempSensorValue/1024.0) * 5.0;
  float temp1 = (((tempSensorValue/1024.0) * 5.0) - .5) * 100;
  Serial.println((String)" - Temp1:"+temp1+" deg C);

  //baromter
  char status;
  double temp2;
  // read temp
  status = pressure.startTemperature();
    if (status != 0){
      // Wait for the measurement to complete:
        delay(status);
        status = pressure.getTemperature(temp2);
            if (status != 0){   
              Serial.println((String)" - Temp2:"+temp2+" deg C");
            }
  delay(500);
  }
}
