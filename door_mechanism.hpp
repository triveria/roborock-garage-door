#pragma once
#include <Adafruit_PWMServoDriver.h>

enum class Door_state_e {undefined, closed, open, somewhere};


class Door {

    private:
        int _position;
        Door_state_e _door_state;
        uint8_t _servo_board_address = 0x40;
        Adafruit_PWMServoDriver _pwm = Adafruit_PWMServoDriver(_servo_board_address);
        uint8_t _servo_right_idx = 0; // slot on servo board
        uint8_t _servo_left_idx = 1; // slot on servo board

    public:
        Door();
        void open_up();
        void close_down();
        void find_servo_position();
};
