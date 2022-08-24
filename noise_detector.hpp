#pragma once


class Microphone {
    private:
        int _microphone_pin;

    public:
        Microphone(int microphone_pin);
        bool noise_detected();
        bool no_noise_detected();
        int noise_level();
};
