#include <SPI.h>
#include <TFT_eSPI.h>
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"
#include "peripherals.h"

#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();  // TFT instance


// Define the font names as arrays, not in quotes
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36




void setup() {

  Serial.begin(115200);
  Serial.println(" STARTING ");

  tft.begin();
  tft.setRotation(0);

  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(changeButton, INPUT_PULLUP);

  // WiFi.softAP(ssid, password,6);

  // ArduinoOTA.setHostname("ESP32-OTA");
  // ArduinoOTA.begin();

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

  //        for (int i = 0; i < 7; i++) {
  //   int noteDuration = noteDurations[i];
  //   tone(buzzer, melody[i], noteDuration);
  //   delay(noteDuration * 1.30);  // A little pause between notes
  // }
  
  noTone(buzzer); 


 attachInterrupt(digitalPinToInterrupt(buttonPin),ISR,FALLING);


  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);    // Set text color and background color for anti-aliasing
  tft.loadFont(AA_FONT_SMALL);               // Load desired font

  // Center the text
  int16_t x = (240 - tft.textWidth("reaction time: 98")) / 2;
  int16_t y = (240 - tft.fontHeight()) / 2;
  tft.setCursor(x, y);

  tft.print("STARTING");

  delay(10000);  

}


void clear(){
    tft.fillScreen(TFT_BLACK);
}

void reactionTimer(){
        
  currT=millis();

  if (change){
    delay(200);
    changeStart=currT;
    step = (step+1)%4;
    change = false;
  }

  currT = millis();

  switch(step){

  case 0: 

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_MAROON);    // Set text color and background color for anti-aliasing
  tft.loadFont(AA_FONT_SMALL);               // Load desired font

  tft.setCursor(110,110);


  // Center the text
  // int16_t x = (240 - tft.textWidth("Reaction Time: 98")) / 2;
  // int16_t y = (240 - tft.fontHeight()) / 2;
  // tft.setCursor(x, y);

  tft.print("PRESS TO START");

    startTime = millis();
    delay(200);

  break;
  case 1:
    currT=millis();
    rands = random(2000,3000);

        if (currT - startTime > rands) { 
     startTime = millis();
       tft.loadFont(AA_FONT_SMALL);               // Load desired font

 tft.setCursor(100, 100);
   tft.setTextColor(TFT_WHITE, TFT_GREEN);    // Set text color and background color for anti-aliasing
  tft.print("GO");

      tone(buzzer, tone3, 400);
      step++;

    }

        
  break;

  case 2:
 
   break;

  case 3:
     char str[10];
        reactionTime = currT-startTime;
        
  sprintf(str, "%d", reactionTime);
        Serial.print("   REACTION TIME:  ");
        Serial.println(reactionTime);
 tft.setCursor(100, 100);
   tft.setTextColor(TFT_WHITE, TFT_RED);    // Set text color and background color for anti-aliasing
  tft.print(reactionTime);
        clear();
        delay(100);

        if (reactionTime-200 < best){
          best = reactionTime-200;

    tone(buzzer, tone1, 200); 
    delay(100);

    tone(buzzer, tone2, 200);
    delay(100);

    tone(buzzer, tone3, 200);
    delay(200); 

    noTone(buzzer); 
        }
        if (best<200){
          clear();
//besttt
        }

        step = 0;
        changeStart=millis();
        
  break;
 }
}













void nToN(int x, int y, char text[]){

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_MAROON);    // Set text color and background color for anti-aliasing
  tft.loadFont(AA_FONT_SMALL);               // Load desired font

  tft.setCursor(x, y);


  // Center the text
  // int16_t x = (240 - tft.textWidth("Reaction Time: 98")) / 2;
  // int16_t y = (240 - tft.fontHeight()) / 2;
  // tft.setCursor(x, y);

  tft.print(text);



}
void nToT(int x, int y, int num){

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_MAROON);    // Set text color and background color for anti-aliasing
  tft.loadFont(AA_FONT_SMALL);               // Load desired font

  tft.setCursor(x, y);


  // Center the text
  // int16_t x = (240 - tft.textWidth("Reaction Time: 98")) / 2;
  // int16_t y = (240 - tft.fontHeight()) / 2;
  // tft.setCursor(x, y);

  tft.print(num);



}


void loop() {

  if (digitalRead(changeButton)==0){
    delay(200);
    changeMode=(changeMode+1)%3;
    step=0;
  }

  switch(changeMode){

    case 0:    // reation tester
    reactionTimer();
    break;

    // case 1:
    // toneGame();
    // break;

    // case 2: 
    // memoryGame();
    // break;
  }

}
