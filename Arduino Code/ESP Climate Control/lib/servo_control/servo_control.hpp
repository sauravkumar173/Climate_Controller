#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <Servo.h>

// Defines for servo motor delays to control position
#define SERVO_PIN 16
#define SERVO_QUARTER_PAN_DELAY 313
#define SERVO_PAN_LEFT 0
#define SERVO_PAN_RIGHT 180
#define SERVO_PAN_STOP 92

// Position of fan at various speeds
#define FAN_POS_0 0
#define FAN_POS_1 1
#define FAN_POS_2 2
#define FAN_POS_3 3

void init_servo_motor(void);
void pan_motor_left(void);
void pan_motor_right(void);
int get_motor_position(void);
#endif