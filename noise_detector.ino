#include "noise_detector.hpp"


Microphone::Microphone(int microphone_pin)
{
    _microphone_pin = microphone_pin;
    pinMode(_microphone_pin, INPUT_PULLDOWN);
}


int Microphone::noise_level()
{
    int noise_level = analogRead(_microphone_pin);
    Serial.println((String)"Noise level is " + noise_level);
    return noise_level;
}


bool Microphone::no_noise_detected()
{
    bool noise_below_threshold = !digitalRead(_microphone_pin);
    Serial.println((String)"Noise level is below threshold:" + noise_below_threshold);

    return noise_below_threshold;
}


bool Microphone::noise_detected()
{
    bool noise_above_threshold = digitalRead(_microphone_pin);
    Serial.println((String)"Noise level is above threshold:" + noise_above_threshold);

    return noise_above_threshold;
}
