# FQBN=arduino:avr:nano
# FQBN=arduino:avr:uno
# FQBN=esp8266:esp8266:nodemcuv2
# FQBN=esp32:esp32:esp32
# SKETCH=lcd
# PORT=/dev/ttyUSB0

init: update-index install-dependencies

update-index:
	arduino-cli core update-index --config-file arduino-cli.yaml
	arduino-cli lib  update-index --config-file arduino-cli.yaml

install-dependencies:
	arduino-cli core install arduino:avr@1.8.6 --config-file arduino-cli.yaml
	arduino-cli lib install Dabble@1.5.2 --config-file arduino-cli.yaml
	arduino-cli lib install LiquidCrystal@1.0.7 --config-file arduino-cli.yaml
	arduino-cli lib install 'RoboCore - Vespa@1.3.0' --config-file arduino-cli.yaml
	# arduino-cli core install esp8266:esp8266@3.1.2 --config-file arduino-cli.yaml
	# arduino-cli core install esp32:esp32@3.0.7 --config-file arduino-cli.yaml
	# arduino-cli lib install ESP8266WiFi@1.0 --config-file arduino-cli.yaml

run: compile upload monitor

compile:
	arduino-cli compile $(SKETCH) --build-path .build/$(SKETCH) --fqbn $(FQBN) --library library --config-file arduino-cli.yaml

upload:
	sudo chmod a+rw $(PORT)
	arduino-cli upload $(SKETCH) --input-dir .build/$(SKETCH) --fqbn $(FQBN) --port $(PORT) --config-file arduino-cli.yaml

monitor:
	sudo chmod a+rw $(PORT)
	arduino-cli monitor --config baudrate=9600 --fqbn $(FQBN) --port $(PORT) --config-file arduino-cli.yaml

monitor-describe:
	sudo chmod a+rw $(PORT)
	arduino-cli monitor --describe --fqbn $(FQBN) --port $(PORT) --config-file arduino-cli.yaml

clean:
	rm -rf .build
	rm -rf .arduino

config-dump:
	arduino-cli config dump
