/*
 * button.c
 *
 * Created: 24-06-2026 11:36:26
 *  Author: hp
 */ 
#define F_CPU 16000000UL
#include "button.h"
#include <util/delay.h>

uint8_t CheckButtonPress(void)
{
	if (!(PIND & (1 << PORTD2)))      // Button pressed
	{
		_delay_ms(30);             // Debounce

		if (!(PIND & (1 << PORTD2)))
		{
			uint16_t time = 0;

			while (!(PIND & (1 << PORTD2)))
			{
				_delay_ms(10);
				time += 10;

				if (time >= 2000)
				{
					while (!(PIND & (1 << PORTD2))); // Wait for release
					return 2;                     // Long press
				}
			}

			return 1;                            // Short press
		}
	}

	return 0;
}