#define trigPin 8
#define echoPin 13
#define buzzerPin 57
#define SHOCK 18

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

const int waterSensorPin = A7;

const int sensorPin = A0;
const int ledPin1 = 11;
const int ledPin2 = 56;

const int DIRFL = 2;
const int PWMFL = 3;
const int DIRBL = 7;
const int PWMBL = 6;

const int DIRFR = 4;
const int PWMFR = 5;
const int DIRBR = 59;
const int PWMBR = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(SHOCK, INPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  go_forward();

  lcd.init();
  lcd.backlight();
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  Serial.println(analogRead(sensorPin));
  int value = analogRead(sensorPin);

  if(value > 750) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  } else {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
  }

  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int a = digitalRead(SHOCK);
  int sensorValue = analogRead(waterSensorPin);
  float waterlevel = map(sensorValue, 0, 1023, 0, 50);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (a ==HIGH) {
    lcd.setCursor(2,0);
    lcd.print("shock danger");
  }

  else {
    lcd.setCursor(2,0);
    lcd.print("shock safty  ");
  }

  if (waterlevel > 15 && waterlevel <= 20) {
    lcd.setCursor(2,1);
    lcd.print("water warning ");
  } else if (waterlevel >20) {
    lcd.setCursor(2,1);
    lcd.print("water danger ");
  } else {
    lcd.setCursor(2,1);
    lcd.print("water safty  ");
  }

  if (distance < 20) {
    if(a==HIGH) {
      tone(buzzerPin, 200);
    }
    else {
      tone(buzzerPin, 587.33,50);
    }
    stop_driving();
  }

  else {
    if(a==HIGH) {
      tone(buzzerPin, 200);
    }
    else {
      noTone(buzzerPin);
    }
  }
    delay(300);
}

void motor_setup(){
    pinMode(DIRFL, OUTPUT);
    pinMode(DIRBL, OUTPUT);

    digitalwrite(DIRFL, LOW);
    analogWrite(PWMFL,0);
    digitalwrite(DIRBL, LOW);
    analogWrite(PWMBL,0);

    pinMode(DIRFR, OUTPUT);
    pinMode(DIRBR, OUTPUT);

    digitalwrite(DIRFR, LOW);
    analogWrite(PWMFR,0);
    digitalwrite(DIRBR, LOW);
    analogWrite(PWMBR,0);
}

void go_forward(){
    digitalWrite(DIRFL, LOW);
    analogWrite(PWMFL,255);
    digitalWrite(DIRBL, LOW);
    analogWrite(PWMBL,255);

    digitalWrite(DIRFR, LOW);
    analogWrite(PWMFR,255);
    digitalWrite(DIRBR, LOW);
    analogWrite(PWMBR,255);
}

void stop_driving(){
    digitalWrite(DIRFL, LOW);
    analogWrite(PWMFL,0);
    digitalWrite(DIRBL, LOW);
    analogWrite(PWMBL,0);

    digitalWrite(DIRFR, LOW);
    analogWrite(PWMFR,0);
    digitalWrite(DIRBR, LOW);
    analogWrite(PWMBR,0);
}