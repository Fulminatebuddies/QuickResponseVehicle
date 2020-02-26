#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"

#define LED_PIN PB0;

void SystemInit(void)
{
	MCUCR &= ~(1<<ISC01);	// Trigger INT0 on rising edge
        MCUCR &= ~(1<<ISC00);	
	PCMSK |= (1<<PCINT0);   // pin change mask: listen to portb, pin PB3
	GIMSK |= (1<<PCIE); // enable PCINT interrupt
	sei();          // enable all interrupts
	DDRB  &= ~(1<<PB0);

}

ISR(PCINT0_vect)
{
	uart_puts("801t");
}

int main(void)
{
	SystemInit();
	while (1)
	{

	}
}
