#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"
#include "../lib/libadc.h"

volatile uint16_t value =1;
static void system_init(void);
static void hotline();

void system_init(void)
{
	MCUCR |= (1<<ISC01);	// Trigger INT0 on rising edge
        MCUCR |= (1<<ISC00);	
	//PCMSK |= (1<<PCINT0);   // pin change mask: listen to portb, pin PB3
	GIMSK |= (1<<INT0); // enable PCINT interrupt
        GIFR |= (1<<INTF0);
	sei();          // enable all interrupts
	DDRB  &= ~(1<<PB1);

}

ISR(INT0_vect)
{
	uart_putu(value);
	uart_puts("t");
}

void hotline(){
	GIMSK &= ~(1<<INT0);
	DDRB |= (1<<PB1);
	PORTB &= ~(1<<PB1);
	_delay_ms(5);
	PORTB |= (1<<PB1);
	
	DDRB  &= ~(1<<PB1);
	PORTB &= ~(1<<PB1);
	GIMSK |= (1<<INT0);
}

int main(void)
{
    IR_init();
    system_init();
    /* loop */
    while (1) {
	value = IR_read();
      //_delay_ms(10);
	if(value < 600){
		hotline();
	}
    }
}
