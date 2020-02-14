#include <Servo.h>

#define LEFT_MOTOR_SERVO_PIN 13
#define RIGHT_MOTOR_SERVO_PIN 12

// Servo rates for stop (adjust via potentiometer on the servo if moving slowly)
#define STOP_LEFT 1500
#define STOP_RIGHT 1500

// Encoders wired to these pins
#define ENCODER_PIN_LEFT 3
#define ENCODER_PIN_RIGHT 2

Servo leftServo; 
Servo rightServo; 

// Encoder counters
volatile int leftMotorDir = 1; // 1 = forward, -1 = reverse 
volatile int leftEncoderCount = 0;
volatile int rightMotorDir = 1;
volatile int rightEncoderCount = 0;

void leftCounter() {
  // Called by interrrupt handler
  leftEncoderCount += leftMotorDir;
}

void rightCounter() {
  // Called by interrrupt handler
    rightEncoderCount += rightMotorDir;
}

void resetEncoders() {
  leftEncoderCount = 0;
  rightEncoderCount = 0;  
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

void printEncoderCounts() {
  Serial.print("Left counter ");
  Serial.println(leftEncoderCount);
  Serial.print("Right counter ");
  Serial.println(rightEncoderCount);
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

void testForward() {
  leftSpeed(50);
  rightSpeed(50);
}

void testBack() {
  leftSpeed(-50);
  rightSpeed(-50);
}
