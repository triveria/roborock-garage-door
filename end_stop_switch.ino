#include "end_stop_switch.hpp"


EndStopSwitch::EndStopSwitch(int switch_pin)
{
    _switch_pin = switch_pin;
    pinMode(_switch_pin, INPUT_PULLDOWN);
}


bool EndStopSwitch::pushed()
{
    bool is_pushed = digitalRead(_switch_pin);
    Serial.println((String)"End stop switch got pushed:" + is_pushed);

    return is_pushed;
}
