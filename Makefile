MCU = attiny13
CC = avr-gcc
CFLAGS = -std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=1200000
TARGET = main
SRCS = main.c /home/ubuntu/test/lib/libsoftwareuart.c
LD = avr-ld
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

all:
	${CC} ${CFLAGS} -o ${TARGET}.o ${SRCS}
	${LD} -o ${TARGET}.elf ${TARGET}.o
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.o ${TARGET}.hex

flash:
	sudo ${AVRDUDE} -p ${MCU} -c avrisp -U flash:w:${TARGET}.hex:i -F -e -b 19200 -v -P /dev/ttyACM0

clean:
	rm -f *.c~ *.o *.elf *.hex
