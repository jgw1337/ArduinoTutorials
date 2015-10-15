/**
 * HC-SR04 Ping distance sensor:
 * VCC to arduino 5v 
 * GND to arduino GND
 * Echo to Arduino pin 7 
 * Trig to Arduino pin 8
 */

#define left_eye_echo     11
#define left_eye_trig     12
#define right_eye_echo     2
#define right_eye_trig     3
#define max_sight_in_feet  3
long duration, inches, cm;

void setup() {
  Serial.begin (9600);
  init_eyes();
}

void loop() {
  see_eye("left");
  see_eye("right");
  Serial.println("");
  delay(100);
}


/**
 * Supplemental Functions
 */
void init_eyes() {
  pinMode(left_eye_trig, OUTPUT);
  pinMode(left_eye_echo, INPUT);
  pinMode(right_eye_trig, OUTPUT);
  pinMode(right_eye_echo, INPUT);
}

void see_eye(String dir) {
  int eye_echo;
  int eye_trig;
  int max_text_width = 50;
  String padding;

  if ( dir == "right") {
    dir = "Right";
    eye_echo = right_eye_echo;
    eye_trig = right_eye_trig;
  } else {
    dir = "Left";
    eye_echo = left_eye_echo;
    eye_trig = left_eye_trig;
  }
  
  digitalWrite(eye_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(eye_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(eye_trig, LOW);
  duration = pulseIn(eye_echo, HIGH);
  inches = duration / 74 / 2;
  cm = (duration/2) / 29.1;

  String strDisplay;
  strDisplay = dir + " eye : " + inches + " in.";

  // Three feet is the max range
  if (inches / 12 >= max_sight_in_feet){
    strDisplay += ".. out of range.";
  }

  for (int i = 0; i < max_text_width - strDisplay.length(); i++) {
    padding += " ";
  }

  Serial.print(strDisplay + padding);
}
