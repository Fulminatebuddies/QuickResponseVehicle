#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/libsoftwareuart.h"

char SerialBuffer[20];

int main(void)
{
  /* loop */
  while (1) {
    serial_read();
    if(SerialBuffer == "001"){
      uart_puts("123t");
    }
  }
}

void serial_read(void){
  char CurrentChar;
  int index = 0;
  while(CurrentChar!=t){
    CurrentChar = uart_getc();
    SerialBuffer[index] = CurrentChar;
    index++;
  }
  SerialBuffer[index] = '\0';
}
