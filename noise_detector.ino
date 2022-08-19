int microphone_pin = 15;

void initialize_noise_detector()
{
    pinMode(microphone_pin, INPUT);
}

void check_microphone()
{
    bool noise_detected = digitalRead(microphone_pin);
    Serial.println(noise_detected); // check if val == HIGH

    int noise_level = analogRead(microphone_pin);
    Serial.println(noise_level);
}
