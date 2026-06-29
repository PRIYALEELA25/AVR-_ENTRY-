/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 09:57:26
 * Author : hp
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD|=(1<<PORTD5);
    while (1) 
    {
		PORTD|=(1<<PORTD5);
		_delay_ms(3000);
		PORTD&=~(1<<PORTD5);
		_delay_ms(5000);
		
    }
	return 0;
}

