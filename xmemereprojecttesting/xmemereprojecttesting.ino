#include <Stepper.h>

// Define the number of steps per revolution for your motor
const int stepsPerRevolution = 200; 

// Initialize the stepper library on pins 8 through 11
Stepper myStepper(stepsPerRevolution, 16, 14,12, 13);
int but = 1;

void setup() {
  // Set the speed at 60 rpm
  myStepper.setSpeed(60);
  pinMode(5,INPUT_PULLUP);
  // Initialize the serial port
  Serial.begin(9600);
}
bool dir=true;
int counter;

void run(){
  delay(1000);
  for (int i = 0; i < 7; i ++){
  myStepper.step(-110);
   delay(2);
  }
  delay(1000000);
}

void loop() {

  int state = digitalRead(5);

    myStepper.step(1); 
    counter++;
    Serial.println(counter);

if(state == 1){
run();
  }

  // dir = !dir;
  // counter = 0;


}
