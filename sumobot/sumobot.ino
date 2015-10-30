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

/**
 * L298N Motor driver
 */

#define motor_left_in1     4
#define motor_left_in2     5
#define motor_left_pwm     9
#define motor_right_in1    6
#define motor_right_in2    7
#define motor_right_pwm   10

void setup() {
  Serial.begin (9600);
  init_eyes();
  init_feet();
}

void loop() {
  if ( isInRange("right_eye") ) {
    all_stop();
  } else {
    go("right", 150);
  }

  if ( isInRange("left_eye") ) {
    go("backward", 150);
  }

/*
  if ( isInRange("ramming_eye") ) {
    ramming_speed();
  } else {
    all_stop();
  }
*/

  Serial.println();
  delay(10);
}


/**
 * Eye Functions
 */
boolean isInRange(String eye) {
  boolean object_detected = false;
  int eye_echo;
  int eye_trig;

  eye.toLowerCase();

  if ( eye == "right_eye" ) {
    eye_echo = right_eye_echo;
    eye_trig = right_eye_trig;
  } else if ( eye == "left_eye" ) {
    eye_echo = left_eye_echo;
    eye_trig = left_eye_trig;
  } else {
    // ramming eye
  }

  digitalWrite(eye_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(eye_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(eye_trig, LOW);
  duration = pulseIn(eye_echo, HIGH);
  inches = duration / 74 / 2;
  cm = (duration/2) / 29.1;

  // Three feet is the max range
  if (inches / 12 <= max_sight_in_feet){
    object_detected = true;
  }

  int max_text_width = 25;
  String padding;
  String strDisplay;
  strDisplay = eye + " eye : " + inches + " in.";
  for (int i = 0; i < max_text_width - strDisplay.length(); i++) {
    padding += " ";
  }
  Serial.print(strDisplay + padding + object_detected + " ; ");

  return object_detected;
}


/**
 * Eye Functions
 */
void init_eyes() {
  pinMode(left_eye_trig, OUTPUT);
  pinMode(left_eye_echo, INPUT);
  pinMode(right_eye_trig, OUTPUT);
  pinMode(right_eye_echo, INPUT);
}


/**
 * Motor Functions
 */
void init_feet() {
  pinMode(motor_left_in1, OUTPUT);
  pinMode(motor_left_in2, OUTPUT);
  pinMode(motor_left_pwm, OUTPUT);
  pinMode(motor_right_in1, OUTPUT);
  pinMode(motor_right_in2, OUTPUT);
  pinMode(motor_right_pwm, OUTPUT);
}


/**
 * Motor Functions
 */
void go(String dir, int speed) {
  dir.toLowerCase();

  if ( dir == "forward" ) {
    dir = "Forward";
    digitalWrite(motor_right_in1, HIGH);
    digitalWrite(motor_right_in2, LOW);

    digitalWrite(motor_left_in1, HIGH);
    digitalWrite(motor_left_in2, LOW);

  } else if ( dir == "backward" ) {
    dir = "Backward";
    digitalWrite(motor_right_in1, LOW);
    digitalWrite(motor_right_in2, HIGH);

    digitalWrite(motor_left_in1, LOW);
    digitalWrite(motor_left_in2, HIGH);

  } else if ( dir == "left" ) {
    dir = "Left";
    digitalWrite(motor_right_in1, HIGH);
    digitalWrite(motor_right_in2, LOW);

    digitalWrite(motor_left_in1, LOW);
    digitalWrite(motor_left_in2, HIGH);

  } else if ( dir == "right" ) {
    dir = "Right";
    digitalWrite(motor_right_in1, LOW);
    digitalWrite(motor_right_in2, HIGH);

    digitalWrite(motor_left_in1, HIGH);
    digitalWrite(motor_left_in2, LOW);

  } else {
    dir = "Spin Right";
    
  }

  // Right
  analogWrite(motor_right_pwm, speed);

  // Left
  analogWrite(motor_left_pwm, speed);

  int max_text_width = 30;
  String padding;
  String strDisplay;
  strDisplay = " dir : " + dir + "; speed : " + speed;
  for (int i = 0; i < max_text_width - strDisplay.length(); i++) {
    padding += " ";
  }
  Serial.print(strDisplay + padding + " ; ");
}


/**
 * Motor Functions
 */
void all_stop() {
  digitalWrite(motor_left_in1, LOW);
  digitalWrite(motor_left_in2, LOW);
  digitalWrite(motor_right_in1, LOW);
  digitalWrite(motor_right_in2, LOW);
}


/**
 * Motor Functions
 */
void ramming_speed() {
  go("forward", 255);
}
