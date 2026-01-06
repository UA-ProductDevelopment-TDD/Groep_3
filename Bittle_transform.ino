#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define actieKnop 3
#define PIN 7

Servo WielL;  // = D3
Servo WielR;  // = D8

Adafruit_NeoPixel pixels(2, PIN, NEO_GRB + NEO_KHZ800);

int Stop = 90;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  WielL.attach(8);
  WielR.attach(4);
  pixels.begin();
  pixels.clear();
  //startPlayback(sample, sizeof(sample));
}

void loop() {

  pixels.setPixelColor(0, pixels.Color(150, 150, 150));
  pixels.setPixelColor(1, pixels.Color(150, 150, 150));
  pixels.show();

  if (digitalRead(actieKnop) == 1) {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.show();
    // put your main code here, to run repeatedly:
    Serial1.println("kdrv");
    delay(500);
    Drive(150);
    delay(5000);
    Drive(Stop);
    Serial1.println("ktfm");
    delay(3000);
    Serial1.println("ksxsv");

    //voice.say(sp2_DANGER);
    //voice.say(sp4_LOW);
    //voice.say(sp4_BATTERY);

    delay(5000);
    Serial1.println("kdrv");
    delay(500);
    Drive(150);
    delay(5000);
    Drive(Stop);
    delay(1000);
  }
}

void Drive(int speed) {  // (90 =  stop, <90 = vooruit, >90 = achteruit)
  int inverse = speed - 90;
  WielL.write(speed);
  WielR.write(90 - inverse);
  delay(10);
}