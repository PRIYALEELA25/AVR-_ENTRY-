/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 11:00:09
 * Author : hp
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

uint8_t duty_level = 0;


void SetDutyCycle(uint8_t level)
{
	switch(level)
	{
		case 0:
		OCR0A = 64;     // 25%
		break;

		case 1:
		OCR0A = 128;    // 50%
		break;

		case 2:
		OCR0A = 191;    // 75%
		break;

		case 3:
		OCR0A = 255;    // 100%
		break;
	}
}

int main(void)
{
	 
	DDRD |= (1 << PORTD6);

	
	DDRD &= ~(1 << PORTD2);
	PORTD |= (1 << PORTD2);

	// Timer0 Fast PWM, Non-Inverting Mode 
	TCCR0A = (1 << COM0A1) |
	(1 << WGM01)  |
	(1 << WGM00);

	//Prescaler = 64 
	TCCR0B = (1 << CS01) |
	(1 << CS00);

	SetDutyCycle(duty_level);

	while(1)
	{
		if(!(PIND & (1 << PORTD2)))
		{
			_delay_ms(50);   // Debounce

			if(!(PIND & (1 << PORTD2)))
			{
				duty_level++;

				if(duty_level > 3)
				{
					duty_level = 0;
				}

				SetDutyCycle(duty_level);

				while(!(PIND & (1 << PORTD2)));

				_delay_ms(50);
			}
		}
	}
}