#
# Copyright 2013 Greizgh <greizgh@gmail.com>
#
# This file is part of FlopMaster.
# FlodMaster is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# FlopMaster is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with FlopMaster.  If not, see <http://www.gnu.org/licenses/>.
TARGET = FlopMaster
#Flavor: purenote or none
FLAVOR = none
MCU = atmega328p
CPU_FREQ = 16000000UL
PORT = /dev/ttyACM0

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
CFLAGS = -Os -D F_CPU=$(CPU_FREQ) -mmcu=$(MCU) -Wall -std=c99

ifeq ($(FLAVOR),purenote)
    SRC = flopmaster_pure.c
else
    SRC = flopmaster.c
endif
OBJ = $(SRC:.c=.o)

all: $(TARGET).hex

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(TARGET).hex: $(TARGET)
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET) $(TARGET).hex

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS)

%.asm:%.c
	$(CC) $(CFLAGS) -S $< -o $@

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(TARGET).hex
	rm -rf $(TARGET)

upload: $(TARGET).hex
	$(AVRDUDE) -c arduino -p ATMEGA328P -P $(PORT) -b 115200 -U flash:w:$(TARGET).hex
