#include "door_mechanism.hpp"
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>



#define SERVO_MIN  66  // This is the 'minimum' pulse length count (out of 4096). Tweak for each servo.
#define SERVO_MAX  497 // This is the 'maximum' pulse length count (out of 4096). Tweak for each servo.

#define DOOR_OPEN_RIGHT 111
#define DOOR_CLOSE_RIGHT 273

#define DOOR_OPEN_LEFT 262
#define DOOR_CLOSE_LEFT 74

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


int position_left = SERVO_MIN;


Door::Door()
{
    _pwm.begin();
    int internal_oscillator_frequency_hz = 27000000;
    _pwm.setOscillatorFrequency(internal_oscillator_frequency_hz);
    _pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}


void Door::open_up()
{
    int left_start_position = DOOR_CLOSE_LEFT;
    int left_end_position = DOOR_OPEN_LEFT;
    int right_start_position = DOOR_CLOSE_RIGHT;
    int right_end_position = DOOR_OPEN_RIGHT;

    float num_steps = 20.f;
    
    float step_size_left = (left_end_position - left_start_position) / num_steps;
    float step_size_right = (right_end_position - right_start_position) / num_steps;
    for(int i = 0; i < num_steps; i++) {
        _pwm.setPWM(_servo_left_idx, 0, left_start_position + i*step_size_left);
        _pwm.setPWM(_servo_right_idx, 0, right_start_position + i*step_size_right);
        delay(50);
    }
    _pwm.setPWM(_servo_left_idx, 0, left_end_position);
    _pwm.setPWM(_servo_right_idx, 0, right_end_position);
}


void Door::close_down()
{
    int left_start_position = DOOR_OPEN_LEFT;
    int left_end_position = DOOR_CLOSE_LEFT;
    int right_start_position = DOOR_OPEN_RIGHT;
    int right_end_position = DOOR_CLOSE_RIGHT;
    
    float num_steps = 20.f;
    
    float step_size_left = (left_end_position - left_start_position) / num_steps;
    float step_size_right = (right_end_position - right_start_position) / num_steps;
    for(int i = 0; i < num_steps; i++) {
        _pwm.setPWM(_servo_left_idx, 0, left_start_position + i*step_size_left);
        _pwm.setPWM(_servo_right_idx, 0, right_start_position + i*step_size_right);
        delay(50);
    }
    _pwm.setPWM(_servo_left_idx, 0, left_end_position);
    _pwm.setPWM(_servo_right_idx, 0, right_end_position);
}


void Door::find_servo_position()
{
    uint8_t servo = _servo_left_idx;
    if(Serial.available() > 0) {
        int choice = Serial.parseInt();
        if ((SERVO_MIN <= choice) && (choice <= SERVO_MAX)) {
            _pwm.setPWM(servo, 0, DOOR_CLOSE_LEFT);
            delay(500);
            Serial.println((String)"moving to position: " + choice);
            _pwm.setPWM(_servo_left_idx, 0, choice);
        }
    }
}
