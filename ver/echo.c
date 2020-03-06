/*
	PB0 - PWM
	PB1 - Interrupt based Half Duplex Rx / Hotline
	PB2 - ADC for IR Rx
	PB3 - Serial Tx
	PB4 - IR Tx
	PB5 - Reset
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"
#include "../lib/libadc.h"
#include "../lib/libpwm.h"

volatile uint16_t value =1;
static void system_init(void);
static void hotline();
uint8_t duty = 127;

void system_init(void)
{
	MCUCR |= (1<<ISC01);	// Trigger INT0 on rising edge
  	MCUCR |= (1<<ISC00);
	//PCMSK |= (1<<PCINT0);   // pin change mask: listen to portb, pin PB3
	GIMSK |= (1<<INT0); // enable PCINT interrupt on PB1
  	GIFR |= (1<<INTF0);
	sei();          // enable all interrupts
	DDRB  &= ~(1<<PB1);

}
ISR(INT0_vect)
{
	//Send the data whenever Master's Requests it
	uart_putu(value);
	uart_puts("t");
}

void hotline(){
	//Disable the INTO0
	GIMSK &= ~(1<<INT0);
	//Make the Interrupt pin as Output
	DDRB |= (1<<PB1);
	//Write Low for 5ms
	PORTB &= ~(1<<PB1);
	_delay_ms(5);
	//Write High again
	PORTB |= (1<<PB1);
	//Make Interrupt pin as Input with pull up internal resistance
	DDRB  &= ~(1<<PB1);
	PORTB &= ~(1<<PB1);
	//Enable the interrupt
	GIMSK |= (1<<INT0);
}

int main(void)
{
  	IR_init();
  	system_init();
	pwm_setup();
	_delay_ms(5000);
	duty = 254;
	pwm_set_duty(duty);
  	/* loop */
  	while (1) {
		value = IR_read();
		if(value < 600){
			//hotline();
		}
  }
}
