/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 11:25:31
 * Author : hp
 */ 

#include <avr/io.h>

#define F_CPU 16000000UL
#include "adc.h"
#include "servo.h"

int main(void)
{
	uint16_t adc_value;

	ADC_Init();
	Servo_Init();

	while (1)
	{
		adc_value = ADC_Read(0);   // Potentiometer on ADC0

		Servo_SetPosition(adc_value);
	}
}


