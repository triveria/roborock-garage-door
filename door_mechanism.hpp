#pragma once
#include <Adafruit_PWMServoDriver.h>

enum class Door_state_e {open, closed};


class Door {

    private:
        int _position;
        Door_state_e _door_state;
        uint8_t _servo_board_address;
        Adafruit_PWMServoDriver _pwm;
        uint8_t _servo_right_idx;
        uint8_t _servo_left_idx;
        
        void _move_both_servos(int left_start_position, int right_start_position, int left_end_position, int right_end_position);
        void _switch_servos_off();

    public:
        Door();
        void setup();
        void open_up();
        void close_down();
        void set_servo_position_via_comport(uint8_t servo_idx);
        bool is_closed();
        bool is_open();
        void set_position(uint8_t servo_idx, int choice);
        void debug();
};
