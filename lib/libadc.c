#include <avr/io.h>
#include <avr/interrupt.h>
#include "libadc.h"

void IR_init(void)
{
	DDRB &= ~_BV(IR_DATA_PIN); // set data pin as INPUT
	adc_init(IR_DATA_PIN);
	DDRB |= (1<<PB4);
	PORTB |= (1<<PB4);
}

int IR_read(void)
{
	int value;
	value = analog_read(); // read analog value from sensor
	//value = ((((uint32_t)value * 1000UL) >> 10) * 5); // convert value using euqation temp = Vin * 1000 / 1024 * Vref [milivolts]
	return value;
}

int analog_read()
{
	uint8_t low, high;
	
	ADCSRA |= _BV(ADSC);  // Run single conversion
	while(bit_is_set(ADCSRA, ADSC)); // Wait conversion is done

	// Read values
	low = ADCL;
        high = ADCH;

        // combine the two bytes
        return (high << 8) | low;
}

void adc_init(uint8_t pin)
{
	switch(pin) {
	case PB2: ADMUX = _BV(MUX0); break; // ADC1
        case PB4: ADMUX = _BV(MUX1); break; // ADC2
        case PB3: ADMUX = _BV(MUX0)|_BV(MUX1); break; // ADC3
        case PB5: // ADC0
	default: ADMUX = 0; break;
	}

	ADMUX &= ~_BV(REFS0); // explicit set VCC as reference voltage (5V)
	ADCSRA |= _BV(ADEN);  // Enable ADC
}
