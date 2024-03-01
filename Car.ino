#include <WiFi.h>

WiFiServer server(80);

const char* ssid = "GNXS-3AD4B8";
const char* password = "1234567890";

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char command = client.read();
        processCommand(command);
      }
    }
    client.stop();
  }
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");
}

void processCommand(char command) {
  switch (command) {
    case 'F':
      forward();
      break;
    case 'B':
      back();
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'O':
      Fleft();
      break;
    case 'N':
      Fright();
      break;
    case 'P':
      Bleft();
      break;
    case 'M':
      Bright();
      break;
    default:
      stop();
  }
}

void forward() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}

void back() {
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

void left() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);

void right() {
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
}

void stop() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void Fleft() {
  right();
  forward();
}

void Fright() {
  left();
  forward();
}

void Bleft() {
  left();
  back();
}

void Bright() {
  right();
  back();
}
