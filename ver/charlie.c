#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"
#include "../lib/libnewadc.h"

static void uart_puttemp(int value);

int main(void)
{
    int value;
    IR_init();
    /* loop */
    while (1) {
      value = IR_read();
      uart_puttemp(value);
      _delay_ms(10);
    }
}

void uart_puttemp(int value)
{
	uart_puts("IR=");
	uart_putu(value);
	uart_putc('\n');
}
