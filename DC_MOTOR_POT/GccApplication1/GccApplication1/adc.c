/*
 * adc.c
 *
 * Created: 24-06-2026 20:46:48
 *  Author: hp
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include "adc.h"

void ADC_Init(void)
{
	ADMUX = (1<<REFS0);

	ADCSRA = (1<<ADEN) |(1<<ADPS2) |(1<<ADPS1) |(1<<ADPS0);
}

unsigned int ADC_Read(unsigned char channel)
{
	ADMUX = (ADMUX & 0xF0) | channel;

	ADCSRA |= (1<<ADSC);

	while(ADCSRA & (1<<ADSC));

	return ADC;
}