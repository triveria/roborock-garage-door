#pragma once


class EndStopSwitch {
    private:
        int _switch_pin;

    public:
        EndStopSwitch(int switch_pin);
        bool pushed();
};
