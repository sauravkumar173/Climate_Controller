#include "servo_control.hpp"

Servo fanMotor;
int fanPosition = FAN_POS_2;

/*
 * @brief: Initialises servo motor
 * @input: void
 * @return: void
 */
void init_servo_motor(void) {

    fanMotor.attach(SERVO_PIN);
}

/*
 * @brief: Pans servo motor left
 * @input: void
 * @return: void
 */
void pan_motor_left(void) {
    // Pans motor only if it is not at position 0
    if (fanPosition != FAN_POS_0) {

        fanMotor.write(SERVO_PAN_LEFT);
        delay(SERVO_QUARTER_PAN_DELAY);
        fanMotor.write(SERVO_PAN_STOP);
        
        fanPosition--;
    }

}

/*
 * @brief: Pans servo motor right
 * @input: void
 * @return: void
 */
void pan_motor_right(void) {
    // Pans motor only if it is not at position 3
    if (fanPosition != FAN_POS_3) {

        fanMotor.write(SERVO_PAN_RIGHT);
        delay(SERVO_QUARTER_PAN_DELAY);
        fanMotor.write(SERVO_PAN_STOP);

        fanPosition++;
    
    }
}

/*
 * @brief: Returns the position of the servo motor
 * @input: void
 * @return: int fanPosition - position of the fan as an integer
 */
int get_motor_position(void) {
    
    return fanPosition;
}
