#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP; 
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // Variables to store the time 
int hours, minutes, seconds;
float fahrenheit;
unsigned long touchStartTime = 0; // Tracks when the touch started
bool wasTouched = false;          // Previous touch state
int bright = 50;

const char* ssid = "I believe Wi can Fi farther";
const char* password = "oceantiger2";
int state;
bool needsHome = true;
bool needsRan = true;
int delayTime = 20;
// const char* apiURL = "https://api.openweathermap.org/data/3.0/onecall?lat=33.44&lon=-94.04&exclude=hourly,daily&appid={API key}
// ";

unsigned long previousMillis = 0;
const long interval = 1800000; // 30 minutes in milliseconds
float currentTemperature = 50.0;


const char* host = "api.openweathermap.org"; 
const char* path = "http://api.openweathermap.org/data/3.0/onecall?lat=40.50&lon=-75.20&exclude=minutely,hourly,daily,alerta&appid=55dc91f7daf75f7a12b2eb7423090888";


WiFiClient wifiClient;
HttpClient httpClient = HttpClient(wifiClient, host, 80);

// Replace with your network credentials
// const char* ssid = "your_SSID";
// const char* password = "your_PASSWORD";

// // OpenWeatherMap API setup
// const String apiKey = "your_API_key"; // Get your API key from OpenWeatherMap
// const String cityId = "your_city_ID"; // Find your city ID on OpenWeatherMap

#define PIN 14 // Digital IO pin for the Neopixels
#define NUMPIXELS 60 // Number of LEDs in the strip

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t hourColor = strip.Color(255, 0, 0);   // Red for hours
uint32_t minuteColor = strip.Color(0, 255, 0); // Green for minutes
uint32_t secondColor = strip.Color(0, 0, 255); // Blue for seconds




void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  // Initialize the strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  fetchTemperature();
  timeClient.begin();
  // Run startup animation
  // startupAnimation();
  //   float fahrenheit = ((currentTemperature - 273.15) * 9.0 / 5.0) + 32.0;
  //   Serial.println();
  //   Serial.print(fahrenheit);
  // displayTemperature(fahrenheit);
      strip.setBrightness(5);  // Set brightness to 50%

}

int starting = 30;

void displayTemperature(float temp) {
  strip.setBrightness(bright); 

  int ledIndex = map(temp, -10, 110, 0, 60); // Map temperature to LED index
  Serial.println(ledIndex);

  for (int i = 0; i < ledIndex; i++) {
    Serial.println(i);
    strip.setPixelColor(pix(i), getColor(i)); // Set the color based on the LED index
    strip.show();
    delay(delayTime);
    if (i < 30){
      starting--;
      strip.setPixelColor(pix(31+i),0,0,0);
    }
  }

    for (int i=ledIndex; i <60; i++){
      strip.setPixelColor(pix(i),0,0,0);
      delay(delayTime/2);
      strip.show();
    }
    starting = 0;
  
}



bool mode = 1;
unsigned long pT;
bool newV = true;
bool newTemp = false;
bool lowest;

void loop() {


// for (int i = -10 ; i < 111; i += 10){
//   startupAnimation();
//   displayTemperature(i);
//   delay(2000);
// }


  int touchValue = touchRead(15);
  bool isTouched = touchValue < 50; // Check if touch detected
  Serial.println(touchRead(15));

  // Tap Detection (Rising Edge)
  if (isTouched && !wasTouched) {
    bright += 25;
    newTemp = true;
    delay(200);
    strip.setBrightness(bright);  // Set brightness to 50%
    touchStartTime = millis(); // Record time when touch starts
  }

  if (isTouched && (millis() - touchStartTime > 500)) { // 500ms threshold for "hold"
    newTemp = true;

     if (lowest){
        delay(3000);
        lowest = false;
     }
     bright+=5;


    if (bright > 255){
      bright = 1;
      lowest = true;
    }
    delay(5);
  } 

Serial.println(bright);  

wasTouched = isTouched; // Update touch state for next loop



if (mode && newTemp){
  newTemp = false;

  strip.setBrightness(bright); 

  int ledIndex = map(fahrenheit, -10, 110, 0, 60); // Map temperature to LED index
  Serial.println(ledIndex);

  for (int i = 0; i < ledIndex; i++) {
    Serial.println(i);
    strip.setPixelColor(pix(i), getColor(i)); // Set the color based on the LED index
  }
  strip.show();

}



// if (mode){
   if (millis()-pT > 600000 || newV == true){
    newV = false;
    pT = millis();
  fetchTemperature();
    fahrenheit = ((currentTemperature - 273.15) * 9.0 / 5.0) + 32.0;
    Serial.println();
    Serial.print(fahrenheit);
    starting = 30;
          startupAnimation();
  displayTemperature(fahrenheit);

   }


// }else{
//   strip.clear();


//   unsigned long epochTime = timeClient.getEpochTime(); // Convert the epoch time to hours, minutes, and seconds 
//   hours = (epochTime % 86400L) / 3600; 
//   minutes = (epochTime % 3600) / 60; 
//   seconds = epochTime%60;
 

//     if (hours >= 12) {
//     if (hours > 12) hours -= 12;
//   }
//   if (hours == 0) hours = 12;

//   int hHand = map(hours, 0,11,60,0);
//   int mHand = map(minutes,0,60,60,0);
//   int sHand = map(seconds,0,60,60,0);

//   Serial.print(hHand);
//   Serial.print(mHand);
//   Serial.println(sHand);



//   addColorAtPosition(pix(15), hourColor);
//   addColorAtPosition(pix(mHand), minuteColor);
//   addColorAtPosition(pix(sHand), secondColor);

//   strip.show(); 
//   delay(20);
// }
}



void fetchTemperature() {
  if (WiFi.status() == WL_CONNECTED) {
    httpClient.get(path);
    int statusCode = httpClient.responseStatusCode();
    String response = httpClient.responseBody();

    if (statusCode > 0) {
      Serial.println("Weather data: " + response);
      // Parse the temperature from the response
      currentTemperature = parseTemperature(response);
      Serial.println("Current Temperature: " + String(currentTemperature) + " °C");
    } else {
      Serial.println("Error on HTTP request");
    }
    httpClient.stop();
  }
}

float parseTemperature(String response) {
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, response);

  // Extract the current temperature from the JSON response
  float temperature = doc["current"]["temp"];
  return temperature;
}

int pix (int index){
  int newPix;
  if (index <= 30){
    newPix = 30-index;
  }else{
    newPix = 90 - index;
  }
  Serial.println(newPix);
  return newPix;
}

void startupAnimation() {

 for (int i = 0; i< 60; i++){
  strip.setPixelColor(pix(i),getColor(i));
  delay(delayTime);
 }
 delay(2000);
  for (int i = 0; i < 1; i++) { // Go around twice
    for (int j = 0; j < 60; j++) {
      // j %= 60;
        strip.setPixelColor(pix(j-29), 0,0,0); // White 
        strip.setPixelColor(pix(j), getColor(j)); // White
        strip.show();
        delay(delayTime);
    }
  }






}



uint32_t getColor(int index) {
  if (index < 30) {
    // Blue section (first 30 LEDs)
    return strip.Color(0, 0, 255); // Blue
  } else if (index < 40) {
    // Blue to White transition (LEDs 30 to 39)
    int blueFade = map(index, 30, 40, 255, 0);
    int whiteFade = map(index, 30, 40, 0, 255);
    return strip.Color(whiteFade, whiteFade, blueFade); // Blue to White
  } else if (index < 50) {
    // White to Yellow transition (LEDs 40 to 49)
    int yellowFade = map(index, 40, 50, 5, 255);
        int redFade = map(index, 40, 50, 5, 255);

    return strip.Color(redFade, yellowFade, 0); // White to Yellow
  } else if (index < 56) {
    // Yellow to Red transition (LEDs 50 to 59)
    
    int redFade = map(index, 50, 60, 180, 255);
    return strip.Color(255, 255 - redFade, 0); // Yellow to Red
    }else if (index < 60){
      return strip.Color(255,0,0);
    }
  
  return strip.Color(0, 0, 0); // Off or default color
}

