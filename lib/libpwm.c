#include <avr/io.h>
#include <util/delay.h>
#include "libpwm.h"

// To calculate frequency of PWM use the formula given in datasheet (F = fclk / N * 256)
void pwm_init(void)
{
    DDRB |= _BV(PB0); // set PWM pin as OUTPUT
    TCCR0A |= _BV(WGM01)|_BV(WGM00); // set timer mode to FAST PWM
    TCCR0A |= _BV(COM0A1); // connect PWM signal to pin (AC0A => PB0)
}

void pwm_set_frequency(uint32_t N)
{

    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | N; // set prescaler
}

void pwm_set_duty(uint8_t duty)
{

    OCR0A = duty; // set the OCRnx
}

void pwm_stop(void)
{

    TCCR0B &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // stop the timer
}
void pwm_setup(void)
{
    uint8_t duty = 127;   //Ranges from 0 to 254 i.e 0% t0 100% duty cycle

    /* setup */
    pwm_init();
    pwm_set_frequency(N_1);
    pwm_set_duty(duty);
    /* loop */
}
