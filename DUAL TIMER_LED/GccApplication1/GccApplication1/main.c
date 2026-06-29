/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 10:50:29
 * Author : hp
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t timer1_count = 0;
volatile uint8_t timer2_count = 0;

/* Timer1 Compare Match ISR */
ISR(TIMER1_COMPA_vect)
{
	timer1_count++;

	if(timer1_count >= 2)
	{
		PORTB ^= (1 << PORTB1);   // Toggle Status LED
		timer1_count = 0;
	}
}

// Timer2 Compare Match ISR 
ISR(TIMER2_COMPA_vect)
{
	timer2_count++;

	if(timer2_count >= 50)
	{
		PORTB ^= (1 << PORTB2);   // Toggle Heartbeat LED
		timer2_count = 0;
	}
}

int main(void)
{
	/* PB1 and PB2 as outputs */
	DDRB |= (1 << PORTB1) | (1 << PORTB2);

	/* ---------- Timer1 Configuration ---------- */
	TCCR1A = 0x00;
	TCCR1B = (1 << WGM12);     // CTC mode

	OCR1A = 15624;            // 1 second

	TIMSK1 = (1 << OCIE1A);   // Enable Compare Match Interrupt

	TCCR1B |= (1 << CS12) | (1 << CS10);   // Prescaler 1024

	/* ---------- Timer2 Configuration ---------- */
	TCCR2A = (1 << WGM21);    // CTC mode

	OCR2A = 155;              // 10 ms

	TIMSK2 = (1 << OCIE2A);   // Enable Compare Match Interrupt

	TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024

	sei();   // Enable Global Interrupts

	while(1)
	{
		
}
}