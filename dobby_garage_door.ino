/**
 * 
 * ref.: https://randomnerdtutorials.com/guide-for-microphone-sound-sensor-with-arduino/
 * To increase threshold of microphone, turn potentionmeter counterclockwise. Turn until LED turns off under normal noise level.
 * 
 * 
 * Pinout of ESP32 Dev Module: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
 * 
 * Wiring from ESP to PWM driver:
 * V5  (lower left corner) -> servo board
 * GND (upper right corner) -> servo board
 * SDO -> SDA
 * CLK -> SCL 
 * 
 * Update:
 * The noise detection turns out to be unreliable:
 * Every air movement is picked up by the microphone.
 * Thus it also opens when ever some one opens a window or door.
 * 
 */


#include "door_mechanism.hpp"
#include "noise_detector.hpp"
#include "end_stop_switch.hpp"


int microphone_pin = 14;
int switch_pin = 16;

Door door;
Microphone microphone(microphone_pin);
EndStopSwitch end_stop_switch(switch_pin);


void setup()
{
    Serial.begin (115200);
    Serial.println("Booting...");

    door.setup();
}


void loop ()
{
    if (!end_stop_switch.pushed() && door.is_closed()) {
        door.open_up();
        door.hold_until_robot_has_left_the_house();
    }

    if (end_stop_switch.pushed() && door.is_open()) {
        door.close_down();
        door.hold_until_robot_has_gone_to_sleep();
    }
}
