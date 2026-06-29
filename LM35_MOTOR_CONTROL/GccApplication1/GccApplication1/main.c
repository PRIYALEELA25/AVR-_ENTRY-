/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 11:08:04
 * Author : hp
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "motor.h"

uint8_t system_on = 0;

int main(void)
{
	uint16_t temperature;
	uint8_t speed;

	DDRD |= (1 << PORTD6);

	DDRD &= ~(1 << PORTD2);
	PORTD |= (1 << PORTD2);

	TCCR0A = (1 << COM0A1) |
	(1 << WGM01) |
	(1 << WGM00);

	TCCR0B = (1 << CS01) |
	(1 << CS00);

	ADC_Init();

	while(1)
	{
		if(!(PIND & (1 << PORTD2)))
		{
			_delay_ms(50);

			if(!(PIND & (1 << PORTD2)))
			{
				system_on ^= 1;

				while(!(PIND & (1 << PORTD2)));
			}
		}

		if(system_on)
		{
			temperature = ReadTemperature();

			speed = CalculateSpeed(temperature);

			SetMotorSpeed(speed);
		}
		else
		{
			SetMotorSpeed(0);
		}
	}
}
