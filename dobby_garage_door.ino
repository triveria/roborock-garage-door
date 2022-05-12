/**
 * 
 * ref.: https://randomnerdtutorials.com/guide-for-microphone-sound-sensor-with-arduino/
 * 
 * poti CCW: increase threshold. turn until LED turns off
 */


int sensor_pin = 15;


void setup()
{
    pinMode(sensor_pin, INPUT);
    Serial.begin (9600);
}


void loop ()
{
//    bool digital_val = digitalRead(sensor_pin);
//    Serial.println(digital_val); // check if val == HIGH

    int analog_val = analogRead(sensor_pin);
    Serial.println(analog_val);
}
