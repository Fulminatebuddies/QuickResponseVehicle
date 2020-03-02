#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"
#include "../lib/libadc.h"

volatile int value;

static void uart_puttemp(int value);
static void system_init(void)

void system_init(void)
{
	MCUCR &= ~(1<<ISC01);	// Trigger INT0 on rising edge
        MCUCR &= ~(1<<ISC00);	
	PCMSK |= (1<<PCINT0);   // pin change mask: listen to portb, pin PB3
	GIMSK |= (1<<PCIE); // enable PCINT interrupt
	sei();          // enable all interrupts
	DDRB  &= ~(1<<PB0);

}

int main(void)
{
    IR_init();
    system_init();
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
