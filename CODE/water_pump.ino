int pinRelay = 13;
int humidity = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinRelay, OUTPUT);

}

void loop() {
  humidity = analogRead(0);
  Serial.print("humidity : ") Serial.printIn(humidity);

  if(humidity > 700){
    digitalWrite(pinRelay, HIGH);

  }
  else if(humidity <= 700){
    digitalWrite(pinRelay, LOW);
  }

  delay(1000);
}
