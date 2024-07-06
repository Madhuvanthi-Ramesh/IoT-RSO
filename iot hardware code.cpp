#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <SPI.h>
#include <NewPing.h>

const char* ssid = "OnePlus Nord 2T 5G";
const char* password = "11111111";

const char* thingSpeakAddress = "api.thingspeak.com";
const String writeAPIKey = "6OFQJQBV1GDI1KN1";  // Replace with your ThingSpeak Write API Key

#define TRIG_PIN1 D2
#define ECHO_PIN1 D1
#define TRIG_PIN2 D5
#define ECHO_PIN2 D6

NewPing sonar1(TRIG_PIN1, ECHO_PIN1);
NewPing sonar2(TRIG_PIN2, ECHO_PIN2);

File dataFile;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");



  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int distance1 = sonar1.ping_cm();
    int distance2 = sonar2.ping_cm();

    Serial.print("Distance Sensor 1: ");
    Serial.print(distance1);
    Serial.print(" cm, ");
    Serial.print("Distance Sensor 2: ");
    Serial.print(distance2);
    Serial.println(" cm");



    // Update ThingSpeak channel
    ThingSpeak.setField(1, distance1);
    ThingSpeak.setField(2, distance2);
    int httpCode = ThingSpeak.writeFields(1);

    if (httpCode == 200) {
      Serial.println("ThingSpeak update successful.");
    } else {
      Serial.println("ThingSpeak update failed. Error code: " + String(httpCode));
    }

    delay(10000);  // Adjust the delay as needed
  }
}
