/**
 * HC-SR04 Ping distance sensor:
 * VCC to arduino 5v 
 * GND to arduino GND
 * Echo to Arduino pin 7 
 * Trig to Arduino pin 8
 */

#define right_eye_echo 7
#define right_eye_trig 8
#define max_sight_in_feet 5
long duration, inches, cm;

void setup() {
  Serial.begin (9600);
  init_right_eye();
}

void loop() {
  see_right_eye();
  delay(100);
}

void init_right_eye() {
  pinMode(right_eye_trig, OUTPUT);
  pinMode(right_eye_echo, INPUT);
}

void see_right_eye() {
  digitalWrite(right_eye_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(right_eye_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(right_eye_trig, LOW);
  duration = pulseIn(right_eye_echo, HIGH);
  inches = duration / 74 / 2;
  cm = (duration/2) / 29.1;

  // Three feet is the max range
  Serial.print("Right eye : ");
  Serial.print(inches);
  Serial.print(" in, ");
  Serial.print(cm);
  Serial.print(" cm");
  if (inches / 12 <= max_sight_in_feet){
  } else {
    Serial.print(". Out of range");
  }
  Serial.println("");
}
