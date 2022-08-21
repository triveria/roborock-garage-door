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


Door::Door() :
    _time_of_last_opening(0),
    _time_of_last_closing(0)
{
    _pwm.begin();
    int internal_oscillator_frequency_hz = 27000000;
    _pwm.setOscillatorFrequency(internal_oscillator_frequency_hz);
    _pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}


void Door::_move_both_servos(int left_start_position, int right_start_position, int left_end_position, int right_end_position)
{
    float num_steps = 20.f;
    int t_ms = 1000;
    int dt_ms = t_ms / num_steps;
    
    float step_size_left = (left_end_position - left_start_position) / num_steps;
    float step_size_right = (right_end_position - right_start_position) / num_steps;
    for(int i = 0; i < num_steps; i++) {
        _pwm.setPWM(_servo_left_idx, 0, left_start_position + i*step_size_left);
        _pwm.setPWM(_servo_right_idx, 0, right_start_position + i*step_size_right);
        delay(dt_ms);
    }
    _pwm.setPWM(_servo_left_idx, 0, left_end_position);
    _pwm.setPWM(_servo_right_idx, 0, right_end_position);
}


bool Door::_enough_time_passed(unsigned long time_threshold, unsigned long time_of_last_event)
{
    unsigned long current_time = millis();
    unsigned long time_since_last_event = current_time - time_of_last_event;
    bool enough_time_passed = time_since_last_event >= time_threshold;
    if( enough_time_passed ) {
        return true;
    } else {
        return false;
    }
}


bool Door::may_be_opened()
{
    return _enough_time_passed(10000, _time_of_last_closing);
}


bool Door::may_be_closed()
{
    return _enough_time_passed(10000, _time_of_last_opening);
}


void Door::open_up()
{
    _move_both_servos(DOOR_CLOSE_LEFT, DOOR_CLOSE_RIGHT, DOOR_OPEN_LEFT, DOOR_OPEN_RIGHT);

    unsigned long current_time = millis();
    _time_of_last_opening = current_time;
}


void Door::_switch_servos_off()
{
    _pwm.setPWM(_servo_left_idx, 0, 0);
    _pwm.setPWM(_servo_right_idx, 0, 0);
}


void Door::close_down()
{
    _move_both_servos(DOOR_OPEN_LEFT, DOOR_OPEN_RIGHT, DOOR_CLOSE_LEFT, DOOR_CLOSE_RIGHT);
    _switch_servos_off();

    unsigned long current_time = millis();
    _time_of_last_closing = current_time;
}


void Door::find_servo_position(uint8_t servo_idx)
{
    if(!(Serial.available() > 0)) {
        return;
    }

    int choice = Serial.parseInt();
    _pwm.setPWM(servo_idx, 0, choice + 100);
    delay(500);
    Serial.println((String)"moving to position: " + choice);
    _pwm.setPWM(servo_idx, 0, choice);
}

void Door::test()
{
    open_up();
    delay(500);
    close_down();
    delay(500);
}
