/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 10:21:48
 * Author : hp
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

uint8_t count = 0;


void DisplayBinary(uint8_t value)
{
	PORTB = (PORTB & 0xF0) | (value & 0x0F);
}

int main(void)
{
	// PB0-PB3 as Output 
	DDRB |= 0x0F;

	// PD2 as Input 
	DDRD &= ~(1<<PORTD2);

	// Internal Pull-up 
	PORTD |= (1<<PORTD2);

	DisplayBinary(count);

	while (1)
	{
		if (!(PIND & (1<<PORTD2)))   // IF Button Pressed
		{
			_delay_ms(50);         

			if (!(PIND & (1<<PORTD2)))
			{
				count++;

				if (count>15)
				{
					count = 0;
				}

				DisplayBinary(count);

				while (!(PIND & (1<<PORTD2))); // Wait for release
				_delay_ms(50);
			}
		}
	}
}
