#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "BSNL-b59310";
const char* password = "muha6175";

WebServer server(80);

const int ledPin = 2;

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>LED Control</title>
      <style>
        body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
        a { display: inline-block; margin: 20px; padding: 15px 30px; background-color: #28a745; color: white; text-decoration: none; font-size: 24px; border-radius: 8px; }
        a.off { background-color: #dc3545; }
      </style>
    </head>
    <body>
      <h1>ESP32 LED Control</h1>
      <a href="/on">Turn ON</a>
      <a href="/off" class="off">Turn OFF</a>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  // Redirect back to root page after turning LED ON
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  // Redirect back to root page after turning LED OFF
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Make sure LED is off at start

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

