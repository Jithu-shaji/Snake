# ==================================================
# Project Settings
# ==================================================
MCU     = atmega328p
F_CPU   = 16000000UL
TARGET  = snake

# Directories
SRC_DIR = src
INC_DIR = include

# Files
SRC     = $(wildcard $(SRC_DIR)/*.c)
OBJ     = $(SRC:.c=.o)

# Tools
CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Flags
CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -I$(INC_DIR)
OBJCOPYFLAGS = -O ihex -R .eeprom
LDFLAGS = -mmcu=$(MCU)

# ==================================================
# Rules
# ==================================================
all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS)  $< $@
	
$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(TARGET).hex
	$(AVRDUDE) -c usbasp -p m328p -U flash:w:$<

clean:
	rm -f $(SRC_DIR)/*.o *.elf *.hex 
