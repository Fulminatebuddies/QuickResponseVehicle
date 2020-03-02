#ifndef	_LIBSOFTWAREUARTFORTYFOUR_H_
#define	_LIBSOFTWAREUARTFORTYFOUR_H_

#ifndef F_CPU
# define        F_CPU           (1000000UL) // 1.0 MHz
#endif  /* !F_CPU */
#define TX_PORT PORTB
#define TX_PIN  PB0
#define TX_DDR  DDRB
#define TX_DDR_PIN DDB0

void uart_putc(char character);
void uart_puts(char* string);
void uart_putu(uint16_t x);
void UART_init();
ISR(TIM0_COMPA_vect);

#endif	/* !_LIBSOFTWAREUARTFORTYFOUR_H_ */
