#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoOTA.h>
#include <FastLED.h>

int pos=1,direction=1;
const char* ssid = "FBI_Surveillance";         // Your new SSID
const char* password = "123";     // Your WiFi password
WebServer server(80);
int mic = 2;
#define LED_PIN 15
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];
int currentEffect = 0;
int brightness = 128; // Initial brightness level (0-255)

int red=50,green=10,blue=25;

int effectSpeed = 50;
string  colorValue = "FF0000";

void adjustBrightness(int newBrightness) {
    brightness = newBrightness;
    FastLED.setBrightness(brightness);
    FastLED.show();
}

const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML>
  <html>
  <head>
    <title>Mallory's Lights :3</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { background-color: black; color: white; text-align: center; }
      .slider { width: 400px; }
      .button { width: 100px; height: 50px; margin: 10px; }
    </style>
  </head>
  <body>
    <h1>Mallory's Lights :3</h1>
    <p>LED Brightness:</p>
    <input type="range" class="slider" id="ledSlider" min="0" max="255" onchange="updateSliderValue(this.value)">
    <p>Effects:</p>
    <button class="button" onclick="setEffect(0)">Off</button>
    <button class="button" onclick="setEffect(1)">Effect 1</button>
    <button class="button" onclick="setEffect(2)">Effect 2</button>
    <button class="button" onclick="setEffect(3)">Effect 3</button>
    <button class="button" onclick="setEffect(4)">Effect 4</button>
    <button class="button" onclick="setEffect(5)">Effect 5</button>
    <button class="button" onclick="setEffect(6)">Audio</button>
    <button class="button" onclick="setEffect(7)">Effect 7</button>
    <button class="button" onclick="setEffect(8)">Effect 8</button>
    <p><button class="button" onclick="goToSleep()">Sleep</button></p>
    <p>Effect Speed:</p>
    <input type="range" class="slider" id="speedSlider" min="0" max="100" onchange="updateEffectSpeed(this.value)">
    <p>Color:</p>
    <input type="color" id="colorPicker" value="#FF0000" onchange="updateColorValue(this.value)">
    
    <script>
      function updateSliderValue(val) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/brightness?value=" + val, true);
        xhr.send();
      }
      function setEffect(effect) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/effect?value=" + effect, true);
        xhr.send();
      }
      function goToSleep() {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/sleep", true);
        xhr.send();
      }
      function updateEffectSpeed(val) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/speed?value=" + val, true);
        xhr.send();
      }
      function updateColorValue(val) {
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/color?value=" + val.substr(1), true);
        xhr.send();
      }
    </script>
  </body>
  </html>
)rawliteral";


void handleSpeed() {
  if (server.hasArg("value")) {
    effectSpeed = server.arg("value").toInt(); // Convert effect speed to integer
    server.send(200, "text/plain", "Effect speed set to " + server.arg("value"));
  } else {
    server.send(400, "text/plain", "Invalid Request");
  }
}

void handleColor() {
  if (server.hasArg("value")) {
    String hexColor = server.arg("value");
    red = strtol(hexColor.substring(0, 2).c_str(), NULL, 16);  // Convert hex to red component
    green = strtol(hexColor.substring(2, 4).c_str(), NULL, 16); // Convert hex to green component
    blue = strtol(hexColor.substring(4, 6).c_str(), NULL, 16);  // Convert hex to blue component
    server.send(200, "text/plain", "Color set to #" + server.arg("value"));
  } else {
    server.send(400, "text/plain", "Invalid Request");
  }
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  pinMode(mic, INPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password, 6); // Using channel 6
  Serial.println("AP started. SSID: " + String(ssid) + " Pass: " + String(password));

  ArduinoOTA.setHostname("ESP32-OTA");
  ArduinoOTA.begin();
  Serial.println("OTA Ready");

  server.on("/", []() { server.send(200, "text/html", index_html);
  });
  
  server.on("/effect", []() {
    if (server.hasArg("value")) {
      currentEffect = server.arg("value").toInt();
      server.send(200, "text/plain", "Effect changed to " + server.arg("value"));
    } else {
      server.send(400, "text/plain", "Invalid Request");
    }
  });
  
  server.on("/brightness", []() {
    if (server.hasArg("value")) {
      int newBrightness = server.arg("value").toInt();
      adjustBrightness(newBrightness);

      server.send(200, "text/plain", "Brightness set to " + server.arg("value"));
    } else {
      server.send(400, "text/plain", "Invalid Request");
    }
  });

    server.on("/speed", handleSpeed);  // Link the handler to the route
    server.on("/color", handleColor);

  server.on("/sleep", []() {
    server.send(200, "text/plain", "Going to sleep now");
    delay(1000);
    esp_deep_sleep_start();
  });

  server.on("/speed", []() {
        effectSpeed = server.arg("value").toInt(); // Convert effect speed to integer
    server.send(200, "text/plain", "Effect speed set to " + server.arg("value"));
  });
  
  server.on("/color", []() {
    colorValue = server.arg("value");
    String hexColor = server.arg("value");

    server.send(200, "text/plain", "Color set to #" + server.arg("value"));
  });

  server.begin();
  Serial.println("HTTP server started");
}

void effect0() {
 FastLED.clear();
 FastLED.show();
}

void effect1() {

   for (int i =0; i<50;i++){
  leds[i] = CRGB(red, green, blue);
  delay(effectSpeed);
  leds[i-1] = CRGB(0, 0, 0);
  FastLED.show();
   }
}

void effect2() {

  static uint8_t hue = 0;
  fill_rainbow(leds, NUM_LEDS, hue, 7); // 7 is the color spread
  FastLED.show();
  hue++;
  delay(effectSpeed);  // Smooth transition delay
}

void effect3() {

  fadeToBlackBy(leds, NUM_LEDS, 20);  // Fade the previous LED trail
  leds[pos] = CHSV((pos * 255) / NUM_LEDS, 255, 255);
  FastLED.show();
  
  pos += direction;
  if (pos == NUM_LEDS || pos == -1) {
    direction *= -1;  // Reverse direction when reaching the ends
    pos += direction;
  }
  delay(effectSpeed);  // Adjust for smoother or faster bouncing
}

void effect4() {

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((i * 255) / NUM_LEDS, 255, 255);  // Vary hue as the strip fills
    FastLED.show();
    delay(effectSpeed);  // Adjust for faster or slower fill
  }
  
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    leds[i] = CRGB::Black;  // Turn off LEDs one by one
    FastLED.show();
    delay(effectSpeed);
  }
}

void effect5(){
             for (int i=0;i<50;i++){
            leds[i] = CRGB(0, 10, 0);
            leds[50-i] = CRGB(0, 10, 0);
            FastLED.show();
            delay(200);
           }
           for (int i=25;i<50;i++){
            leds[i] = CRGB(0, 0, 0);
            leds[25-i] = CRGB(0, 0, 0);
            FastLED.show();
            delay(200);
           }
}

void effect6(){

            int db = map(analogRead(2),0,4096,0,50);
             for (int i=0;i<db;i++){
            leds[i] = CRGB(200, 70, 130);
           }
            FastLED.show();

           delay(50);
           for (int i=0;i<db;i++){
            leds[i] = CRGB(0, 0, 0);
           }
          FastLED.show();

}



void loop() {
    ArduinoOTA.handle();
    server.handleClient();



    switch (currentEffect) {
        case 0:
            effect0();
            break;
        case 1:
            effect1();
            break;
        case 2:
            effect2();
            break;
        case 3: 
           effect3();
           break;
        case 4: 
            effect4();
          break;
        case 5: 
            effect5();
           break;
        case 6: 
           effect6();           
          break;
        case 7: 
            for(int i=0;i<50;i++){
            leds[i] = CRGB(random(0,111), random(0,111), random(0,111));
            FastLED.show();   
            delay(100);             
            }
          
        break;
    }
}
