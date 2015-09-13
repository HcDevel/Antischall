#define F_CPU 1000000
#define TON_FREQUENZ 250 //Ton Frequenz in Hz

#define CTC_VALUE (F_CPU / 8 / 2 / TON_FREQUENZ)

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char an=1;

int main(void) {
  DDRB |= (1<<0); //Lautsprecher
  DDRB |= (1<<4);

  TCCR0A = (1<<WGM01); //Timer für Schwingkreis
  TCCR0B |= (1<<CS01);
  OCR0A = CTC_VALUE;
  TIMSK |= (1<<OCIE0A);
  sei();

  for (;;) {

  }
}

ISR (TIMER0_COMPA_vect) { //Togglen der Lautsprecher Pins bei Interrupt
  if (an) {
    PORTB ^= (1<<4);
    PORTB ^= (1<<0);
  }
}
