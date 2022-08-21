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
        int _time_of_last_opening;
        int _time_of_last_closing;
        void _move_both_servos(int left_start_position, int right_start_position, int left_end_position, int right_end_position);
        bool _enough_time_passed(unsigned long time_threshold, unsigned long time_of_last_event);
        void _switch_servos_off();

    public:
        Door();
        void open_up();
        void close_down();
        void find_servo_position(uint8_t servo_idx);
        void test();
        bool may_be_opened();
        bool may_be_closed();
};