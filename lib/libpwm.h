#ifndef	_LIBPWM_H_
#define	_LIBPWM_H_

#define N_1    (_BV(CS00))     //No prescaler i.e N = 1
#define N_8    (_BV(CS01))     //Prescaler N = 8   
#define N_64   (_BV(CS01)|_BV(CS00)) //Prescaler N = 64
#define N_256  (_BV(CS02))  //Prescaler N = 256
#define N_1024 (_BV(CS02)|_BV(CS00))  //Prescaler N = 1024

void pwm_init(void);
void pwm_set_frequency(uint32_t N);
void pwm_set_duty(uint8_t duty);
void pwm_stop(void);
void pwm_setup(void);

#endif	/* !_LIBPWM_H_ */

