#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define actieKnop 3
#define PIN 7

Servo WielL;  // = D3
Servo WielR;  // = D8

Adafruit_NeoPixel pixels(2, PIN, NEO_GRB + NEO_KHZ800);

int Stop = 90;
int Kleur0[] = { 150, 150, 150 };  //wit
int Kleur1[] = { 255, 0, 0 };      //rood

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  WielL.attach(8);
  WielR.attach(4);
  pixels.begin();
  pixels.clear();
  //startPlayback(sample, sizeof(sample));
}

void loop() {// put your main code here, to run repeatedly:

  pixels.setPixelColor(0, pixels.Color(Kleur0[0], Kleur0[1], Kleur0[2]));
  pixels.setPixelColor(1, pixels.Color(Kleur0[0], Kleur0[1], Kleur0[2]));
  pixels.show(); //lampen standaard op wit

  if (digitalRead(actieKnop) == 1) {
    pixels.setPixelColor(0, pixels.Color(Kleur1[0], Kleur1[1], Kleur1[2]));
    pixels.setPixelColor(1, pixels.Color(Kleur1[0], Kleur1[1], Kleur1[2]));
    pixels.show(); //lampen op kleur 1
    
    Serial1.println("kdrv");// rijmodus
    delay(500); //5 seconden delay

    Drive(150); //rijden aaan snelheid (150)
    delay(5000); //5 seconden rijden

    Drive(Stop); //stoppen met rijden
    Serial1.println("ktfm"); //transformeren
    LedBlink(3000, 255, 0, 0, 0, 0, 255); //led blink rood blauw met delay

    Serial1.println("ksxsv"); //67 + dansen
    delay(8000); //8 seconden delay
    delay(1750); //1,75 seconden delay
    Rotate(180); //draaien op locatie
    delay(1750); //1,75 seconden draaien
    Rotate(Stop); //stoppen met draaien
    delay(500); //delay voor beweging rijden

    Serial1.println("kdrv"); //rijpositie
    delay(1000);//tijd voor activatie

    Drive(150); //rijden aan snelheid 150
    delay(5000); //5 seconden rijden

    Drive(Stop); //stoppen met rijden
    delay(1000); //delay 
  }
}



void LedBlink(int delaytijd, int rood1, int groen1, int blauw1, int rood2, int groen2, int blauw2) {  // commando dat leds laat blinken tijdens een bepaalde delayduurtijd(delaytijd, rgb blink 1, rgb blink 2) 
  int fractiedelaytijd = 200;
  for (int i = 0; i <= delaytijd / fractiedelaytijd; i++) {
    pixels.setPixelColor(0, pixels.Color(rood2, groen2, blauw2));
    pixels.setPixelColor(1, pixels.Color(rood1, groen1, blauw1));
    pixels.show();
    delay(fractiedelaytijd / 2);
    pixels.setPixelColor(0, pixels.Color(rood1, groen1, blauw1));
    pixels.setPixelColor(1, pixels.Color(rood2, groen2, blauw2));
    pixels.show();
    delay(fractiedelaytijd / 2);
  }
  pixels.setPixelColor(0, pixels.Color(Kleur1[0], Kleur1[1], Kleur1[2]));
  pixels.setPixelColor(1, pixels.Color(Kleur1[0], Kleur1[1], Kleur1[2]));
  pixels.show();
}

void Drive(int speed) {  // (90 =  stop, <90 = vooruit, >90 = achteruit)
  int inverse = speed - 90;
  WielL.write(speed);
  WielR.write(90 - inverse);
  delay(10);
}

void Rotate(int speed) {// roteerd de robot (wielen draaien in tegengestelde richting)
  WielL.write(speed);
  WielR.write(speed);
  delay(10);
}