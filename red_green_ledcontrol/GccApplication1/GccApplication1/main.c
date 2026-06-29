/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 10:09:53
 * Author : hp
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Red LED (PD5) and Green LED (PD6) as Output
	DDRD |= (1 << PORTD5) | (1 << PORTD6);

	// Push Button (PD2) as Input
	DDRD &= ~(1 << PORTD2);

	// Enable Internal Pull-up
	PORTD |= (1 << PORTD2);

	// Initially Red LED ON, Green LED OFF
	PORTD |= (1 << PORTD5);
	PORTD &= ~(1 << PORTD6);

	uint8_t state = 0;   // 0 = Red ON, 1 = Green ON

	while (1)
	{
		// Button Pressed (Active Low)
		if (!(PIND & (1 << PORTD2)))
		{
			_delay_ms(50); 

			if (!(PIND & (1 << PORTD2)))
			{
				if (state == 0)
				{
					PORTD &= ~(1 << PORTD5); // Red OFF
					PORTD |= (1 << PORTD6);  // Green ON
					state = 1;
				}
				else
				{
					PORTD &= ~(1 << PORTD6); // Green OFF
					PORTD |= (1 << PORTD5);  // Red ON
					state = 0;
				}

				// Wait until button released
				while (!(PIND & (1 << PORTD2)));
				_delay_ms(50);
			}
		}
	}
}


