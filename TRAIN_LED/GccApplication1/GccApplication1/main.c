/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 10:16:18
 * Author : hp
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Configure PORTB as output
	DDRB = 0xFF;

	while (1)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			PORTB = (1 << i);   // Turn ON only one LED
			_delay_ms(200);     //  delay
		}
	}
}