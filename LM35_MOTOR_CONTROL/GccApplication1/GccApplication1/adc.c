/*
 * adc.c
 *
 * Created: 24-06-2026 11:11:38
 *  Author: hp
 */ 
#include "adc.h"

void ADC_Init(void)
{
	ADMUX = (1 << REFS0);

	ADCSRA = (1 << ADEN) |
	(1 << ADPS2) |
	(1 << ADPS1) |
	(1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | channel;

	ADCSRA |= (1 << ADSC);

	while (ADCSRA & (1 << ADSC));

	return ADC;
}

uint16_t ReadTemperature(void)
{
	uint16_t adc_value;

	adc_value = ADC_Read(0);

	return ((adc_value * 500UL) / 1024);
}