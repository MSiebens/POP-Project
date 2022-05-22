#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define UTC_OFFSET_IN_SECONDS 7200

// Replace with your network credentials
const char* ssid     = "WiFi-Grunebempt";
const char* password = "grune44bempt";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

// Variables to save date and time
int DoorOpenSummer = 7;
int DoorClosedSummer = 19;
int DoorOpenWinter = 8;
int DoorClosedWinter = 20;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(921600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// Initialize a NTPClient to get time
  timeClient.begin();

  pinMode(13, OUTPUT);
}
void loop() {
  digitalWrite(13, LOW);
  timeClient.update();

  Serial.println(timeClient.getHours());

  if (timeClient.getHours() == DoorClosedSummer)
  {
    digitalWrite(13, HIGH);
  }
  
  if (timeClient.getHours() == DoorOpenSummer)
  {
    digitalWrite(13, LOW);
  }

  // if (timeClient.getHours() == DoorClosedWinter)
  // {
  // digitalWrite(13, HIGH);
  // }
  
  // if (timeClient.getHours() == DoorOpenWinter)
  // {
  //   digitalWrite(13, LOW);
  // }

  delay(1000);
}