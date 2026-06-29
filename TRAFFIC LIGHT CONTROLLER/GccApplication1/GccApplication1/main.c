/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 10:34:07
 * Author : hp
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>

void Timer1_Delay_1s(void)
{
	TCCR1A = 0x00;

	TCCR1B = (1 << WGM12);           // CTC Mode
	OCR1A = 15624;                   // 1 second

	TCNT1 = 0;
	TIFR1 |= (1 << OCF1A);           // Clear flag

	TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024

	while (!(TIFR1 & (1 << OCF1A)));

	TCCR1B = 0x00;                   // Stop timer
}

void Delay_Seconds(uint8_t sec)
{
	while(sec--)
	{
		Timer1_Delay_1s();
	}
}

int main(void)
{
	DDRB |= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB2);

	while (1)
	{
		// Green ON
		PORTB = (1 << PORTB0);
		Delay_Seconds(10);

		// Orange ON
		PORTB = (1 << PORTB1);
		Delay_Seconds(3);

		// Red ON
		PORTB = (1 << PORTB2);
		Delay_Seconds(10);
	}
}

