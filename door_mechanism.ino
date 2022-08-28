#include "door_mechanism.hpp"
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>


#define SERVO_MIN  66  // This is the 'minimum' pulse length count (0..4095). Tweak for each servo.
#define SERVO_MAX  497 // This is the 'maximum' pulse length count (0..4095). Tweak for each servo.

#define DOOR_OPEN_RIGHT 111
#define DOOR_CLOSE_RIGHT 260

#define DOOR_OPEN_LEFT 241
#define DOOR_CLOSE_LEFT 73

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


void Door::_move_both_servos(int left_start_position, int right_start_position, int left_end_position, int right_end_position)
{
    float num_steps = 5.f;
    int t_ms = 500;
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
    int wait_until_movement_finished = 500;
    delay(wait_until_movement_finished);
    _switch_servos_off();

    _door_state = Door_state_e::closed;
}


void Door::hold_until_robot_has_left_the_house()
{
    int time_until_robot_has_left_the_house = 10000;
    delay(time_until_robot_has_left_the_house);
}


void Door::hold_until_robot_has_gone_to_sleep()
{
    int time_until_robot_has_gone_to_sleep = 10000;
    delay(time_until_robot_has_gone_to_sleep);
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


uint8_t Door::servo_left_idx()
{
    return _servo_left_idx;
}


uint8_t Door::servo_right_idx()
{
    return _servo_right_idx;
}


void Door::set_position_via_comport(uint8_t servo_idx)
{
    _pwm.wakeup();
    if(!(Serial.available() > 0)) {
        return;
    }

    int choice = Serial.parseInt();
    int missinterpreted_value = 0;
    if (choice == missinterpreted_value) {
        return;
    }
    set_position(servo_idx, choice - 100);
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
