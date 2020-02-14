#include <Servo.h>

#define LEFT_MOTOR_SERVO_PIN 13
#define RIGHT_MOTOR_SERVO_PIN 12

#define STOP_LEFT 1500
#define STOP_RIGHT 1500
Servo leftServo; 
Servo rightServo; 

void attachMotors() {
  rightServo.attach(RIGHT_MOTOR_SERVO_PIN);
  leftServo.attach(LEFT_MOTOR_SERVO_PIN);
}

void stopMotors() {
  leftServo.writeMicroseconds(STOP_LEFT);
  rightServo.writeMicroseconds(STOP_RIGHT);
}

void testForward() {
  leftServo.writeMicroseconds(STOP_LEFT + 100);
  rightServo.writeMicroseconds(STOP_RIGHT - 100);  
}

void testBack() {
  leftServo.writeMicroseconds(STOP_LEFT - 100);
  rightServo.writeMicroseconds(STOP_RIGHT + 100);  
  
}
