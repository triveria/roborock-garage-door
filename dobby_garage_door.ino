/*
  Input Pull-up Serial

  This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a digital
  input on pin 2 and prints the results to the Serial Monitor.

  The circuit:
  - momentary switch attached from pin 2 to ground
  - built-in LED on pin 13

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  20K-ohm resistor is pulled to 5V. This configuration causes the input to read
  HIGH when the switch is open, and LOW when it is closed.

  created 14 Mar 2012
  by Scott Fitzgerald

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/InputPullupSerial

  Motor controller code taken from https://create.arduino.cc/projecthub/ryanchan/how-to-use-the-l298n-motor-driver-b124c5
*/


int button_pin  = 2;
int motor1_pin1 = 3;
int motor1_pin2 = 4;
int led_pin     = 13;


void setup() {
    //start serial connection
    Serial.begin(9600);
    //configure pin 2 as an input and enable the internal pull-up resistor
    pinMode(button_pin, INPUT_PULLUP);
    pinMode(led_pin, OUTPUT);
    
    pinMode(motor1_pin1, OUTPUT);
    pinMode(motor1_pin2, OUTPUT);
}


void loop() {
    //read the pushbutton value into a variable
    int sensorVal = digitalRead(2);
    //print out the value of the pushbutton
    Serial.println(sensorVal);
    
    // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
    // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
    // button's pressed, and off when it's not:
    if (sensorVal == HIGH) {
        digitalWrite(13, LOW);
        digitalWrite(motor1_pin1, HIGH);
        digitalWrite(motor1_pin2, LOW);
    } else {
        digitalWrite(13, HIGH);
        digitalWrite(motor1_pin1, LOW);
        digitalWrite(motor1_pin2, HIGH);
    }
}