#!/bin/bash
read -p "Press a key, [CF]:Compile & Flash [F]:Flash " input0
if [ "$input0" == "CF" ]; then
	avr-gcc -g -Os -mmcu=attiny13 -c $1.c
	avr-gcc -g -mmcu=attiny13 -o $1.elf $1.o
	avr-objcopy -j .text -j .data -O ihex $1.elf $1.hex
	avr-size $1.elf

	read -p "Press a key, [U]:Arduino UNO [A]:ATtiny13a " input1
	Aa="A"
	if [ "$input1" == "$Aa" ]; then
		sudo avrdude -F -c avrisp -p attiny13 -P /dev/ttyACM0 -D -U flash:w:$1.hex:i -v -b 19200 -e
	elif [ "$input1" == "U" ]; then
		sudo avrdude -F -c arduino -p m328p -P /dev/ttyACM0 -D -U flash:w:$1.hex:i -v -b 115200
	fi
elif [ "$input0" == "F" ]; then
	read -p "Press a key, [U]:Arduino UNO [A]:ATtiny13a " input1
        Aa="A"
	if [ "$input1" == "$Aa" ]; then
                sudo avrdude -F -c avrisp -p attiny13 -P /dev/ttyACM0 -D -U flash:w:$1.hex:i -v -b 19200 -e
        elif [ "$input1" == "U" ]; then
                sudo avrdude -F -c arduino -p m328p -P /dev/ttyACM0 -D -U flash:w:$1.hex:i -v -b 115200
        fi
fi



