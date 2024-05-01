#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WebSocketsClient.h>

#define BUTTON1_PIN 5  // up button GPIO5 = D1
#define BUTTON2_PIN 4 // left button, GPIO4 = D2
#define BUTTON3_PIN 0  // down button, GPIO0 = D3
#define BUTTON4_PIN 2 // right button, GPIO2 = D4
#define BUTTON5_PIN 14 // right button, GPIO14 = D5

// variables for reading the button status
int button1_state = 0;
int button2_state = 0;
int button3_state = 0;
int button4_state = 0;
int button5_state = 0;

//const char* ssid = "iPhone (2)"; // Replace with your WiFi network name
//const char* password = "nickisthebest"; // Replace with your WiFi password
const char* ssid = "nate"; // Replace with your WiFi network name
const char* password = "12345678"; // Replace with your WiFi password

WebSocketsClient webSocket; // WebSocket client instance

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WebSocket] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WebSocket] Connected to: %s\n", payload);
      break;
    case WStype_TEXT:
      Serial.printf("[WebSocket] Received text: %s\n", payload);
      break;
  }
}

void setup() {
  Serial.begin(9600); // Start serial communication

  // Configure the ESP8266 pin as a pull-up input: HIGH when the button is open, LOW when pressed.
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(BUTTON5_PIN, INPUT_PULLUP);

  // Setup WiFi
  WiFi.begin(ssid, password); // Connect to the WiFi network

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");

  // Setup WebSocket
  webSocket.begin("172.23.5.70", 8080, "/"); // WebSocket server address and port
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000); // Try to reconnect every 5 seconds

}

void loop() {
  webSocket.loop(); // Allow WebSocket client to process events

  // read the state of the button value:
  button1_state = digitalRead(BUTTON1_PIN);
  button2_state = digitalRead(BUTTON2_PIN);
  button3_state = digitalRead(BUTTON3_PIN);
  button4_state = digitalRead(BUTTON4_PIN);
  button5_state = digitalRead(BUTTON5_PIN);

  // control LEDs according to the state of button
  if (button1_state == LOW) { // button is pressed
    Serial.println("Button 1 PRESSED - UP");
    webSocket.sendTXT("...."); // up = 4
    delay(200); // Debounce delay
    return; // only want one command at a time so break out of the loop iteration
  }
  if (button2_state == LOW) {
    Serial.println("Button 2 PRESSED - LEFT");
    delay(200); // Debounce delay
    webSocket.sendTXT("..."); // left = 3
    return; // only want one command at a time so break out of the loop iteration
  }
  if (button3_state == LOW) {
    Serial.println("Button 3 PRESSED - DOWN");
    webSocket.sendTXT(".."); // down = 2
    delay(200); // Debounce delay
    return; // only want one command at a time so break out of the loop iteration
  }
  if (button4_state == LOW) {
    Serial.println("Button 4 PRESSED - RIGHT");
    webSocket.sendTXT("."); // right = 1
    delay(200); // Debounce delay
    return; // only want one command at a time so break out of the loop iteration
  }
  if (button5_state == LOW) {
    Serial.println("Button 5 PRESSED - ENTER");
    webSocket.sendTXT("....."); // right = 1
    delay(200); // Debounce delay
    return; // only want one command at a time so break out of the loop iteration
  }
   
  delay(200); // Debounce delay

}
