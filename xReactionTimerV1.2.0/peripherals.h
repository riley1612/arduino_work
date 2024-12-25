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



void ISR(){
 change = true;
}




#endif
