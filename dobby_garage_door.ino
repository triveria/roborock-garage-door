/**
 * 
 * ref.: https://randomnerdtutorials.com/guide-for-microphone-sound-sensor-with-arduino/
 * 
 * poti CCW: increase threshold. turn until LED turns off
 * 
 * pinout: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
 * 
 * Pins:
 * V5  (lower left corner) -> servo board
 * GND (upper right corner) -> servo boad
 * SDO -> SDA
 * CLK -> SCL 
 * 
 * 
 */


#include "door_mechanism.hpp"
#include "noise_detector.hpp"


void setup()
{
    Serial.begin (115200);
    Serial.println("8 channel Servo test!");
    
    init_door_mechanism();        
    delay(10);
}


void loop ()
{
    //check_microphone();
    
    open_door();
    delay(1500);
    close_door();
    delay(1500);
}
