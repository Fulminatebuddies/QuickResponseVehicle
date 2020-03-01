#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lib/libsoftwareuart.h"  //B0 - Tx and B1 - Rx

#define N_1    (_BV(CS00))
#define N_8    (_BV(CS01))
#define N_64   (_BV(CS01)|_BV(CS00))
#define N_256  (_BV(CS02))
#define N_1024 (_BV(CS02)|_BV(CS00))

volatile uint32_t encoderValue = 0;
void SystemInit(void)
{
	MCUCR |= (1<<ISC01) | (1<<ISC00);	// Trigger INT0 on rising edge
	PCMSK0 |= (1<<PCINT0);   // pin change mask: listen to portb, pin PB3
	GIMSK |= (1<<PCIE0); // enable PCINT interrupt
	sei();          // enable all interrupts

}

static void pwm_init(void)
{
    DDRA |= _BV(PA7); // set PWM pin as OUTPUT
    TCCR0A |= _BV(WGM00) | _BV(WGM01); // set timer mode to FAST PWM
    TCCR0A |= _BV(COM0B1); // connect PWM signal to pin (AC0A => PB0)
}

static void pwm_set_frequency(uint32_t N)
{

    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | N; // set prescaler
}

static void pwm_set_duty(uint8_t duty)
{

    OCR0B = duty; // set the OCRnx
}
static void pwm_stop(void)
{

    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
}

ISR(PCINT0_vect)
{
	encoderValue++;
 	
}


int main(void)
{
	encoderValue = 0;
	uint8_t duty = 127;    //Ranges from 0 to 254 i.e 0% t0 100% duty cycle

   	 /* setup */
	DDRB  &= ~(1<<PB2);    //Interrupt pin
    	SystemInit();          //Int setup
	pwm_init();
    	pwm_set_frequency(N_1);
    	pwm_set_duty(duty);
	

	while (1)
	{
	uart_putc('H');
	uart_putc('\r');
	uart_putc('\n');
	if(encoderValue == 1064){
	pwm_stop();}
	}
}

