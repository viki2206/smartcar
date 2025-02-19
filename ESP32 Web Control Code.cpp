#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "your_SSID";         // Your Wi-Fi SSID
const char* password = "your_PASSWORD"; // Your Wi-Fi Password

// Motor pins (change to match your setup)
const int motorLeftForward = D1;
const int motorLeftBackward = D2;
const int motorRightForward = D3;
const int motorRightBackward = D4;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Define motor control pins
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);

  // Define routes for the web page
  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_GET, moveForward);
  server.on("/backward", HTTP_GET, moveBackward);
  server.on("/left", HTTP_GET, turnLeft);
  server.on("/right", HTTP_GET, turnRight);
  
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body><h1>Smart Car Control</h1>";
  html += "<p><a href='/forward'>Move Forward</a></p>";
  html += "<p><a href='/backward'>Move Backward</a></p>";
  html += "<p><a href='/left'>Turn Left</a></p>";
  html += "<p><a href='/right'>Turn Right</a></p>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void moveForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
  server.send(200, "text/html", "Moving Forward");
}

void moveBackward() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, HIGH);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, HIGH);
  server.send(200, "text/html", "Moving Backward");
}

void turnLeft() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, HIGH);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
  server.send(200, "text/html", "Turning Left");
}

void turnRight() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, HIGH);
  server.send(200, "text/html", "Turning Right");
}
