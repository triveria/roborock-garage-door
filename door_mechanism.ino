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


void Door::_move_both_servos(int left_start_position, int right_start_position, int left_end_position, int right_end_position)
{
    float num_steps = 20.f;
    int t_ms = 1000;
    int dt_ms = t_ms / num_steps;
    
    float step_size_left = (left_end_position - left_start_position) / num_steps;
    float step_size_right = (right_end_position - right_start_position) / num_steps;
    for(int i = 0; i < num_steps; i++) {
        int left_position  = left_start_position + i*step_size_left;
        int right_position = right_start_position + i*step_size_right;

        // Serial.println((String)"left: " + left_position + ". right: " + right_position);

        _pwm.setPWM(_servo_left_idx,  0, left_position);
        _pwm.setPWM(_servo_right_idx, 0, right_position);
        delay(dt_ms);
    }
    _pwm.setPWM(_servo_left_idx, 0, left_end_position);
    _pwm.setPWM(_servo_right_idx, 0, right_end_position);
}


void Door::_switch_servos_off()
{
    _pwm.sleep();
}


Door::Door() :
    _servo_board_address(0x40),
    _servo_right_idx(0),
    _servo_left_idx(1)
{
}


void Door::setup()
{
    _pwm = Adafruit_PWMServoDriver(_servo_board_address);
    _pwm.begin();
    delay(10);
    int internal_oscillator_frequency_hz = 27000000;
    _pwm.setOscillatorFrequency(internal_oscillator_frequency_hz);
    _pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    close_down();
}


void Door::open_up()
{
    _pwm.wakeup();
    Serial.println("Opening door...");
    _move_both_servos(DOOR_CLOSE_LEFT, DOOR_CLOSE_RIGHT, DOOR_OPEN_LEFT, DOOR_OPEN_RIGHT);

    _door_state = Door_state_e::open;
}


void Door::close_down()
{
    Serial.println("Closing door...");
    _move_both_servos(DOOR_OPEN_LEFT, DOOR_OPEN_RIGHT, DOOR_CLOSE_LEFT, DOOR_CLOSE_RIGHT);
    _switch_servos_off();

    _door_state = Door_state_e::closed;
}


bool Door::is_open()
{
    bool is_already_open = _door_state == Door_state_e::open;
    Serial.println((String)"is_already_open: " + is_already_open);

    return is_already_open;
}


bool Door::is_closed()
{
    bool is_already_closed = _door_state == Door_state_e::closed;
    Serial.println((String)"is_already_closed: " + is_already_closed);

    return is_already_closed;
}


void Door::set_position_via_comport(uint8_t servo_idx)
{
    if(!(Serial.available() > 0)) {
        return;
    }

    int choice = Serial.parseInt();
    set_position(servo_idx, choice + 100);
    delay(500);
    Serial.println((String)"moving to position: " + choice);
    set_position(servo_idx, choice);
}


void Door::set_position(uint8_t servo_idx, int choice)
{
    _pwm.setPWM(servo_idx, 0, choice);
}


void Door::debug()
{
    if(is_closed()){
        open_up();
    }

    if(is_open()) {
        close_down();
    }
}
