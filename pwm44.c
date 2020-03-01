#include <avr/io.h>
#include <util/delay.h>

#define N_1    (_BV(CS00))
#define N_8    (_BV(CS01))
#define N_64   (_BV(CS01)|_BV(CS00))
#define N_256  (_BV(CS02))
#define N_1024 (_BV(CS02)|_BV(CS00))

static void pwm_init(void)
{
    DDRA |= _BV(PA7); // set PWM pin as OUTPUT
    TCCR0A |= _BV(COM0B1) | _BV(WGM01) | _BV(WGM00); // set timer mode to FAST PWM
}

static void pwm_set_frequency(uint32_t N)
{

    TCCR0B = (TCCR0B & ~((1<<CS02)|(1<<CS01)|(1<<CS00))) | N; // set prescaler
}

static void pwm_set_duty(uint32_t duty)
{

    OCR0B = duty; // set the OCRnx
}

//static void pwm_stop(void)
//{

//    TCCR1B &= ~((1<<CS12)|(1<<CS11)|(1<<CS10)); // stop the timer
//}

int main(void)
{
    uint32_t duty = 127;    //Ranges from 0 to 254 i.e 0% t0 100% duty cycle

    /* setup */
    pwm_init();
    pwm_set_frequency(N_1);
    pwm_set_duty(duty);
    /* loop */
    while (1) {
       //pwm_set_duty(duty++);
        //_delay_ms(100);
    }
}
