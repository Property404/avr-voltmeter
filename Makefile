SHELL = /bin/sh
CC = avr-gcc

SRC_DIR = .
BUILD_DIR = .

NAME = $(BUILD_DIR)/voltmeter

OBJECTS = main.o delay.o servo.o adc.o

SOURCES = $(OBJECTS:%.o=$(SRC_DIR)/%.o)

# Compiler flags
C_FLAGS = -std=c99 -Wall -Wextra -mmcu=atmega328p
CFLAGS = -std=c99 -Wall -Wextra -mmcu=atmega328p


# Build recipe
voltmeter: $(SOURCES)
	$(CC) -o $(NAME).elf $(SOURCES) $(C_FLAGS)
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $(NAME).elf $(NAME).hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(NAME).hex

clean:
	rm -f *.o *.elf *.hex
