#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
  DDRB |= (1<<0); //Lautsprecher
  DDRB |= (1<<4);

  TCCR0A = (1<<WGM01); //Timer für Schwingkreis
  TCCR0B |= (1<<CS01);
  OCR0A = 250; //TODO: Frequenz berechnen
  TIMSK |= (1<<OCIE0A);
  sei();

  for (;;) {
    
  }
}

ISR (TIMER0_COMPA_vect) { //Togglen der Lautsprecher Pins bei Interrupt
  PORTB ^= (1<<4);
  PORTB ^= (1<<0);
}
