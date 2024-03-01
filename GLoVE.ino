#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>

int X = 0;
int Y = 0;
Adafruit_MPU6050 mpu;
WiFiClient client;

const char* ssid = "GNXS-3AD4B8";
const char* password = "1234567890";
const char* host = "192.168.1.50";

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  Wire.begin();
  
  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  delay(1000);
}

void loop() {
  sensors_event_t event;
  mpu.getEvent(&event);
  
  X = event.acceleration.x;
  Y = event.acceleration.y;

  if(X > -10 && X < 10 && Y > -10 && Y < 10) {
    sendCommand('S');
  }
  if (X < -50 && Y > -10 && Y < 10) {
    sendCommand('F');
  }
  if (X > 50 && Y > -10 && Y < 10) {
    sendCommand('B');
  }
  if (Y < -50 && X > -10 && X < 10) {
    sendCommand('R');
  }
  if (Y > 50 && X > -10 && X < 10) {
    sendCommand('L');
  }
  if (Y < -50 && X < -30) {
    sendCommand('N');
  }
  if (Y < -50 && X > 30) {
    sendCommand('M');
  }
  if (Y > 50 && X < -30) {
    sendCommand('O');
  }
  if (Y > 50 && X > 40) {
    sendCommand('P');
  }
  delay(100); // Adjust delay if needed
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

void sendCommand(char command) {
  if(!client.connect(host, 80)) {
    Serial.println("Connection failed");
    return;
  }
  client.print(String(command));
  client.stop();
}
