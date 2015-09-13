#define F_CPU 1000000
#define TON_FREQUENZ 250 //Ton Frequenz in Hz

#define CTC_VALUE (F_CPU / 8 / 2 / TON_FREQUENZ)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char an=1;

int main(void) {
  DDRB |= (1<<0); //Lautsprecher
  DDRB |= (1<<4);
  unsigned char antischall_an=0;

  DDRB |= (1<<2); //LED
  unsigned char blinken=0;

  DDRB &= ~(1<<1); //Taster
  PORTB |=(1<<1);
  unsigned char zeit_gedrueckt;

  TCCR0A = (1<<WGM01); //Timer für Schwingkreis
  TCCR0B |= (1<<CS01);
  OCR0A = CTC_VALUE;
  TIMSK |= (1<<OCIE0A);
  sei();

  for (;;) {
    if (!(PINB & (1<<1))) {
      _delay_ms(100);
      for (zeit_gedrueckt=0;!(PINB & (1<<1)) && zeit_gedrueckt<250; ++zeit_gedrueckt)
        _delay_ms(2);

      if (zeit_gedrueckt == 250)
        if (an) an=0;
        else an=1;
      else {
        PORTB ^= (1<<4);
        if (antischall_an) antischall_an=0;
        else antischall_an=1;
        if (!an) an=1;
      }

      for (;!(PINB & (1<<1)););
      _delay_ms(100);
    }

    if (!an) {
      if (blinken == 250) { blinken=0; PORTB ^= (1<<2); }
      else ++blinken;
      _delay_ms(2);
    } else if (antischall_an) {
      PORTB |= (1<<2);
    } else
      PORTB &= ~(1<<2);
  }
}

ISR (TIMER0_COMPA_vect) { //Togglen der Lautsprecher Pins bei Interrupt
  if (an) {
    PORTB ^= (1<<4);
    PORTB ^= (1<<0);
  }
}
