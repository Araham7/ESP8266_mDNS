#include <ESP8266WiFi.h>    // Include the ESP8266 Wi-Fi library
#include <ESP8266mDNS.h>    // Include the mDNS library for ESP8266

const char* ssid = "Laptop";           // Wi-Fi SSID
const char* password = "8918172922";   // Wi-Fi password
const char* hostname = "esp8266";      // mDNS hostname

void setup() {
  // Start serial communication with 9600 baud rate
  Serial.begin(9600); 
  Serial.println("\nStarting ESP8266 mDNS Basic Code...");  // Print start message
  delay(35);  // Short delay for stability

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);  
  Serial.print("Connecting to WiFi..");   // Print connecting message
  while (WiFi.status() != WL_CONNECTED) {  // Wait until connected to Wi-Fi
    delay(500);  // Wait for 500ms
    Serial.print(".");  // Print dot to indicate connection progress
  }
  Serial.println("\nWiFi connected.");  // Print Wi-Fi connected message
  Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());  // Print the ESP8266 IP address

  // Start mDNS with the defined hostname
  if (MDNS.begin(hostname)) {  
    Serial.println("mDNS responder started.");  // If mDNS started successfully
    Serial.printf("You can access your ESP8266 at http://%s.local\n", hostname);  // Print mDNS URL
  } else {
    Serial.println("Error starting mDNS responder.");  // Print error message if mDNS fails
  }
}

void loop() {
  // Continuously handle mDNS queries
  MDNS.update();  
}



