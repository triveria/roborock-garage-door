#include "end_stop_switch.hpp"


EndStopSwitch::EndStopSwitch(int switch_pin)
{
    _switch_pin = switch_pin;
    pinMode(_switch_pin, INPUT_PULLUP);
}


bool EndStopSwitch::pushed()
{
    bool is_pushed = digitalRead(_switch_pin);
    Serial.println(is_pushed);

    return is_pushed;
}
