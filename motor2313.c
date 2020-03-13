#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include "lib/uart.h"
volatile uint32_t encoderValue = 0;
#define N_1    (_BV(CS00))
#define N_8    (_BV(CS01))
#define N_64   (_BV(CS01)|_BV(CS00))
#define N_256  (_BV(CS02))
#define N_1024 (_BV(CS02)|_BV(CS00))
float rpm;

void SystemInit(void)
{
DDRD  &= ~(1<<PD2);
MCUCR |= (1<<ISC01) | (1<<ISC00);	// Trigger INT0 on rising edge
GIMSK |= (1<<INT0); // enable PCINT interrupt
sei();          // enable all interrupts

}

void timerint(void)
{
TCCR1A = 0x00; 					//Timer counter control register
TCCR1B = _BV(WGM12)| _BV(CS12)| _BV(CS10); // prescale at 1024 and CTC mode activated
TIMSK |= _BV(OCIE1A);			//Set bit 6 in TIMSK to enable Timer 1 compare interrupt.
OCR1A = 0x1E83;					//Set OCR1A

}

ISR(TIMER1_COMPA_vect)
{
//PORTD ^=(1<<PD5);				//Toggle PortB3
rpm = (encoderValue / 334) * 60;
encoderValue = 0;
}


ISR(INT0_vect)
{
encoderValue++;
}

static void pwm_init(void)
{
DDRB |= _BV(PB2); // set PWM pin as OUTPUT
TCCR0A |= _BV(COM0A1) | _BV(WGM01) | _BV(WGM00); // set timer mode to FAST PWM
}

static void pwm_set_frequency(uint32_t N)
{

TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | N; // set prescaler
}

static void pwm_set_duty(uint8_t duty)
{

OCR0A = duty; // set the OCRnx
}

static void pwm_stop(void)
{
TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
}

int main(void)
{
DDRD = _BV(PD5);
CLKPR = (1<<CLKPCE);
CLKPR = 0;
init_uart();
sei();
encoderValue = 0;
SystemInit();
timerint();
uint16_t c = 0;
uint8_t duty = 127;    //Ranges from 0 to 254 i.e 0% t0 100% duty cycle
pwm_init();                                     /* PWM setup */
pwm_set_frequency(N_8);
pwm_set_duty(duty);
while (1)
{
c = uart_getc();
if (c == UART_NO_DATA) {
uart_putu(encoderValue);
uart_putc('\t');
uart_putu(rpm);
uart_putc('\r');
uart_putc('\n');
}
if( c == '9' ){
PORTD |= (1 <<PORTD5);
}
if(c == '1')
{
PORTD &= ~(1 << PORTD5);
}
}

}
