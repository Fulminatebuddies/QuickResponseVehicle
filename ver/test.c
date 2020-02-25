#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"

int main(void)
{
    char c;
    uart_puts("IC 1 Hello World!");
    uart_putc('\r');
    uart_putc('\n');
    /* loop */
    while (1) {
       c = uart_getc();
	uart_putc(c);
	uart_puts(" IC1");
	     uart_putc('\r');
	     uart_putc('\n');
    }
}
