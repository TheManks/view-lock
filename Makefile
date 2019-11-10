upload: compile
	@echo "uploading view-lock on /dev/ttyACM0"
	sudo arduino-cli upload  -p /dev/ttyACM0 -b arduino:samd:nano_33_iot -i ./bin/vlock.bin
compile: bin/vlock.bin bin/vlock.elf	
	@echo "attempted compiling view-lock"

bin/vlock.bin: view-lock/view-lock.ino view-lock/secrets.h view-lock/VLock.hpp view-lock/VLock.cpp
	arduino-cli compile -b arduino:samd:nano_33_iot view-lock -o bin/vlock
