#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"

#define	IR_DATA_PIN	PB2

static void IR_init(void);
static int IR_read(void);
static int analog_read(uint8_t pin);
static void uart_puttemp(int value);

int main(void)
{
    int value;
    IR_init();
    /* loop */
    while (1) {
      value = IR_read();
      uart_puttemp(value);
      _delay_ms(10);
    }
}

void IR_init(void)
{

	DDRB &= ~_BV(IR_DATA_PIN); // set data pin as INPUT
}

int IR_read(void)
{
	int value;
	value = analog_read(IR_DATA_PIN); // read analog value from sensor
	value = ((((uint32_t)value * 1000UL) >> 10) * 5); // convert value using euqation temp = Vin * 1000 / 1024 * Vref [milivolts]
	return value;
}

int analog_read(uint8_t pin)
{
	uint8_t low, high;

	switch(pin) {
	      case PB2: ADMUX = _BV(MUX0); break; // ADC1
        case PB4: ADMUX = _BV(MUX1); break; // ADC2
        case PB3: ADMUX = _BV(MUX0)|_BV(MUX1); break; // ADC3
        case PB5: // ADC0
	      default: ADMUX = 0; break;
	}

	ADMUX &= ~_BV(REFS0); // explicit set VCC as reference voltage (5V)
	ADCSRA |= _BV(ADEN);  // Enable ADC
	ADCSRA |= _BV(ADSC);  // Run single conversion
	while(bit_is_set(ADCSRA, ADSC)); // Wait conversion is done

	// Read values
	low = ADCL;
        high = ADCH;

        // combine the two bytes
        return (high << 8) | low;
}

void uart_puttemp(int value)
{
	uart_puts("IR=");
	uart_putu(value);
	uart_putc('\n');
}
