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


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


int microphone_pin = 15;

uint8_t servo_board_address = 0x40;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(servo_board_address);

#define SERVO_MIN  66  // This is the 'minimum' pulse length count (out of 4096). Tweak for each servo.
#define SERVO_MAX  497 // This is the 'maximum' pulse length count (out of 4096). Tweak for each servo.

#define DOOR_OPEN_RIGHT 111
#define DOOR_CLOSE_RIGHT 273

#define DOOR_OPEN_LEFT 262
#define DOOR_CLOSE_LEFT 74

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


uint8_t servo_right_idx = 0; // slot on servo board
uint8_t servo_left_idx = 1; // slot on servo board

int position_left = SERVO_MIN;


void setup()
{
    pinMode(microphone_pin, INPUT);
    Serial.begin (115200);
    Serial.println("8 channel Servo test!");
    
    pwm.begin();
    int internal_oscillator_frequency_hz = 27000000;
    pwm.setOscillatorFrequency(internal_oscillator_frequency_hz);
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
        
    delay(10);
}


void check_microphone()
{
    bool noise_detected = digitalRead(microphone_pin);
    Serial.println(noise_detected); // check if val == HIGH

    int noise_level = analogRead(microphone_pin);
    Serial.println(noise_level);
}


void open_door()
{
    int left_start_position = DOOR_CLOSE_LEFT;
    int left_end_position = DOOR_OPEN_LEFT;
    int right_start_position = DOOR_CLOSE_RIGHT;
    int right_end_position = DOOR_OPEN_RIGHT;

    float num_steps = 20.f;
    
    float step_size_left = (left_end_position - left_start_position) / num_steps;
    float step_size_right = (right_end_position - right_start_position) / num_steps;
    for(int i = 0; i < num_steps; i++) {
        pwm.setPWM(servo_left_idx, 0, left_start_position + i*step_size_left);
        pwm.setPWM(servo_right_idx, 0, right_start_position + i*step_size_right);
        delay(50);
    }
    pwm.setPWM(servo_left_idx, 0, left_end_position);
    pwm.setPWM(servo_right_idx, 0, right_end_position);
}


void close_door()
{

    int left_start_position = DOOR_OPEN_LEFT;
    int left_end_position = DOOR_CLOSE_LEFT;
    int right_start_position = DOOR_OPEN_RIGHT;
    int right_end_position = DOOR_CLOSE_RIGHT;
    
    float num_steps = 20.f;
    
    float step_size_left = (left_end_position - left_start_position) / num_steps;
    float step_size_right = (right_end_position - right_start_position) / num_steps;
    for(int i = 0; i < num_steps; i++) {
        pwm.setPWM(servo_left_idx, 0, left_start_position + i*step_size_left);
        pwm.setPWM(servo_right_idx, 0, right_start_position + i*step_size_right);
        delay(50);
    }
    pwm.setPWM(servo_left_idx, 0, left_end_position);
    pwm.setPWM(servo_right_idx, 0, right_end_position);
}


void find_servo_position()
{
    uint8_t servo = servo_left_idx;
    if(Serial.available() > 0) {
        int choice = Serial.parseInt();
        if ((SERVO_MIN <= choice) && (choice <= SERVO_MAX)) {
            position_left = choice;
            pwm.setPWM(servo, 0, DOOR_CLOSE_LEFT);
            delay(500);
            Serial.println((String)"moving to position: " + choice);
            pwm.setPWM(servo_left_idx, 0, choice);
        }
    }
}


void control_servo()
{


    

//    uint8_t start_pos = 240;
//    uint8_t end_pos = 255;
//    uint8_t step_size = (end_pos - start_pos) / 10;
    
    // instead of using stupid loop: buttons?
//    for( uint8_t pos = start_pos; pos < end_pos;  pos += step_size) {
//        Serial.println(pos);
//        pwm.setPWM(servo_right_idx, 0, pos);
//        delay(1000);
//    }

//    if(Serial.available() > 0) {
//        char incomingByte = Serial.read();
//        if ((incomingByte >= '0') && (incomingByte <= '9')) {
//            int choice = (incomingByte - '0') * 10;
//            Serial.println((String)"moving by: " + choice);
//        }
//    }



    
     // right: ca 253 = close, 70 = open
    
    //pwm.setPWM(servo_right_idx, 0, 255);
    //pwm.setPWM(servo_right_idx, 0, 255);
    
//    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
//        pwm.setPWM(servo_idx, 0, pulselen);
//    }
    
//    delay(500);
//    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//        pwm.setPWM(servo_idx, 0, pulselen);
//    }
}


void loop ()
{
    //check_microphone();
    //control_servo();
    
    open_door();
    delay(1500);
    close_door();
    delay(1500);
}
