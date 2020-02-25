#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lib/libsoftwareuart.h"

volatile uint32_t encoderValue = 0;
volatile uint32_t test = 4294967296;
void SystemInit(void)
{
	MCUCR &= ~(1<<ISC01) | ~(1<<ISC00);	// Trigger INT0 on rising edge
	PCMSK |= (1<<PCINT0);   // pin change mask: listen to portb, pin PB3
	GIMSK |= (1<<PCIE); // enable PCINT interrupt
	sei();          // enable all interrupts

}

ISR(PCINT0_vect)
{
	encoderValue++;
}

int main(void)
{
	encoderValue = 0;
	DDRB  &= ~(1<<PB0);
	SystemInit();
	while (1)
	{
	uart_putu(encoderValue);
	uart_putc('\r');
	uart_putc('\n');
	}
}
