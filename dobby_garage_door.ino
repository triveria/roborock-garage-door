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
 * Potential bugs:
 *  - time wrap around: then is time of last opening in the future
 *  - door cannot be used in the first 10 seconds or so, since time_of_last_closing is initialized with 0
 */


#include "door_mechanism.hpp"
#include "noise_detector.hpp"
#include "end_stop_switch.hpp"


int microphone_pin = 15; // @TODO: set proper pin
int switch_pin = 10; // @TODO: set proper pin

Door door;
Microphone microphone(microphone_pin);
EndStopSwitch end_stop_switch(switch_pin);


void setup()
{
    Serial.begin (115200);
    Serial.println("Booting...");
}


void loop ()
{
    if (microphone.noise_detected() && door.may_be_opened()) {
        door.open_up();
    }

    if (end_stop_switch.pushed() && door.may_be_closed()) {
        door.close_down();
    }
}
