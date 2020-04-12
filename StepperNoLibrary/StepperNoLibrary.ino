int motorPins[] = {8, 9, 10, 11};
int count = 0;
int count2 = 0;
int delayTime = 500;
int potPin = 0;
int potValue = 0;



void setup() {
  Serial.begin (9600);
  for (count = 0; count < 4; count++) { pinMode(motorPins[count], OUTPUT); }
}
 
void moveForward() {
  Serial.println("moveForward");
  if ((count2 == 0) || (count2 == 1)) { count2 = 16; } count2>>=1;
  for (count = 3; count >= 0; count--) {
    digitalWrite(motorPins[count], count2>>count&0x01);
  }
  delay(delayTime);
}

void moveBackward() {
  Serial.println("moveBackward");
  if ((count2 == 0) || (count2 == 1)) {
    count2 = 16;
  }
  count2>>=1;
  for (count = 3; count >= 0; count--) {
    digitalWrite(motorPins[3 - count], count2>>count&0x01);
  }
  delay(delayTime);
}

void loop() {
 potValue = analogRead(potPin);
 Serial.println("Loop");
 Serial.print(potValue);
 if (potValue > 540) {
    // move faster the higher the value from the potentiometer
    delayTime = 2048 - 1024 * potValue / 512 + 1;
    moveForward();
  } else if (potValue < 480) {
    // move faster the lower the value from the potentiometer
    delayTime = 1024 * potValue / 512 + 1;
    moveBackward();
  } else {
    delayTime = 1024;
  }
}