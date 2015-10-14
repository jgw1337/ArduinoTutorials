/**
 * HC-SR04 Ping distance sensor:
 * VCC to arduino 5v 
 * GND to arduino GND
 * Echo to Arduino pin 7 
 * Trig to Arduino pin 8
 */

#define eyes1_echo 7
#define eyes1_trig 8
long duration, inches, cm;

void setup() {
  Serial.begin (9600);
  pinMode(eyes1_trig, OUTPUT);
  pinMode(eyes1_echo, INPUT);
}

void loop() {
  digitalWrite(eyes1_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(eyes1_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(eyes1_trig, LOW);
  duration = pulseIn(eyes1_echo, HIGH);
  inches = duration / 74 / 2;
  cm = (duration/2) / 29.1;

  // Five feet is the max range
  if (inches / 12 <= 5){
    Serial.print(inches);
    Serial.print(" in, ");
    Serial.print(cm);
    Serial.println(" cm");
  } else {
    Serial.println("Out of range");
  }
  delay(100);
}
