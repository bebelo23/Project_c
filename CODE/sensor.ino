void setup(){

Serial.begin(115200);

pinMode(4, INPUT);

}

void loop(){

Serial.print("Moisture Sensor Value:");

Serial.println(analogRead(4));

delay(1000);
}
