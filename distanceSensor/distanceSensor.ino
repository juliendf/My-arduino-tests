/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 Red POS to Arduino pin 11
 Green POS to Arduino pin 10
 560 ohm resistor to both LED NEG and GRD power rail
 More info at: http://goo.gl/kJ8Gl
 Original code improvements to the Ping sketch sourced from Trollmaker.com
 Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
 */

#define trigPin 13
#define echoPin 12
#define ledRed 11
#define ledGreen 10
#define buzOut 8

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance < 4) {  // This is where the LED On/Off happens
    digitalWrite(ledRed,HIGH); 
    digitalWrite(ledGreen,LOW);
    tone(buzOut,4000,20);
  } else if (distance < 8) {
    digitalWrite(ledRed,HIGH); 
    digitalWrite(ledGreen,LOW);  
    tone(buzOut,3000,20);
  } else if (distance < 12) {
    digitalWrite(ledRed,LOW); 
    digitalWrite(ledGreen,HIGH);  
    tone(buzOut,2000,20);
  } else if (distance < 16) {
    digitalWrite(ledRed,LOW); 
    digitalWrite(ledGreen,HIGH);  
    tone(buzOut,1000,20);
}
  else {
    digitalWrite(ledRed,LOW);
    digitalWrite(ledGreen,HIGH);
    //tone(buzOut,distance,20);
    
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(90);
}
