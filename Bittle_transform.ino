#include <Servo.h>

Servo WielL;  // = D4
Servo WielR;  // = D8

int Forward = 120;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  WielL.attach(3);
  WielR.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial1.println("krest");
    delay(1000);
    drive();
    delay(1000);
    stop();
    Serial1.println("kbx");
    delay(5000);
    Serial1.println("krest");
    delay(1000);
    drive();
    delay(1000);
    stop();
    delay(1000);
}

int drive() {
  WielL.write(140);
  WielR.write(140);
}

int stop() {
  WielL.write(90);
  WielR.write(90);
}