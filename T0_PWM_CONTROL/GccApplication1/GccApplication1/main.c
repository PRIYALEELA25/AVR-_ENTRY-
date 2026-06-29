/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 10:55:55
 * Author : hp
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

uint8_t level = 0;


void UpdatePWM(uint8_t level)
{
	switch(level)
	{
		case 0:
		OCR0A = 64;      // 25%
		break;

		case 1:
		OCR0A = 128;     // 50%
		break;

		case 2:
		OCR0A = 191;     // 75%
		break;

		case 3:
		OCR0A = 255;     // 100%
		break;
	}
}

int main(void)
{
	/* OC0A (PD6) as output */
	DDRD |= (1 << PORTD6);

	/* Push button on PD2 */
	DDRD &= ~(1 << PORTD2);
	PORTD |= (1 << PORTD2);

	/* Timer0 Fast PWM, Non-Inverting */
	TCCR0A = (1 << COM0A1) |
	(1 << WGM01)  |
	(1 << WGM00);

	/* Prescaler = 64 */
	TCCR0B = (1 << CS01) |
	(1 << CS00);

	UpdatePWM(level);

	while(1)
	{
		if(!(PIND & (1 << PORTD2)))
		{
			_delay_ms(50);

			if(!(PIND & (1 << PORTD2)))
			{
				//level++;

				if(level < 3)
				{
					level++;
				}

				UpdatePWM(level);

				while(!(PIND & (1 << PORTD2)));

				_delay_ms(50);
			}
		}
	}
}
