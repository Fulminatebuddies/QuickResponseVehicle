#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lib/libsoftwareuart.h"

int main(void)
{
    char *p, buff[16];
    /* loop */
    while (1) {
	uart_puts("ThunderBuddies! and Viraj\r\n");
        p = buff;
        *p = 0;
        _delay_ms(10);
        uart_puts(buff);
    }
}
