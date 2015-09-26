int led = 13;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  s();
  o();
  s();
  space();
}

void o() {
  dash();
  dash();
  dash();
}

void s() {
  dot();
  dot();
  dot();
}

void space() {
  delay(800);
}

void dot() {
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  delay(200);
}

void dash() {
  digitalWrite(led, HIGH);
  delay(800);
  digitalWrite(led, LOW);
  delay(200);
}

