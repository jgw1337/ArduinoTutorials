/*
 * Servo wiring
 *  - yellow wire to digital 9
 *  - red wire to 5V
 *  - black wire to ground
 */
#include <Servo.h>

Servo myservo;              // create servo object to control a servo
                            // twelve servo objects can be created on most boards

int pos = 0;                // variable to store the servo position
int servo = 9;              // servo pin X

void setup() {
  myservo.attach(servo);    // attaches the servo on pin X to the servo object
}

void loop() {
  for (pos = 0; pos <= 159; pos += 1) {    // goes from 0 degrees to 159 degrees (my specific servo)
                                           // in 1 degree increments
    myservo.write(pos);                    // tell servo to go to position in variable 'pos'
    delay(5);                              // waits 5ms for the servo to reach the position
  }
  for (pos = 150; pos >= 0; pos -= 1) {    // goes from 150 degrees (my specific servo) to 0 degrees
                                           // in 1 degree increments
    myservo.write(pos);                    // tell servo to go to position in variable 'pos'
    delay(5);                              // waits 5ms for the servo to reach the position
  }
}
