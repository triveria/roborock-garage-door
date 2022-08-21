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
 * 
 */


#include "door_mechanism.hpp"
#include "noise_detector.hpp"


int microphone_pin = 15;


Door door;
Microphone microphone(microphone_pin);


void setup()
{
    Serial.begin (115200);
    Serial.println("Booting...");
}


void loop ()
{
    door.test();

    microphone.noise_detected();
    // bool laser_broken = check_laser();

    // if (microphone.noise_detected() && door.may_be_opened()) {
    //     door.open_up();
    // }

    // if (laser_broken && door.may_be_closed()) {
    //     door.close_down();
    // }
}
