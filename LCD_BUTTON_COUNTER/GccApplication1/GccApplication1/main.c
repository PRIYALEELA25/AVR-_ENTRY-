/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 11:35:32
 * Author : hp
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "button.h"

unsigned long counter = 0;

int main(void)
{
	DDRD &= ~(1 << PORTD2);
	PORTD |= (1 << PORTD2);

	LCD_Init();

	UpdateLCD(counter);

	while(1)
	{
		uint8_t status;

		status = CheckButtonPress();

		if(status == 1)
		{
			counter++;

			UpdateLCD(counter);
		}
		else if(status == 2)
		{
			counter = 0;

			UpdateLCD(counter);
		}
	}
}
