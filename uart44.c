

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lib/libsoftwareuartfortyfour.h"


int main(void)
{
   UART_init();
   int value = 100;
   while(1)
   {
    uart_puts("H ");
    uart_putu(value);
    uart_putc('\n');
    _delay_ms(100);
   }

   return 0;
}

