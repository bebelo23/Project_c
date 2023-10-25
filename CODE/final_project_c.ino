#define BLYNK_TEMPLATE_ID "TMPL6ny8ENg4V"
#define BLYNK_TEMPLATE_NAME "Plant Watering System"
#define BLYNK_AUTH_TOKEN "dAfTP9_CCFU3yQtux7hi6u9MuOVaYZDe"
#include <Wire.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define sensor 33
#define relay 4

BlynkTimer timer;

// Enter your Auth token
char auth[] = "dAfTP9_CCFU3yQtux7hi6u9MuOVaYZDe";

//Enter your WIFI SSID and password
char ssid[] = "boomie";
char pass[] = "00000000";

void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

//Get the ultrasonic sensor values
void soilMoisture() {
  int value = analogRead(sensor);
  value = map(value, 0, 4095, 0, 100);

  Blynk.virtualWrite(V0, value);
  Serial.println(value);
  if (value <= 50)
  {
    Blynk.logEvent("plant_watering_system");
  }
}

//Get the button value
BLYNK_WRITE(V1) {
  bool Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(relay, LOW);
  } else {
    digitalWrite(relay, HIGH);
  }
}

void loop() {
  soilMoisture();
  Blynk.run();  // Run the Blynk library
  delay(200);
}
