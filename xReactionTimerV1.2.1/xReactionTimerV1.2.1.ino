#include <SPI.h>
#include <TFT_eSPI.h>
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"
#include <PNGdec.h>
// #include "mal.h" // Image is stored here in an 8-bit array

PNG png; // PNG decoder instance

#define MAX_IMAGE_WIDTH 241 // Adjust for your images

int16_t xpos = 0;
int16_t ypos = 0;

// TFT_BLACK       0x0000
// TFT_NAVY        0x000F
// TFT_DARKGREEN   0x03E0
// TFT_DARKCYAN    0x03EF
// TFT_MAROON      0x7800
// TFT_PURPLE      0x780F
// TFT_OLIVE       0x7BE0
// TFT_LIGHTGREY   0xC618
// TFT_DARKGREY    0x7BEF
// TFT_BLUE        0x001F
// TFT_GREEN       0x07E0
// TFT_CYAN        0x07FF
// TFT_RED         0xF800
// TFT_MAGENTA     0xF81F
// TFT_YELLOW      0xFFE0
// TFT_WHITE       0xFFFF
// TFT_ORANGE      0xFDA0
// TFT_GREENYELLOW 0xB7E0
// TFT_PINK        0xFC9F

const uint16_t imageData[] = {
  
};

int step, reactionTime, change, rands,changeButton,drawnOnce, changeMode,x,y,middle=26, green = 25, red = 33, best=1000;
int showBest, lastRun, total, trials,primary, menue, drawSelection, selection = 1, newMenue, average;
unsigned long currT, changeStart, startTime;
int birdRadius = 5, gravity = 1, jumpStrength = -5, pipeWidth = 10;
int pipeGap=40, birdY=60, birdVelocity=0;
int pipeX=240,pipeHeight,score;
bool gameRunning = true;
bool offMenu;
int redSel, greenSel,circler,circle1x,circle2,circle2x,overLap,area,circleOver,circleScore;
unsigned long gameInterval;
int redScore,newGame=1;


int dinoY = 150; // Initial Y position of the dinosaur
int dinoX = 30; // X position of the dinosaur
int dinoJump = 0; // Jump state
int obstacleX1 = 290; // Initial X position of the bottom obstacle
int obstacleX2 = 650; // Initial X position of the top obstacle
bool gameOver = false;
bool onBottom = true; // Track whether the dino is on the bottom ground
int obstacleSpeed = 5; // Initial speed of obstacles
unsigned long previousMillis = 0; // Store last time obstacles moved
unsigned long speedIncreaseInterval = 5000; // Interval at which to increase speed (5 seconds)
unsigned long gameOverTime = 0; // Store the time when the game is over
bool gameStarted = false;
bool gameGoing;
bool color;
unsigned long gameStart;
bool spelling;



char buffer[20];
// Define the font names as arrays, not in quotes
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36

TFT_eSPI tft = TFT_eSPI();  // TFT instance

void ISR(){
 change = true;
}

// void pngDraw(PNGDRAW *pDraw) {
//   uint16_t lineBuffer[MAX_IMAGE_WIDTH];
//   png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
//   tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
// }

void setup() {
   Serial.begin(9600);
   tft.begin();
   tft.setRotation(0);
   pinMode(26,INPUT_PULLUP);
   pinMode(33,INPUT_PULLUP);
   pinMode(25,INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(green),ISR,FALLING);
   pipeHeight = random(10,150);
         tft.fillScreen(TFT_BLACK);
         tft.setCursor(60, 110);
        tft.loadFont(AA_FONT_LARGE); // Must load the font first

          tft.println("HELLO");
          delay(2000);

         tft.fillScreen(TFT_BLACK);
         drawSelection = 1;
         newMenue = 1;
  //   int16_t rc = png.openFLASH((uint8_t *)mal, sizeof(mal), pngDraw);
  // // if (rc == PNG_SUCCESS) {
  // //   tft.startWrite();
  // //   uint32_t dt = millis();
  // //   rc = png.decode(NULL, 0);
  // //   tft.endWrite();
  // //   // png.close(); // not needed for memory->memory decode
  // // }
  // delay(3000);
}

void clear(){

      Serial.println("CLEARED");
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);    // Set text color and background color for anti-aliasing
      tft.loadFont(AA_FONT_SMALL);               // Load desired font

      // tft.setTextColor(TFT_WHITE, TFT_BLACK);    // Set text color and background color for anti-aliasing
      // tft.loadFont(AA_FONT_SMALL);               // Load desired font

      // Center the text
      x = (240 - tft.textWidth("Best: 888")) / 2;
      y = (240 - tft.fontHeight()) / 4;

      sprintf(buffer, "%d", best);
      tft.setCursor(x,(240 - tft.fontHeight())/4);
      tft.print("Best: ");
      tft.print(buffer);
      tft.setCursor(x-20, 28);
      sprintf(buffer, "%d", average);

      tft.print("Avgerage: ");
      tft.print(buffer);

      switch(lastRun){
        case 1: 
         tft.setTextColor(TFT_YELLOW, TFT_BLACK);    // Set text color and background color for anti-aliasing
         tft.loadFont(AA_FONT_SMALL);               // Load desired font
         tft.setCursor(100,200);
         tft.print("INSANE");
         break;
       case 2: 
         tft.setTextColor(TFT_GREEN, TFT_BLACK);    // Set text color and background color for anti-aliasing
         tft.loadFont(AA_FONT_SMALL);               // Load desired font
         tft.setCursor(60,200);
         tft.print("ABOVE AVERAGE");
         break;
       case 3: 
         tft.setTextColor(TFT_WHITE, TFT_BLACK);    // Set text color and background color for anti-aliasing
         tft.loadFont(AA_FONT_SMALL);               // Load desired font
         tft.setCursor(90,200);
         tft.print("AVERAGE");
         break;
       case 4: 
         tft.setTextColor(TFT_RED, TFT_BLACK);    // Set text color and background color for anti-aliasing
         tft.loadFont(AA_FONT_SMALL);               // Load desired font
         tft.setCursor(60,200);
         tft.print("BELOW AVERAGE");
         break;
      }
      
}

void reactionTimer(){

  //  tft.setTextSize(4); 

  //   Serial.print("STEP: ");
  //  Serial.println(step);

  currT=millis();



  if (change){
    delay(100);
    changeStart=currT;
    step = (step+1);
    change = false;
    drawnOnce = 0;
    // clear();
      Serial.println("TRIGGERED");
  }
  
  switch(step){

  case 0: 

    Serial.println("STEP: 0");

      if (drawnOnce == 0){
        drawnOnce = 1;

       tft.setTextColor(TFT_WHITE, TFT_BLACK);    // Set text color and background color for anti-aliasing

      // Center the text
              tft.loadFont(AA_FONT_LARGE); // Must load the font first

      x = (240 - tft.textWidth("Press Start")) / 2;
      y = (240 - tft.fontHeight()) / 2;
      tft.setCursor(x, y);

      tft.print("Press Start");
      }

    startTime = millis();

  break;

  case 1: 
    Serial.println("STEP: 1");

    if (drawnOnce == 0){
        drawnOnce = 1;
      clear();

      tft.setTextColor(TFT_WHITE, TFT_BLACK);    // Set text color and background color for anti-aliasing

      // Center the text
      x = (240 - tft.textWidth("Get Ready...")) / 2;
      y = (240 - tft.fontHeight()) / 2;
      tft.setCursor(x-60, y);
      tft.loadFont(AA_FONT_LARGE); // Must load the font first

      tft.print("Get Ready...");
    }

        rands = random(2000,3000);
        delay(rands);
        // if (millis() - startTime > rands) { 
         startTime = millis();

          tft.fillScreen(TFT_BLACK);

          tft.setTextColor(TFT_GREEN, TFT_BLACK);    // Set text color and background color for anti-aliasing

          // Center the text
          // x = (240 - tft.textWidth("GO")) / 2;
          // y = (240 - tft.fontHeight()) / 2;
          tft.setCursor(90, 100);
            tft.loadFont(AA_FONT_LARGE); // Must load the font first

                    tft.print("GO!");

          // tft.fillScreen(TFT_BLACK);
          // tft.setTextSize(2); 
          // tft.setTextColor(TFT_GREEN, TFT_BLACK);    // Set text color and background color for anti-aliasing
          // delay(500);
        
          // tone(buzzer, tone3, 400); 

          step++;
         startTime = millis();
          tft.setCursor(90, 120);
        //}

  break;

  case 2:
    Serial.println("STEP: 2");
    tft.setCursor(70, 150);
    tft.print(millis()-startTime);
    delay(20);
    tft.fillRect(70, 150, 90, 30, TFT_BLACK);

  break;

  case 3:
  Serial.println("STEP: 3");

        reactionTime = (millis()-startTime);

        int theTime = ((int)reactionTime)-99;
        total += theTime;
        trials++;

        average = total/trials;

        if (average < 400 && average > 300){
          lastRun = 3;
          }
          if (average < 200 && average > 180){
            lastRun = 2;
          }
          if (average < 100){
            lastRun = 1;
          }
          if(average > 400){
            lastRun = 4;
        }

    if (drawnOnce == 0){
        drawnOnce = 1;
        // clear();          

      // Center the text
      x = (240 - tft.textWidth("000")) / 2;
      y = (240 - tft.fontHeight()) / 2;
      tft.setCursor(x-20, y);

      tft.fillScreen(TFT_BLACK);

      sprintf(buffer, "%d", theTime);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);    // Set text color and background color for anti-aliasing
        tft.loadFont(AA_FONT_LARGE); // Must load the font first

      tft.print(buffer);
    }
        Serial.print("   REACTION TIME:  ");
        Serial.println(reactionTime);
        //DISPLAY
        delay(1000);

        if (theTime < best){
          best = theTime;
          showBest=1;

          tft.fillScreen(TFT_BLACK);
          tft.setCursor(20,100);
          tft.setTextColor(TFT_GREEN, TFT_BLACK);    // Set text color and background color for anti-aliasing
         tft.loadFont(AA_FONT_LARGE); // Must load the font first

          tft.print("NEW BEST!");
          delay(1000);
        }
    // tone(buzzer, tone1, 200); 
    // delay(100);

    // tone(buzzer, tone2, 200);
    // delay(100);

    // tone(buzzer, tone3, 200);
    // delay(200); 

    // noTone(buzzer); 
    //     }
    //     if (best<200){
    //       clear();
    //       nToN(best);
    //     }

        step = 0;
        changeStart=millis();
        clear();
        drawnOnce = 0;
        
    break;
  }
  
}

void updateGame() {
  if (digitalRead(green) == LOW) {
    birdVelocity = jumpStrength;
  }

  birdY += birdVelocity;
  birdVelocity += gravity;

  pipeX -= 2;
  if (pipeX < -pipeWidth) {
    pipeX = 240;
    pipeHeight = random(10, 210);
    score++;
  }
}

void checkCollision() {
  if (birdY < 0 || birdY > 240) {
    gameRunning = false;
    tft.fillScreen(TFT_BLACK);
  }

  if (pipeX < 100 && pipeX > 90) {
    if (birdY < pipeHeight || birdY > pipeHeight + pipeGap) {
      gameRunning = false;
          tft.fillScreen(TFT_BLACK);
    }
  }
}

void drawGame() {
  // tft.fillScreen(TFT_BLACK);

  // Draw bird
  tft.fillRect(90,0,20,240,TFT_BLACK);

  tft.fillCircle(100, birdY, birdRadius, TFT_WHITE);

  // Draw pipes
  tft.fillRect(pipeX, 0, pipeWidth, pipeHeight, TFT_WHITE);
  tft.fillRect(pipeX, pipeHeight + pipeGap, pipeWidth, 240 - pipeHeight - pipeGap, TFT_WHITE);
  
  tft.fillRect(pipeX+pipeWidth, 0, pipeWidth, pipeHeight, TFT_BLACK);
  tft.fillRect(pipeX+pipeWidth, pipeHeight + pipeGap, pipeWidth, 240 - pipeHeight - pipeGap, TFT_BLACK);

  // Draw score
  tft.fillRect(50,15,50,15,TFT_BLACK);
  tft.setCursor(60, 15);
  tft.setTextSize(2);
  tft.print("Score: ");
  tft.print(score);
  delay(50);
}

void displayGameOver() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 100);
  tft.setTextSize(4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.print("Game Over");
  delay(100);
  // tft.setTextSize(2);
  // tft.setCursor(30, 100);
  // tft.print("Press to Restart");
}

void resetGame() {
  tft.fillScreen(TFT_BLACK);
  birdY = 60;
  birdVelocity = 0;
  pipeX = 240;
  score = 0;
  gameRunning = true;
}

void restartGame() {


  dinoY = 150;
  dinoX = 30;
  dinoJump = 0;
  obstacleX1 = 290;
  obstacleX2 = 650;
  gameOver = false;
  onBottom = true;
  obstacleSpeed = 5;
  previousMillis = millis();
  tft.fillScreen(TFT_BLACK);
  
  // Draw initial grounds
  // tft.fillRect(0, 170, 240, 10, TFT_WHITE); // Bottom ground
  // tft.fillRect(0, 90, 240, 10, TFT_WHITE); // Top ground
}

void GeoDash(){


  if (!gameOver) {
    // Clear previous dinosaur position
    tft.fillRect(dinoX, dinoY, 20, 20, TFT_BLACK);

    // Update dinosaur position
    // if (dinoJump > 0) {
      // dinoY += (onBottom ? -5 : 5); // Jump up if on bottom, down if on top
      // dinoJump--;
      if (dinoJump == 1 && !onBottom) {
      dinoJump = 0;
      dinoY = 100; // Fall down if on bottom
    } if (dinoJump ==1 && onBottom) {
      dinoJump = 0;
      dinoY = 150; // Rise up if on top
    }

    // Draw dinosaur
    tft.fillRect(dinoX, dinoY, 20, 20, TFT_GREEN);

    // Clear previous obstacle positions
    tft.fillRect(obstacleX1, 150, 20, 20, TFT_BLACK);
    tft.fillRect(obstacleX2, 100, 20, 20, TFT_BLACK);

    // Update obstacle positions
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= speedIncreaseInterval) {
      previousMillis = currentMillis;
      obstacleSpeed++;
      tft.setTextSize(0);
      tft.fillRect(0,0,200,55,TFT_BLACK);

      tft.setCursor(20,30);
      tft.print("Speed: ");
      tft.print(obstacleSpeed-5);
    }
    obstacleX1 -= obstacleSpeed;
    obstacleX2 -= obstacleSpeed;

    // Reset obstacles when off screen

    if (obstacleX2 < -20) obstacleX2 = 240;
    if (obstacleX1 < -20) {

    obstacleX1 = obstacleX2 + 340;
    }
    // Draw obstacles
    tft.fillRect(obstacleX1, 150, 20, 20, TFT_RED);
    tft.fillRect(obstacleX2, 100, 20, 20, TFT_RED);

    // Check for collision
    if ((obstacleX1 < dinoX + 20 && obstacleX1 > dinoX - 20 && dinoY >= 150) || 
        (obstacleX2 < dinoX + 20 && obstacleX2 > dinoX - 20 && dinoY <= 100)) {
      gameOver = true;
      gameOverTime = millis(); // Record the time of game over
    }

    delay(50); // Control the game speed
    gameStarted = true;
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(4);
    tft.setCursor(10, 100);
    tft.println("Game Over");
    delay(3000);
    restartGame();
    }
  

  // Check for gravity switch (button press on pin 5)
  if (digitalRead(green) == LOW && gameStarted) {
    onBottom = !onBottom; // Switch gravity
    dinoJump = 1; // Smooth transition with a jump
    delay(80); // Debounce delay
  }
}

void redAndGreen(){

 if (newGame){
  gameStart = millis();
newGame=0;
}

  if (!gameGoing){
    color = random(0,2);
    spelling = random(0,2);
    tft.setTextSize(3);
    tft.setCursor(60,100);
    if (color == 1){       //RED
      tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_RED);
    if (spelling == 1){
        tft.print("GREEN");
    }
    else {
          tft.setCursor(75,100);
        tft.print("RED");
    }
    }else{                 //GREEN
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_GREEN);
        
      if (spelling == 1){
        tft.print("GREEN");
    }
    else {
        tft.setCursor(75,100);
        tft.print("RED");
    }
}

gameGoing = true;
}
    tft.setTextColor(TFT_WHITE);
tft.fillRect(75,30,100,30,TFT_BLACK);
tft.setCursor(75,30);
tft.setTextSize(0);
tft.print(10000-(millis()-gameStart));
delay(40);
tft.setCursor(100,150);
tft.setTextSize(1);
tft.fillRect(100,150,50,50,TFT_BLACK);
tft.print(redScore);

if (digitalRead(green) == 0 && color == 0){
  tft.setCursor(90,100);

  delay(200);
  gameGoing=0;
  redScore++;
} 
if (digitalRead(green)==0 && color == 1 || 10000-(millis()-gameStart) <250){        // GAME OVER
  tft.fillScreen(TFT_BLACK);
    tft.setCursor(30,100);
  tft.println("Game Over");
  tft.print("    Score: ");
  tft.print(redScore);
  delay(3000);
  tft.fillScreen(TFT_BLACK);
  redScore = 0;
    delay(300);
    gameStart = millis();

  gameGoing=0;
}

if (digitalRead(red)==0 && color == 1){
  tft.setCursor(90,100);
    delay(200);
  gameGoing=0;
  redScore++;
}

if (digitalRead(red)==0 && color == 0){        // GAME OVER
  tft.fillScreen(TFT_BLACK);
    tft.setCursor(30,100);
  tft.println("Game Over");
  tft.print("    Score: ");
  tft.print(redScore);  
  delay(3000);
  tft.fillScreen(TFT_BLACK);
  gameStart = millis();

    redScore = 0;

    delay(300);
  gameGoing=0;
 }


}

float calculateOverlapArea(float radius, float distance) {
  if (distance >= 2 * radius) {
    return 0; // No overlap
  }
  if (distance <= 0) {
    return PI * radius * radius; // Complete overlap
  }
  
  float d = distance / 2.0;
  float r2 = radius * radius;
  float h = sqrt(r2 - d * d);

  float angle1 = 2.0 * acos(d / radius);
  float angle2 = angle1;
  
  float segmentArea1 = (r2 / 2.0) * (angle1 - sin(angle1));
  float segmentArea2 = (r2 / 2.0) * (angle2 - sin(angle2));
  
  return segmentArea1 + segmentArea2;
}

void circleSlide(){
  if (newGame){
    tft.fillScreen(TFT_BLACK);
    newGame=0;
  circler = 30;
  circle1x = 120;
  circle2x = 0;
  circleScore = 0;
  }

  if (circle2x > 230){
    circleOver = true;
  }

  if (circleOver){  // GAME OVER
    tft.fillScreen(TFT_BLACK);
    int x = (tft.width() - tft.textWidth("Game Over")) / 2; 
    int y = (tft.height() - tft.fontHeight()) / 2; 
    tft.setCursor(x,y);
    tft.println("Game Over");

    int nx = (tft.width() - tft.textWidth("    Score: ")) / 2; 
    int ny = ((tft.height() - tft.fontHeight()) / 4)*3; 
    tft.setCursor(nx,ny);
    tft.print("Score: ");
    tft.print(circleScore);
    delay(3000);
    newGame=1;
    circleOver = 0;
    
  }

  if (millis() - gameInterval > 100){
    gameInterval = millis();
    circle2x+=10;
    int temp = circle2x - circler;
    tft.fillRect((temp)-10, 90, 60,70, TFT_BLACK);
    tft.fillCircle(circle1x,120,circler,TFT_GREEN);
    tft.fillCircle(circle2x, 120,circler,TFT_WHITE);
  }

  if (digitalRead(green) == 0){
    tft.fillCircle(120,120,circler,TFT_BLACK);
    delay(1000);
    circler = circler - (abs(120-circle2x))/2;
    if (circler <= 0){
      circleOver = 1;
    }
    // overLap = calculateOverlapArea(circler, abs((circle1x-circle2x)));
    // area = circler * circler * 3.1416;
    // area = area - (area-overLap);
    // circler -= (sqrt(area / PI));
    circle2x = 0;
    tft.fillScreen(TFT_BLACK);
    circleScore++;
  }
}

int sliderX = 120, direction, speed, ballx, bally, xspeed=1, yspeed=-1;
int pongScore;
int colorPick;
int pballx,pbally,gamedelay=15;

void pong(){

  if (newGame){
    ballx = random(50,150);
    bally = random(60,100);
    newGame = 0;
    pongScore = 0;
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(36,36,168,10,TFT_WHITE);
    tft.fillRect(36,36,10,168,TFT_WHITE);
    tft.fillRect(204,36,10,168,TFT_WHITE);
    yspeed = -1;
  }

  pballx=ballx;
  pbally=bally;

  ballx += xspeed;
  bally += yspeed;

  if (ballx > 196 || ballx <53){
    xspeed *= -1;
    colorPick = tft.color565(random(0, 256), random(0, 256), random(0, 256));
  } 

  if (bally < 53){
    yspeed *= -1;
    colorPick = tft.color565(random(0, 256), random(0, 256), random(0, 256));

  }
  
  if (bally > 197 && bally < 199 && ballx > sliderX-5 && ballx < (sliderX+35)){
    colorPick = tft.color565(random(0, 256), random(0, 256), random(0, 256));
    // yspeed *= -1; 
    yspeed = random(-3,0);
    int xs = random(-3,3);
    while (xs == 0){
      xs = random(-3,2);
    }

    // if (abs(yspeed)==1){
    //   yspeed *= 2;
    // }else{
    //   yspeed -= 1;
    // }
    // yspeed = (yspeed / yspeed)*random(1,3);
    pongScore ++;
    x = (tft.width() - tft.textWidth("  ")) / 2;
    tft.setCursor(x,120);
    tft.fillRect(x, 120, tft.textWidth("    ", 2), tft.fontHeight(2), TFT_BLACK);
    tft.setTextSize(0);
    tft.print(pongScore);
  }

  tft.fillCircle(pballx,pbally,6,TFT_BLACK);
  tft.fillCircle(ballx,bally,6,colorPick);



  delay(gamedelay);

  if (digitalRead(green)==0){
    tft.fillRect(sliderX,204,24,10,TFT_BLACK);
    sliderX+=3;
    if (sliderX>180)sliderX=180;
  }
  if (digitalRead(red) == 0){
    tft.fillRect(sliderX,204,24,10,TFT_BLACK);
    sliderX-=3;
    if (sliderX<36)sliderX = 36;
  }

  tft.fillRect(sliderX,204,24,10,TFT_WHITE);

  if (bally > 210){
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    x = (tft.width() - tft.textWidth("Score:   ")) / 2;
    tft.setCursor(x,20);
    tft.print("Score: ");
    tft.print(pongScore);
    tft.setTextSize(3);
    x = (tft.width() - tft.textWidth("Game Over")) / 2;
    tft.setCursor(x,90);
    tft.print("Game Over");
    delay(3000);
    newGame = 1;
  } 
  

}

void menu(){
  if (digitalRead(green) == 0){
    delay(200);
    selection++;
    if(selection > 6)selection=1;
    drawSelection = 1;
    greenSel=1;
    redSel=0;
    newGame = 1;
  }

  if (digitalRead(red) == 0){
    delay(200);
    selection--;
    if(selection < 1)selection=6;
    drawSelection = 1;
    redSel=1;
    greenSel=0;
  }


 if (drawSelection == 1){
   drawSelection = 0;
  if (newMenue){
      newMenue = false;
      tft.loadFont(AA_FONT_SMALL); // Must load the font first
      tft.setCursor(80,70);
      tft.setTextSize(1);
      tft.print("Reaction Timer");
      tft.setCursor(80,95);
      tft.print("Flappy Bird");
      tft.setCursor(80,120);
      tft.print("Geometry Dash");
      tft.setCursor(80,145);
      tft.print("Circle Stack");
      tft.setCursor(80,170);
      tft.print("Pong");
      tft.setCursor(80,200);    
      tft.setTextSize(1);
  
      tft.setTextColor(TFT_RED);
      tft.print("Red ");
      tft.setTextColor(TFT_WHITE);
      tft.print("and ");
      tft.setTextColor(TFT_GREEN);
      tft.print("green");
      tft.loadFont(AA_FONT_SMALL); // Must load the font first
      tft.setTextColor(TFT_WHITE);

    }

  tft.fillRect(60, 60, 15, 240, TFT_BLACK);
            if (redSel){
              tft.fillCircle(65, 75+(selection-1)*25, 5, TFT_RED);
            }else{
              tft.fillCircle(65, 75+(selection-1)*25, 5, TFT_GREEN);
            }  
    tft.setTextSize(3);
    tft.loadFont(AA_FONT_LARGE); 
    tft.setCursor(60,30);
    tft.setTextColor(TFT_PURPLE);
    tft.print("Menu");
    tft.setTextColor(TFT_WHITE);

  }

  if (digitalRead(middle)==0){
  delay(200);
  tft.fillScreen(TFT_BLACK);
  newMenue = 1;
  drawSelection = 1;
  primary = selection;
  offMenu = true;
  delay(300);
  }
}


void loop() {

if (digitalRead(middle)==0 && offMenu){
  delay(200);
  tft.fillScreen(TFT_BLACK);
  primary=0;
  offMenu = false;
  drawSelection = 1;
  newMenue = 1;
  newGame = 1;
}

switch(primary){

case 0:
menu();
break;

case 1:
reactionTimer();
break;

case 2:
  if (gameRunning) {
    updateGame();
    checkCollision();
    drawGame();
   } else {
    displayGameOver();
    if (digitalRead(middle) == LOW) {
      resetGame();
        tft.fillScreen(TFT_BLACK);

    }
  }
  delay(5);
break;

case 3:
GeoDash();
break;

case 4:
circleSlide();
break;

case 5:
pong();
break;

case 6:
redAndGreen();
break;
    
}

}
