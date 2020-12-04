
#include<Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor


// initialize the stepper library on pins 8 through 11:
Stepper stepperX(stepsPerRevolution, 4, 5, 6, 7);
Stepper stepperY(stepsPerRevolution, 8, 9, 10, 11);
int x, y;
static int xpos = 0, ypos = 0;
void setup() {
  // put your setup code here, to run once:
  stepperX.setSpeed(60);
  stepperY.setSpeed(60);
  pinMode(3, INPUT); //For X
  pinMode(2, INPUT); //For Y
  Serial.begin(9600);
  Serial.println("Ready to Start:");
  input();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  for (int i = 0; i < x; i++) {
    stepperX.step(-1);
  }
  for (int i = 0; i < y; i++) {
    stepperY.step(-1);
  }
  input();
  delay(3000);
  if (x == -1 && y == -1) {
    Serial.println("bitch");
    home();
    Serial.println("bitchin");
  }

}
void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}

void input() {
  Serial.println();
  Serial.println("Input:");
  serialFlush();
  while (Serial.available() <= 0) {
  }
  if (Serial.available() > 0) {
    delay(500);
    x = Serial.parseFloat();
    Serial.print("X:");
    Serial.println(x);
    serialFlush();
  }
  while (Serial.available() <= 0) {
  }
  if (Serial.available() > 0) {
    delay(500);
    y = Serial.parseFloat();
    Serial.print("Y:");
    Serial.println(y);
  }

}

void home() {
  while(true){
  if (digitalRead(3) == LOW && digitalRead(2) == LOW) {
    stepperX.step(1);
    stepperY.step(1);
  }
  if (!digitalRead(3) == HIGH && digitalRead(2) == HIGH) {
    stepperX.step(1);
  }
  if (!digitalRead(2) == HIGH && digitalRead(3) == HIGH) {
    stepperY.step(1);
  }
  if (digitalRead(3) == HIGH && digitalRead(2) == HIGH) {
    Serial.println("done");
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    break;
  }    
  
  }
}
