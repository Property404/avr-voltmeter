SHELL = /bin/sh
CC = avr-gcc

BUILD_DIR = .

NAME = $(BUILD_DIR)/voltmeter

OBJECTS = main.o servo.o adc.o

# Compiler flags
CFLAGS = -std=c99 -Wall -Wextra -mmcu=atmega328p

# Build recipe
voltmeter: $(OBJECTS)
	$(CC) -o $(NAME).elf $(OBJECTS) $(CFLAGS)
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $(NAME).elf $(NAME).hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(NAME).hex

clean:
	rm -f *.o *.elf *.hex
