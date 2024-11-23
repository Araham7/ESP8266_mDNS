#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

const char* ssid = "Laptop";
const char* password = "8918172922";
const char* hostname = "esp8266";

void setup() {
  // Start serial communication
  Serial.begin(9600);
  Serial.println("\nStarting ESP8266 mDNS Basic Code...");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());

  // Start mDNS
  if (MDNS.begin(hostname)) {
    Serial.println("mDNS responder started.");
    Serial.printf("You can access your ESP8266 at http://%s.local\n", hostname);
  } else {
    Serial.println("Error starting mDNS responder.");
  }
}

void loop() {
  // Handle mDNS queries
  MDNS.update();
}




