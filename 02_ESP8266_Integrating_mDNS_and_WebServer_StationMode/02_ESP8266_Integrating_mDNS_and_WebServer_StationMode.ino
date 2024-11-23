#include <ESP8266WiFi.h>        // Include the ESP8266 Wi-Fi library
#include <ESP8266mDNS.h>        // Include the mDNS library for ESP8266
#include <ESP8266WebServer.h>   // Include the ESP8266WebServer library for handling HTTP requests

const char* ssid = "Laptop";            // Wi-Fi SSID (your Wi-Fi network name)
const char* password = "8918172922";    // Wi-Fi password
const char* hostname = "esp8266";       // mDNS hostname for your ESP8266 (used for mDNS resolution)

ESP8266WebServer server(80);            // Create a web server instance on port 80

void handleRoot();  // Forward declaration of the handleRoot function

void setup() {
  // Start serial communication with 9600 baud rate
  Serial.begin(9600);
  Serial.println("\nStarting ESP8266 mDNS Basic Code...");  // Print start message to serial monitor
  delay(500);  // Short delay for system stability

  // Connect to Wi-Fi network using the provided SSID and password
  WiFi.begin(ssid, password);  
  Serial.print("Connecting to WiFi..");  // Print connecting message to serial monitor
  while (WiFi.status() != WL_CONNECTED) {  // Wait until the Wi-Fi connection is established
    delay(500);  // Wait for 500ms before trying again
    Serial.print(".");  // Print a dot to indicate the connection is in progress
  }
  Serial.println("\nWiFi connected.");  // Print Wi-Fi connected message
  Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());  // Print the ESP8266's IP address

  // Start the mDNS responder with the specified hostname
  if (MDNS.begin(hostname)) {  
    Serial.println("mDNS responder started.");  // If mDNS started successfully
    Serial.printf("You can access your ESP8266 at > http://%s.local\n", hostname);  // Print mDNS URL
  } else {
    Serial.println("Error starting mDNS responder.");  // Print error message if mDNS fails
  }

  // Define the web server routes
  server.on("/", HTTP_GET, handleRoot);  // When the root URL is accessed, call the handleRoot function
  
  // Start the web server
  server.begin();
  Serial.println("HTTP server started");  // Print confirmation when the HTTP server starts
}

void loop() {
  // Continuously handle mDNS queries (this keeps mDNS running)
  MDNS.update();  

  // Handle client requests
  server.handleClient();
}

// Function to handle the root path ("/") and send a response to the client
void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP8266!");  // Send a simple text response to the client
}



