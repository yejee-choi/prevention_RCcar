#define trigPin 8
#define echoPin 13
#define buzzerPin 57

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance < 20) {
    tone(buzzerPin, 587.33,50);
  }

  else if {
    tone(buzzerPin, 415.30,200);
  }
  
  else {
    noTone(buzzerPin);
  }

  delay(300);
}