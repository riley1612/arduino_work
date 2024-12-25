#ifndef DISPLAYCONTROL_H
#define peripherals_H
 #include<arduino.h>

#define NOTE_E5 659
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_E7 2637
#define NOTE_E7 2637
#define NOTE_E7 2637
#define NOTE_C7 2093
#define NOTE_E7 2637
#define NOTE_G7 3136
#define NOTE_G6 1568
#define NOTE_E6 1319
#define NOTE_C6 1047
#define NOTE_G6 1568
#define NOTE_G5 784

const char* ssid = "I LOVE YOU MALLORY";
const char* password = "pass";

unsigned long lastT;
unsigned long currT;
unsigned long time1;
unsigned long startT;
unsigned long delayTime = random(1000, 5000);
unsigned long startTime;
unsigned long debounceTime = 50; 
unsigned long lastDebounceTime = 0;
unsigned long reactionTime;
unsigned long trackerC;
unsigned long trackerP;
unsigned long best=200;
unsigned long toneStart;
const int tone1 = 400;  // C4
const int tone2 = 500;  // E4
const int tone3 = 600;  // G4
int changeButton=13;
int buzzer=5;  //5
int motor;
int led =15;
int greenLed=21;
int blueLed=23;
int redLed=22;
int setMode;
int dt = 50;
int buttonPin = 2;
int step=0;
int circle;
int flag;
int lastState = 3;
int changeMode=0;
int buttonState;
int pinA = 25;int pinB = 12;int pinC = 17;int pinD = 18;
int pinE = 19;int pinF = 26;int pinG = 16;
int pinDP;int D1 = 27;int D2 = 33;int D3 = 0; int D4 = 14;
unsigned long changeStart = 0;
int rands = random(2000,3000);
int toneone=502;
int tonetwo=500;
int oS;



int noteDurations[] = {
  150, 150, 300, 100, 150, 350, 300 
};

int melody[] = {
  NOTE_E6, NOTE_E6, NOTE_E6, NOTE_C6, NOTE_E6, NOTE_G6, NOTE_G5
};


volatile bool change = false;
bool isTrialComplete = false;  
bool running = false;
bool goMode= false;
bool reactRan=0;
bool timeToWait = true;
bool timeForANewLoop = true;
bool ledOn = false;
bool choice;
bool correct;

//
    void zero() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
  }

  void one() {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
  }

  void two() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
  }

  void three() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
  }

  void four() {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
  }

  void five() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
  }

  void six() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
  }

  void seven() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
  }

  void eight() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
  }

  void nine() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
  }


  void allNumbers(){

        one();delay(500);
        two();delay(500);
        three();delay(500);
        four();delay(500);
        five();delay(500);
        six();delay(500);
        seven();delay(500);
        eight();delay(500);
        nine();delay(500);
  }

  void turnOffAllSegments(){
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    digitalWrite(pinD, HIGH);
    digitalWrite(pinE, HIGH);
    digitalWrite(pinF, HIGH);
    digitalWrite(pinG, HIGH);
  }

  void digit4(){
    digitalWrite(D1, 0);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
  }
      
  void digit1(){

    digitalWrite(D1, 1);
    digitalWrite(D2, 0);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
  }
      
  void digit2(){
    digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 0);
    digitalWrite(D4, 1);
  }
      
  void digit3(){
    digitalWrite(D1, 1);
    digitalWrite(D2, 1);
    digitalWrite(D3, 1);
    digitalWrite(D4, 0);
  }

  void all4Digits(){

    digitalWrite(D1, 0);
    digitalWrite(D2, 0);
    digitalWrite(D3, 0);
    digitalWrite(D4, 0);
  }
//


void ISR(){
 change = true;
}

void setup() {

  Serial.begin(115200);
  Serial.println(" STARTING ");

  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(changeButton, INPUT_PULLUP);

  WiFi.softAP(ssid, password,6);

  ArduinoOTA.setHostname("ESP32-OTA");
  ArduinoOTA.begin();

  //  for (int i = 0; i < 7; i++) {
  //     int noteDuration = noteDurations[i];
  //     tone(buzzer, melody[i], noteDuration);
  //     delay(noteDuration * 1.30);  // A little pause between notes
  //   }
  //   noTone(buzzer);  // Turn off the buzzer

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinDP, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  //        for (int i = 0; i < 7; i++) {
  //   int noteDuration = noteDurations[i];
  //   tone(buzzer, melody[i], noteDuration);
  //   delay(noteDuration * 1.30);  // A little pause between notes
  // }
  
  noTone(buzzer); 

  for (int i=0;i<255;i++){
    analogWrite(greenLed,i);
    analogWrite(blueLed,i);
    analogWrite(redLed,i);
    analogWrite(led,i);
    delay(1);
  }
  for (int i=255;i>0;i--){
    analogWrite(greenLed,i);
    analogWrite(blueLed,i);
    analogWrite(redLed,i);
    analogWrite(led,i);
    delay(1);
  }
 attachInterrupt(digitalPinToInterrupt(buttonPin),ISR,FALLING);

 digitalWrite(motor,0);
all4Digits();
 for (int i = 0; i<10;i++){
  
       digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, 1);
      delay(500);
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      delay(500);
 }



}

void draw(int num){
 switch (num){
 case 0:
 zero();
 break;
 case 1:
 one();
 break;


 case 2:
 two();
 break;


 case 3:
 three();
 break;


 case 4:
 four();
 break;


 case 5:
 five();
 break;


 case 6:
 six();
 break;


 case 7:
 seven();
 break;


 case 8:
 eight();
 break;
 
 case 9:
 nine();
 break;


 }
}

void nToN(unsigned long n){

 for (int i = 0; i < 50; i++){

 digit4();
 draw(n % 10);
 delay(3);


 digit3();
 draw((n/10)%10);
 delay(3);


 digit2();
 draw((n/100)%10);
 delay(3);


 digit1();
 draw((n/1000%10));
 delay(3);

 }

}

void clear(){
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
}

void waiting(){
      
    trackerC = millis();

    if (trackerC - trackerP > 100){
      trackerP = trackerC;
    circle = (circle+1)%12;
    }



    // while(!running){
    // delay(5);
    // Serial.println(" Stuck in loop ");
    // for (int i=0; i<50; i++){


    switch (circle){
  case 0:
      digit4();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 1:
      digit4();
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 1);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 2:
      digit4();
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 1);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 3:
      digit4();
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 4:
      digit3();
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 5:
      digit2();
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 6:
      digit1();
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 7:
      digit1();
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 1);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 8:
      digit1();
      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 1);
      digitalWrite(pinG, 0);
      break;

  case 9:
      digit1();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 10:
      digit2();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;

  case 11:
      digit3();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
      break;
      //}  
    }
  
}



#endif
