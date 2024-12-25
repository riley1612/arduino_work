// #include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "peripherals.h"

void reactionTimer(){

  analogWrite(greenLed, 30);
  analogWrite(redLed, 0);
  analogWrite(blueLed, 0);            
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
    waiting();
    startTime = millis();
    analogWrite(led,0);

  break;

  case 1: 
        digit1();
        digitalWrite(pinA, 1);
        digitalWrite(pinB, HIGH);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, HIGH);
        digitalWrite(pinF, HIGH);
        digitalWrite(pinG, HIGH);
        delay(2);

        digit2();
        digitalWrite(pinA, LOW);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, LOW);
        digitalWrite(pinG, 1);
        delay(2);
        
        digit3();
        digitalWrite(pinA, 1);
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, 1);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 1);
        digitalWrite(pinG, 1);
        delay(2);
        digit4();
        digitalWrite(pinA, 1);
        digitalWrite(pinB, HIGH);
        digitalWrite(pinC, 0);
        digitalWrite(pinD, LOW);
        digitalWrite(pinE, HIGH);
        digitalWrite(pinF, HIGH);
        digitalWrite(pinG, HIGH);
    delay(5);
      
    turnOffAllSegments();
    // digitalWrite(led,0);

    currT=millis();
    rands = random(2000,3000);

        if (currT - startTime > rands) { 
    startTime = millis();

      tone(buzzer, tone3, 400);
      analogWrite(led,20);
      step++;

    }

        
  break;

  case 2:
   clear();
  break;

  case 3:
        noTone(buzzer); 
        digitalWrite(buzzer,0);
        analogWrite(led,0);
        reactionTime = currT-startTime;
        Serial.print("   REACTION TIME:  ");
        Serial.println(reactionTime);
        nToN(reactionTime-200);
        nToN(reactionTime-200);

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
          nToN(best);
        }

        step = 0;
        changeStart=millis();
        
  break;
 }
}


void toneGame(){

  analogWrite(greenLed , 0);
  analogWrite(redLed,40);
  analogWrite(blueLed,0);

  if (change){
    delay(200);


    step = (step+1)%4;
    change = false;
  }

 switch(step){

  case 0:
   analogWrite(led,0);
    trackerC = millis();

    if (trackerC - trackerP > 280){
      trackerP = trackerC;
    circle = (circle+1)%6;
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
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 1);
      delay(5);

      break;

   case 1:      
      digit3();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 1);
      delay(5);

      break;

   case 2:
            digit2();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 1);
      delay(5);
      clear();

      break;

   case 3:
            digit1();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 1);
      delay(5);
      clear();

      break;

   case 4:
      digit2();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 1);
      delay(5);
      clear();

      break;

   case 5:
      digit3();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 1);
      delay(5);
      clear();

      break;

   case 6:
      digit4();
      digitalWrite(pinA, 1);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 1);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 1);
      delay(5);
      clear();

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
  break;

  case 1: 

 clear();



 oS = (random(0,3))*3;

  toneone = random(300, 601); // Random note between 300 and 600 Hz
  tonetwo = toneone + oS;

    tone(buzzer, toneone, 600);
    delay(1000);
    tone(buzzer,tonetwo, 600);
   toneStart = millis();
    step++;
    choice =1;
  break;

  case 2:
    clear();
       if (millis() - toneStart >0 && millis() - toneStart < 999){
          digit1();
          digitalWrite(pinA,1);
          digitalWrite(pinB,1);
          digitalWrite(pinC,1);
          digitalWrite(pinD,1);
          digitalWrite(pinE,0);
          digitalWrite(pinF,0);
          digitalWrite(pinG,1);
   }
          if (millis() - toneStart >1000 && millis() - toneStart < 1999){
          digit1();
          digitalWrite(pinA,1);
          digitalWrite(pinB,1);
          digitalWrite(pinC,0);
          digitalWrite(pinD,1);
          digitalWrite(pinE,1);
          digitalWrite(pinF,0);
          digitalWrite(pinG,1);
   }
          if (millis() - toneStart >2000 && millis() - toneStart < 3999){
          digit1();
          digitalWrite(pinA,0);
          digitalWrite(pinB,1);
          digitalWrite(pinC,1);
          digitalWrite(pinD,0);
          digitalWrite(pinE,0);
          digitalWrite(pinF,0);
          digitalWrite(pinG,0);
   }
   
   if (millis() - toneStart >3000){
    step++;
    choice = 0;
   }
  break;

  case 3:                                        // CHECK IF TONES ARE =
        if (toneone == tonetwo){
          correct = 0;
        }
        else {
          correct = 1;
        }
        if (choice == correct){
          tone(buzzer,600,100);
          delay(200);
          tone(buzzer,600,100);
          for (int i=0;i<100;i++){
            digit1();
            digitalWrite(pinA, 0);                    // "Y"
            digitalWrite(pinB, HIGH);
            digitalWrite(pinC, 1);
            digitalWrite(pinD, 1);
            digitalWrite(pinE, 0);
            digitalWrite(pinF, HIGH);
            digitalWrite(pinG, HIGH);
            delay(2);    
            digit2();
            digitalWrite(pinA, 1);                    // "E"
            digitalWrite(pinB, 0);
            digitalWrite(pinC, 0);
            digitalWrite(pinD, 1);
            digitalWrite(pinE, 1);
            digitalWrite(pinF, HIGH);
            digitalWrite(pinG, HIGH);
            delay(2);   
            digit3();
            digitalWrite(pinA, 1);                    // "S"
            digitalWrite(pinB, 0);
            digitalWrite(pinC, 1);
            digitalWrite(pinD, 1);
            digitalWrite(pinE, 0);
            digitalWrite(pinF, HIGH);
            digitalWrite(pinG, HIGH);
            delay(2);
          }
            }
        else{
          tone(buzzer,350,100);
          delay(200);
          tone(buzzer,350,100);
          delay(200);
                    for (int i=0;i<100;i++){

        digit2();
        digitalWrite(pinA, 0);                    // "n"
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 1);
        digitalWrite(pinD, 0);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 0);
        digitalWrite(pinG, 1);
        delay(3);
        digit3();
        digitalWrite(pinA, 0);                    // "o"
        digitalWrite(pinB, 0);
        digitalWrite(pinC, 1);
        digitalWrite(pinD, 1);
        digitalWrite(pinE, 1);
        digitalWrite(pinF, 0);
        digitalWrite(pinG, 1);
        delay(3);
                    }
        }
        noTone(buzzer); 
        step=0;
  break;
 }
}

int stage, countr, tempCounter;
bool currBeep, bigPress, buttonPressed;
unsigned long pressStart, pressStop, pressDuration;

bool morse[10];

void memoryGame(){
  
  switch(stage){
    case 0: 

      currBeep = random(1);
      if (currBeep == 1){
        tone(buzzer, 400, 500);
      } else {
        tone(buzzer, 400, 100);     // Generate a beep and log it in the morse[]
      }
      morse[countr] = currBeep; 
      stage ++;
    break;

    case 1:
      int state = digitalRead(buttonPin);
          if (tempCounter == countr){
            stage = 0;
            countr ++;
            tempCounter = 0;
          }

          if (buttonState == 0 && !buttonPressed) {
            startTime = millis();
            buttonPressed = true;

            } else if (buttonState == LOW && buttonPressed) {     // Time the buttonpress        
            pressDuration = millis() - startTime;
            buttonPressed = false; 

            if (pressDuration > 400){
              bigPress = 1;
            }else{
              bigPress = 0;
            }
            if (bigPress != morse[countr]){
              tone(buzzer, 300, 200);
              delay(100);
              tone(buzzer,300,200);
              delay(3000);
              stage = 0;
          }          
          }
          break;
  }
}


void loop() {


  ArduinoOTA.handle();

  if (digitalRead(changeButton)==0){
    delay(200);
    changeMode=(changeMode+1)%3;
    step=0;
  }

  switch(changeMode){

    case 0:    // reation tester
    reactionTimer();
    break;

    case 1:
    toneGame();
    break;

    case 2: 
    memoryGame();
    break;
  }
}