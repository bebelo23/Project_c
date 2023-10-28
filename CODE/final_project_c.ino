#define BLYNK_TEMPLATE_ID "TMPL6ny8ENg4V"  // กำหนด ID ของ Blynk Template
#define BLYNK_TEMPLATE_NAME "Plant Watering System"  // กำหนดชื่อของ Blynk Template
#define BLYNK_AUTH_TOKEN "dAfTP9_CCFU3yQtux7hi6u9MuOVaYZDe"  // กำหนด Blynk Auth Token

#include <Wire.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define sensor 33  // กำหนดขาที่ต่อกับเซ็นเซอร์อัลตราโซนิก (ultrasonic sensor)
#define relay 4  // กำหนดขาที่ต่อกับรีเลย์

BlynkTimer timer;

// Enter your Auth token
char auth[] = "dAfTP9_CCFU3yQtux7hi6u9MuOVaYZDe";

//Enter your WIFI SSID and password
char ssid[] = "boomie";
char pass[] = "00000000";

void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);  // เริ่มต้นการเชื่อมต่อ Blynk ด้วย Auth Token, SSID และ Password

  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);  // ตั้งค่าขารีเลย์ให้ปิดเริ่มต้น
}

// ฟังก์ชันสำหรับดึงค่าเซ็นเซอร์อัลตราโซนิก (ultrasonic sensor)
void soilMoisture() {
  int value = analogRead(sensor);  // อ่านค่าจากเซ็นเซอร์
  value = map(value, 0, 4095, 0, 100);  // แปลงค่าให้อยู่ในช่วง 0-100

  Blynk.virtualWrite(V0, value);  // ส่งค่าไปยังแอป Blynk ที่ Widget V0
  Serial.println(value);  // แสดงค่าที่ Serial Monitor
  if (value <= 50) {
    Blynk.logEvent("plant_watering_system");  // ถ้าค่าน้ำเซ็นเซอร์ต่ำกว่าหรือเท่ากับ 50 ให้บันทึกเหตุการณ์ "plant_watering_system" ใน Blynk
  }
}

// ฟังก์ชันสำหรับตรวจสอบค่าจากปุ่มที่แอป Blynk กด (Widget Button)
BLYNK_WRITE(V1) {
  bool Relay = param.asInt();  // อ่านค่าที่ส่งมาจาก Widget V1
  if (Relay == 1) {
    digitalWrite(relay, LOW);  // เปิดรีเลย์
  } else {
    digitalWrite(relay, HIGH);  // ปิดรีเลย์
  }
}

void loop() {
  soilMoisture();  // เรียกใช้ฟังก์ชัน soilMoisture() เพื่อดึงค่าเซ็นเซอร์
  Blynk.run();  // ให้ Blynk library ทำงาน
  delay(200);  // หน่วงเวลาเล็กน้อยเพื่อป้องกันการทำงานเกินไป
}
