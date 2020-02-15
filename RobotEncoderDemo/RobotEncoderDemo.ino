
/* 
 * SRS Robot Demo (Arduino Uno + ShieldBot, the older version of the kit)
 * Demo using Parallax Boe-Bot Digital Encoder Kit for PID motion control
 * Wired as shown here https://www.parallax.com/sites/default/files/downloads/28107-Boe-Bot-Digital-Encoder-Product-Guide-v2.0.pdf
 * Details on interrupts here https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * Will Smith 2020
 */

#include "MotorControl.h"

// Timing for PID Velocity control
unsigned long msLoop = millis();

int lastLeftEncoderTicks = 0;
int lastRightEncoderTicks = 0;

int deltaLeftTicks = 0;
int deltaRightTicks = 0;


// base target speeds in ticks
//int leftSpeed 10
//int rightSpeed 10

void setup() {
  Serial.begin(115200);
  Serial.print("Robot demo: Initializing...");
  attachMotors(); 
  stopMotors();
  resetEncoders();
  Serial.println("complete.");
}



unsigned long reverseTimer = millis();

#define MS_INITIATE_REVERSE 5000

int targetSpeed = 5;
void loop() {

  // NOTE: If you are powering the robot over only USB (battery pack unplugged)
  // the encoders may brown out and you'll get weird interrupt behavior.
  // To test encoders, you may wish to power breadboard only (switch at 1) 
  // and manually move the wheels, otherwise make sure the battery pack is plugged in 
  // when you set the switch to 2.


  if ((millis() - msLoop) > 250) {
    calcTicksDelta();
    driveStraightMillimeters(500, deltaLeftTicks, deltaRightTicks);
    msLoop = millis();   
  }

  
//  if ((millis() - msLoop) > 250) {
//    calcTicksDelta();
//    leftTargetSpeedTicks(targetSpeed, deltaLeftTicks);
//    rightTargetSpeedTicks(targetSpeed, deltaRightTicks);
//    msLoop = millis();   
//  }
//
//  if (millis() - reverseTimer > MS_INITIATE_REVERSE) {
//    // Drive back and forth interestingly
//    if (targetSpeed > 0) {
//      targetSpeed = -5;
//    } else {
//      targetSpeed = 5;
//    }
//    reverseTimer = millis();
//  }

}

void calcTicksDelta() {
  deltaLeftTicks = leftEncoderTicks - lastLeftEncoderTicks;
  deltaRightTicks = rightEncoderTicks - lastRightEncoderTicks;
  
  Serial.println("Deltas: ");
  Serial.println(deltaLeftTicks);
  Serial.println(deltaRightTicks);
  
  lastLeftEncoderTicks = leftEncoderTicks;
  lastRightEncoderTicks = rightEncoderTicks;  
}

void simpleTestLoop() {
  Serial.println("Moving Forward");
  testForward();
  delay(1000);
  stopMotors();
  printEncoderCounts();
  printDistance();
  delay(1000);

  Serial.println("Moving Back");
  testBack();
  delay(1000);
  stopMotors();
  printEncoderCounts();
  printDistance();
  delay(1000);  
}
