
/* 
 * SRS Robot Demo (Arduino Uno + ShieldBot, the older version of the kit)
 * Demo using Parallax Boe-Bot Digital Encoder Kit for PID motion control
 * Wired as shown here https://www.parallax.com/sites/default/files/downloads/28107-Boe-Bot-Digital-Encoder-Product-Guide-v2.0.pdf
 * Details on interrupts here https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * Will Smith 2020
 */

#include "MotorControl.h"


static int leftTarget = 100;
static int rightTarget = 100;

void setup() {
  Serial.begin(115200);
  Serial.print("Robot demo: Initializing...");
  attachMotors(); 
  stopMotors();
  resetEncoders();
  Serial.println("complete.");
}


void loop() {

  // NOTE: If you are powering the robot over only USB (battery pack unplugged)
  // the encoders may brown out and you'll get weird interrupt behavior.
  // To test encoders, you may wish to power breadboard only (switch at 1) 
  // and manually move the wheels, otherwise make sure the battery pack is plugged in 
  // when you set the switch to 2.

  simpleTestLoop();
}

void simpleTestLoop() {
  Serial.println("Moving Forward");
  testForward();
  delay(1000);
  stopMotors();
  printEncoderCounts();
  delay(1000);

  Serial.println("Moving Back");
  testBack();
  delay(1000);
  stopMotors();
  printEncoderCounts();
  delay(1000);  
}
