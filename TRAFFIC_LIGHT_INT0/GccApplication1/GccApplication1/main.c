/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 10:44:22
 * Author : hp
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t emergency_flag = 0;

/* INT0 ISR */
ISR(INT0_vect)
{
	emergency_flag = 1;
}

int main(void)
{
	//PB0=Green, PB1=Orange, PB2=Red 
	DDRB |= (1<<PORTB0) | (1<<PORTB1) | (1<<PORTB2);

	/* PD2(INT0) as input */
	DDRD &= ~(1<<PORTD2);

	/* Enable internal pull-up */
	PORTD |= (1<<PORTD2);

	/* Falling edge trigger for INT0 */
	EICRA |= (1<<ISC01);
	EIMSK |= (1<<INT0);

	sei();

	while(1)
	{
		/* GREEN */
		PORTB = (1<<PORTB0);
		_delay_ms(10000);

		if(emergency_flag)
		{
			PORTB = (1<<PORTB0);
			_delay_ms(5000);

			emergency_flag = 0;
			continue;
		}

		/* ORANGE */
		PORTB = (1<<PORTB1);
		_delay_ms(3000);

		if(emergency_flag)
		{
			PORTB = (1<<PORTB0);
			_delay_ms(5000);

			emergency_flag = 0;
			continue;
		}

		/* RED */
		PORTB = (1<<PB2);
		_delay_ms(10000);

		if(emergency_flag)
		{
			PORTB = (1<<PORTB0);
			_delay_ms(5000);

			emergency_flag = 0;
		}
	}
}