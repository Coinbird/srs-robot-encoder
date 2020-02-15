#include <Servo.h>
#include "Odometry.h"

#define LEFT_MOTOR_SERVO_PIN 13
#define RIGHT_MOTOR_SERVO_PIN 12

// Servo rates for stop (adjust via potentiometer on the servo if moving slowly)
#define STOP_LEFT 1500
#define STOP_RIGHT 1500

// Encoders wired to these pins
#define ENCODER_PIN_LEFT 3
#define ENCODER_PIN_RIGHT 2

// Full speed clockwise = 1.3 ms pulses
// Max speed is +/- 1300 (added to microseconds)
#define MAX_SPEED 200
#define MED_SPEED 50
#define SLOW_SPEED 25
#define MIN_SPEED 15

Servo leftServo; 
Servo rightServo; 

// Encoder counters
volatile int leftMotorDir = 1; // 1 = forward, -1 = reverse 
volatile int leftEncoderTicks = 0; // could be long, for long distance missions?
volatile int rightMotorDir = 1;
volatile int rightEncoderTicks = 0;

// Current motor speeds
#define SPEED_DELTA 10
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

// --- INTERRUPT HANDLERS ---

void leftCounter() {
  // Called by interrrupt handler
  leftEncoderTicks += leftMotorDir;
}

void rightCounter() {
  // Called by interrrupt handler
    rightEncoderTicks += rightMotorDir;
}


// --- SETUP ROUTINES ---

void resetEncoders() {
  leftEncoderTicks = 0;
  rightEncoderTicks = 0;  
}

void attachMotors() {
  rightServo.attach(RIGHT_MOTOR_SERVO_PIN);
  leftServo.attach(LEFT_MOTOR_SERVO_PIN);
  pinMode(ENCODER_PIN_LEFT, INPUT);  
  pinMode(ENCODER_PIN_RIGHT, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_LEFT), leftCounter, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_RIGHT), rightCounter, RISING);  
  resetEncoders();
}


// --- DEBUG / INFO ROUTINES ---

void printEncoderCounts() {
  Serial.print("Left counter ");
  Serial.println(leftEncoderTicks);
  Serial.print("Right counter ");
  Serial.println(rightEncoderTicks);
}

void printDistance() {
  Serial.print("Left distance (mm) ");
  Serial.println(getDistanceMm(leftEncoderTicks));
  Serial.print("Right distance (mm) ");
  Serial.println(getDistanceMm(rightEncoderTicks));
  
}

// --- MOVEMENT COMMANDS ---

void stopMotors() {
  leftServo.writeMicroseconds(STOP_LEFT);
  rightServo.writeMicroseconds(STOP_RIGHT);
}

void leftSpeed(int speed) {
  leftMotorDir = speed > 0 ? 1 : -1; // set motor direction for interrupt encoder counter
  leftServo.writeMicroseconds(STOP_LEFT + speed);  
}

void rightSpeed(int speed) {
  rightMotorDir = speed > 0 ? 1 : -1;
  rightServo.writeMicroseconds(STOP_RIGHT - speed);  // inverse of left
}


void leftTargetSpeedTicks(int desired, int current) {
  // This is basically simple P control
  if (desired > current) {
    leftMotorSpeed += SPEED_DELTA;    
  } else if (desired < current) {
    leftMotorSpeed -= SPEED_DELTA;        
  } // else, stable speed is reached.
  leftSpeed(leftMotorSpeed);
}

void rightTargetSpeedTicks(int desired, int current) {
  if (desired > current) {
    rightMotorSpeed += SPEED_DELTA;    
  } else if (desired < current) {
    rightMotorSpeed -= SPEED_DELTA;        
  }
  // Else... stable.
  rightSpeed(rightMotorSpeed);  
}

void driveStraightMillimeters(float targetMm, int deltaLeft, int deltaRight) {
  // NOTE: Generally, reset encoders before issuing this command
  // Use left encoder as "master" value
  int target = int(targetMm / distancePerTickMm); // from odometry
  if (leftEncoderTicks < target) {
    // TODO adjust track dynamically
    int ticksRemaining = target - leftEncoderTicks;
    // Slow down when we get closer
    leftTargetSpeedTicks(ticksRemaining > 25 ? 5 : 1, deltaLeft);
    rightTargetSpeedTicks(ticksRemaining > 25 ? 5 : 1, deltaRight);
    Serial.print("Target: ");
    Serial.println(target);
    Serial.print("Progress: ");
    Serial.println(leftEncoderTicks);
  }

  if (leftEncoderTicks >= target && leftSpeed > 0) {
    Serial.println("GOAL REACHED.");
    stopMotors();
  }
}

void testForward() {
  leftSpeed(MAX_SPEED);
  rightSpeed(MAX_SPEED);
}

void testBack() {
  leftSpeed(-MAX_SPEED);
  rightSpeed(-MAX_SPEED);
}
