#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"

int main(void)
{
  /* loop */
  while (1) {
    while(ch!=t){
      ch = uart_getc();
      c[i] = ch;
      i++;
    }
    c[i] = '\0';

    // if(c=='2'){
    //   c = uart_getc();
    //   uart_putc(c);
    //   uart_puts(" ICT");
    //   uart_putc('\r');
    //   uart_putc('\n');
    //}
  }
}

void serial_read(void){
  char SerialBuffer[20];
  char CurrentChar;
  int index = 0;
  while(CurrentChar!=t){
    ch = uart_getc();
    c[index] = ch;
    index++;
  }
  c[index] = '\0';
}
