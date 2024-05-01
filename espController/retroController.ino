#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// This file is used for testing connecting to WiFi

const char* ssid = "iPhone (2)"; // Replace with your WiFi network name
const char* password = "nickisthebest"; // Replace with your WiFi password

void setup() {
  Serial.begin(9600); // Start the serial communication
  WiFi.begin(ssid, password); // Connect to the WiFi network

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
  makeHTTPSRequest(); // Make the HTTPS request
}

void loop() {
  // Keep the function here to make repeated requests or use deep sleep for battery-driven applications
}

void makeHTTPSRequest() {
  WiFiClientSecure client; // Create a WiFiClientSecure object
  HTTPClient https; // Declare an object of class HTTPClient

  client.setInsecure(); // Use this for testing purposes (ignores SSL certificate errors)
  
  if (https.begin(client, "https://www.google.com")) { // Specify request destination
    int httpCode = https.GET(); // Send the request

    if (httpCode > 0) { // Check the returning code
      String payload = https.getString(); // Get the request response payload
      Serial.println("Received payload:");
      Serial.println(payload);
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpCode);
    }

    https.end(); // Close connection
  } else {
    Serial.println("Unable to connect");
  }
}
