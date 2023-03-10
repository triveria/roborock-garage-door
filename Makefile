# ref.: https://create.arduino.cc/projecthub/B45i/getting-started-with-arduino-cli-7652a5


LIBS:="Adafruit PWM Servo Driver Library"
FQBN:="esp32:esp32:esp32"
SKETCH:="dobby_garage_door.ino"

USB_PORT:="/dev/ttyUSB0"


all: compile

install:
	arduino-cli lib install $(LIBS)

compile:
	arduino-cli compile --fqbn $(FQBN) $(SKETCH)

flash: compile
	arduino-cli upload -p $(USB_PORT) --fqbn $(FQBN) $(SKETCH)

connect:
	minicom -b 115200 -o -D $(USB_PORT)
