// #define F_CPU 8000000L
/*#include <avr/io.h>                    // adding header files
#include <util/delay.h>                // for _delay_ms()

int main(void)
{
   DDRB |= (1<<DDB5);                       // setting DDR of PORT C
   while(1)
   {
       // LED on
       PORTB |= (1<<PORTB5);            // PC0 = High = LED attached on PC0 is ON
       _delay_ms(1000);                // wait 500 milliseconds

       //LED off
       PORTB &= ~(1<<PORTB5);            // PC0 = Low = LED attached on PC0 is OFF
       _delay_ms(5000);                // wait 500 milliseconds
   }
}*/

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB0                     // PB0 as a LED pin

int
main(void)
{

        /* setup */
        DDRB = 0b00000001;              // set LED pin as OUTPUT
        PORTB = 0b00000000;             // set all pins to LOW

        /* loop */
        while (1) {
                PORTB ^= _BV(LED_PIN);  // toggle LED pin
                _delay_ms(500);
        }
}
