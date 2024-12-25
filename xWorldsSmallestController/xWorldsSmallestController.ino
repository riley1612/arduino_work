#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoOTA.h>


// ESP32 network credentials
const char* ssid = "iLoveMallory";
const char* password = "your_password";

// ESP32 server IP and endpoint
const char* serverIP = "http://192.168.4.1/effect?value=0";


void setup() {
  // Serial.begin(115200);


 ArduinoOTA.setHostname("esp32-ota"); // Optional: Set a hostname for your device 
 ArduinoOTA.begin();
 WiFi.softAP(ssid, password);

  // WiFi.begin(ssid, password);

  // Connect to Wi-Fi
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }
  // Serial.println("Connected to WiFi");

  // // Create a WiFi client
  // WiFiClient client;

  // // Set the effect value to 0 and make an HTTP request
  // int effectValue = 0;
  // String url = String(serverIP);

  // if (WiFi.status() == WL_CONNECTED) {
  //   HTTPClient http;
  //   http.begin(client, url); // Use the client and URL

  //   int httpCode = http.GET();

  //   if (httpCode > 0) {
  //     String payload = http.getString();
  //     Serial.println("HTTP Response code: " + String(httpCode));
  //     Serial.println("Payload: " + payload);
  //   } else {
  //     Serial.println("Error on HTTP request");
  //   }
  //   http.end();
  // }
}

void loop() {
  ArduinoOTA.handle();
  // Nothing to do here
}
