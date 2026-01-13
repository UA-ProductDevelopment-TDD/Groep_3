#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define NOTE_B0  31
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

#define actieKnop 3
#define PIN 7
#define buzzerPin 2

Servo WielL;  // = D3
Servo WielR;  // = D8

Adafruit_NeoPixel pixels(10, PIN, NEO_GRB + NEO_KHZ800);

int Stop = 90;
int Kleur0[] = { 150, 150, 150 };  //wit
int Kleur1[] = { 255, 0, 0 };      //rood

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  WielL.attach(8);
  WielR.attach(4);
  Drive(Stop);
  pixels.begin();
  pixels.clear();
  //startPlayback(sample, sizeof(sample));
}

void loop() {// put your main code here, to run repeatedly:

  pixels.setPixelColor(0, pixels.Color(Kleur0[0], Kleur0[1], Kleur0[2]));
  pixels.setPixelColor(9, pixels.Color(Kleur0[0], Kleur0[1], Kleur0[2]));
  pixels.show(); //lampen standaard op wit
  Drive(Stop);

  if (digitalRead(actieKnop) == 1) {
    pixels.setPixelColor(0, pixels.Color(Kleur1[0], Kleur1[1], Kleur1[2]));
    pixels.setPixelColor(9, pixels.Color(Kleur1[0], Kleur1[1], Kleur1[2]));
    pixels.show(); //lampen op kleur 1
    
    Serial1.println("kdrv");// rijmodus
    delay(500); //5 seconden delay
    speelBeep();

    Drive(30); //rijden aaan snelheid (150)
    delay(5000); //5 seconden rijden

    speelBeep();
    Drive(Stop); //stoppen met rijden
    Serial1.println("ktfm"); //transformeren
    speelTransform();
    LedBlink(4500, 255, 0, 0, 0, 0, 255); //led blink rood blauw met delay

    //Serial1.println("ksxsv"); //67 + dansen
    LedBlink(4000, 255, 255, 255, 0, 0, 0);
    //delay(8000); //8 seconden delay
    //delay(1750); //1,75 seconden delay
    //Rotate(0); //draaien op locatie
    speelZesZeven ();
    delay(500); //1,75 seconden delay
    speelZesZeven ();
    delay(500);
    speelZesZeven ();
    delay(500);
    Rotate(Stop); //stoppen met draaien
    delay(500); //delay voor beweging rijden

    Serial1.println("kdrv"); //rijpositie
    delay(1000);//tijd voor activatie

    speelBeep();
    Drive(30); //rijden aan snelheid 150
    delay(5000); //5 seconden rijden

    Drive(Stop); //stoppen met rijden
    delay(1000); //delay 
  }
}



void LedBlink(int delaytijd, int rood1, int groen1, int blauw1, int rood2, int groen2, int blauw2) {  // commando dat leds laat blinken tijdens een bepaalde delayduurtijd(delaytijd, rgb blink 1, rgb blink 2) 
  int fractiedelaytijd = 200;
  for (int i = 0; i <= delaytijd / fractiedelaytijd; i++) {
    pixels.setPixelColor(0, pixels.Color(rood2, groen2, blauw2));
    pixels.setPixelColor(9, pixels.Color(rood1, groen1, blauw1));
    pixels.show();
    delay(fractiedelaytijd / 2);
    pixels.setPixelColor(0, pixels.Color(rood1, groen1, blauw1));
    pixels.setPixelColor(9, pixels.Color(rood2, groen2, blauw2));
    pixels.show();
    delay(fractiedelaytijd / 2);
  }
  pixels.setPixelColor(0, pixels.Color(Kleur1[0], Kleur1[1], Kleur1[2]));
  pixels.setPixelColor(9, pixels.Color(Kleur1[0], Kleur1[1], Kleur1[2]));
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

//__________________________________________Beeper________________________________________________________
void speelLijst(int noten[], int ritmes[], int aantalNoten) {
  for (int i = 0; i < aantalNoten; i++) {
    int duur = 2000 / ritmes[i];
    tone(buzzerPin, noten[i], duur);
    
    int pauze = duur * 1.30;
    delay(pauze);
    noTone(buzzerPin);
  }
}
void speelTransform() {
  int noten[] = { NOTE_C5, NOTE_B5, NOTE_D5 };
  int ritmes[] = { 16, 16, 4 }; 
  int lengte = sizeof(noten) / sizeof(noten[0]);
  
  speelLijst(noten, ritmes, lengte);
}

void speelBack() {
  int noten[] = { NOTE_C5, NOTE_B4, NOTE_D5, NOTE_B4, NOTE_C5};
  int ritmes[] = { 8, 8, 8, 8, 2 }; // Ritme versnelt (2 is langzaam, 16 is snel)
  int lengte = sizeof(noten) / sizeof(noten[0]);
  
  speelLijst(noten, ritmes, lengte);
}

void speelBeep () {
  int noten[] = { NOTE_D3, NOTE_D3};
  int ritmes[] = { 8, 4 }; // Ritme versnelt (2 is langzaam, 16 is snel)
  int lengte = sizeof(noten) / sizeof(noten[0]);
  
  speelLijst(noten, ritmes, lengte);
}

void speelZesZeven () {
  int noten[] = { NOTE_A3, NOTE_A3, NOTE_A3 };
  int ritmes[] = { 4, 6, 6 }; // Ritme versnelt (2 is langzaam, 16 is snel)
  int lengte = sizeof(noten) / sizeof(noten[0]);
  
  speelLijst(noten, ritmes, lengte);
}