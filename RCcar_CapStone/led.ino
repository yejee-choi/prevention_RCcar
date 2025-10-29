const int sensorPin = A0;
const int ledPin1 = 11;
const int ledPin2 = 56;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  int value = analogRead(sensorPin);
  
  if (sensorValue > 750) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  } else {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
  }
  delay(100);
}