
/* 
 * SRS Robot Demo (Arduino Uno + ShieldBot, the older version of the kit)
 * Demo using Parallax Boe-Bot Digital Encoder Kit for PID motion control
 * Wired as shown here https://www.parallax.com/sites/default/files/downloads/28107-Boe-Bot-Digital-Encoder-Product-Guide-v2.0.pdf
 * Will Smith 2020
 */

#include "MotorControl.h"

int speed = 0;

void setup() {
  attachMotors(); 
}

void loop() {
  testForward();
  delay(1000);
  stopMotors();
  delay(1000);
  testBack();
  delay(1000);
  stopMotors();
  delay(1000);
}
