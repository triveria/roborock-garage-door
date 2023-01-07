# ref.: https://arduino.github.io/arduino-cli/0.28/getting-started/


LIBS:="Adafruit PWM Servo Driver Library"
FQBN:="esp32:esp32:esp32"
SKETCH:="roborock-garage-door.ino"

USB_PORT:="/dev/ttyUSB0"


all: compile

install:
	arduino-cli lib install $(LIBS)
	arduino-cli core update-index --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
	arduino-cli core install esp32:esp32

compile:
	arduino-cli compile --fqbn $(FQBN) $(SKETCH)

flash: compile
	arduino-cli upload -p $(USB_PORT) --fqbn $(FQBN) $(SKETCH)

connect:
	minicom -b 115200 -o -D $(USB_PORT)
