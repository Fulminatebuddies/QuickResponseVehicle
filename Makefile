MCU = attiny13
CC = avr-gcc
CFLAGS = -std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=1200000
TARGET = main
SRCS = ver/echo.c ./lib/libsoftwareuart.c ./lib/libadc.c ./lib/libpwm.c
LD = avr-ld
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
VAR_LOCAL = "default"

all:
	${CC} ${CFLAGS} -o ${TARGET}.o ${SRCS}
	${LD} -o ${TARGET}.elf ${TARGET}.o
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.o ${TARGET}.hex

flash:
	sudo ${AVRDUDE} -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -e -b 19200 -v

clean:
	rm -f *.c~ *.o *.elf *.hex

one: 
	@grep "#include \"" ${SRCS} > tmp; sed -e 's/\(^.*\.\.\)\(.*\)\(".*$ \)/\2/' tmp > tmp1 ; sed -i 's/.h/.c/g' tmp1 ; sed -i 's/\//\.\//1' tmp1; cat tmp1 | xargs > oneline.txt;
	cat oneline.txt;

        #$(eval VAR_LOCAL := $(shell cat oneline.txt))

