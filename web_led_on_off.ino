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
    </head>
    <body>
      <h2>LED Control</h2>
      <button onclick="toggleLED('on')">Turn ON</button>
      <button onclick="toggleLED('off')">Turn OFF</button>
      <script>
        function toggleLED(state) {
          fetch("/" + state);
        }
      </script>
    </body>
    </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/plain", "LED is ON");
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); Serial.println("Connecting...");
  }
  Serial.println("Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() {
  server.handleClient();
}

