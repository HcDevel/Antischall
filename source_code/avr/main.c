#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
//Set the Data Direction Register to output
DDRB |= (1<<0);
DDRB |= (1<<4);
PORTB ^= (1<<0);

while (1) {
//Toggle the signal
PORTB ^= (1<<4);
PORTB ^= (1<<0);
//wait 0.5 sec
_delay_us(1000);
}
return 0;
}
