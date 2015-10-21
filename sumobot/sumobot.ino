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
  see_eye("left");
  see_eye("right");
  Serial.println("");
  delay(100);
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

void spin(String dir) {
  int motor_fwd_in1;
  int motor_fwd_in2;
  int motor_fwd_pwm;
  int motor_bkwd_in1;
  int motor_bkwd_in2;
  int motor_bkwd_pwm;

  if ( dir == "right") {
    dir = "Right";
    motor_fwd_in1 = motor_left_in1;
    motor_fwd_in2 = motor_left_in2;
    motor_fwd_pwm = motor_left_pwm;
    motor_bkwd_in1 = motor_right_in1;
    motor_bkwd_in2 = motor_right_in2;
    motor_bkwd_pwm = motor_right_pwm;
  } else {
    dir = "Left";
    motor_fwd_in1 = motor_right_in1;
    motor_fwd_in2 = motor_right_in2;
    motor_fwd_pwm = motor_right_pwm;
    motor_bkwd_in1 = motor_left_in1;
    motor_bkwd_in2 = motor_left_in2;
    motor_bkwd_pwm = motor_left_pwm;
  }

  // Step forward
  digitalWrite(motor_fwd_in1, HIGH);
  digitalWrite(motor_fwd_in2, LOW);
  analogWrite(motor_fwd_pwm, 255);

  // Step backward
  digitalWrite(motor_bkwd_in1, LOW);
  digitalWrite(motor_bkwd_in2, HIGH);
  analogWrite(motor_bkwd_pwm, 255);
}

void all_stop() {
  digitalWrite(motor_left_in1, LOW);
  digitalWrite(motor_left_in2, LOW);
  digitalWrite(motor_right_in1, LOW);
  digitalWrite(motor_right_in2, LOW);
}

void ramming_speed() {
  digitalWrite(motor_left_in1, HIGH);
  digitalWrite(motor_left_in2, LOW);
  analogWrite(motor_left_pwm, 255);
  digitalWrite(motor_right_in1, HIGH);
  digitalWrite(motor_right_in2, LOW);
  analogWrite(motor_right_pwm, 255);
}

