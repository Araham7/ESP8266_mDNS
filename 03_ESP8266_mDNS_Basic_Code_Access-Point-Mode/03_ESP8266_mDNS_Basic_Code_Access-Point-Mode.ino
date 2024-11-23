#include <ESP8266WiFi.h>    // Include the ESP8266 Wi-Fi library
#include <ESP8266mDNS.h>    // Include the mDNS library for ESP8266

const char* ssid = "ESP8266-Access-Point";   // Wi-Fi SSID for the access point
const char* password = "123456789";          // Wi-Fi password for the access point
const char* hostname = "esp8266";            // mDNS hostname

void setup() {
  // Start serial communication with 9600 baud rate
  Serial.begin(9600); 
  Serial.println("\nStarting ESP8266 Access Point Mode...");  // Print start message
  delay(35);  // Short delay for stability

  // Start Wi-Fi in Access Point mode
  WiFi.softAP(ssid, password);  
  Serial.print("Setting up Access Point..");   // Print setting up AP message
  while (WiFi.softAPgetStationNum() == 0) {  // Wait for at least one client to connect
    delay(500);  // Wait for 500ms
    Serial.print(".");  // Print dot to indicate AP setup progress
  }
  Serial.println("\nAccess Point Started.");  // Print AP started message
  Serial.printf("AP IP Address: %s\n", WiFi.softAPIP().toString().c_str());  // Print AP IP address

  // Start mDNS with the defined hostname
  if (MDNS.begin(hostname)) {  
    Serial.println("mDNS responder started.");  // If mDNS started successfully
    Serial.printf("You can access your ESP8266 AP at http://%s.local\n", hostname);  // Print mDNS URL
  } else {
    Serial.println("Error starting mDNS responder.");  // Print error message if mDNS fails
  }
}

void loop() {
  // Continuously handle mDNS queries
  MDNS.update();  
}



