#ifndef	_LIBADC_H_
#define	_LIBADC_H_

#ifndef F_CPU
# define        F_CPU           (1200000UL) // 1.2 MHz
#endif  /* !F_CPU */

#define	IR_DATA_PIN	PB2 

void IR_init(void);
int IR_read(void);
int analog_read();
void adc_init(uint8_t pin)

#endif	/* !_LIBADC_H_ */
