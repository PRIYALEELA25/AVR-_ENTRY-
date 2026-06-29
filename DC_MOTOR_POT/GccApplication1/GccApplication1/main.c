/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 20:45:38
 * Author : hp
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>

#include "adc.h"
#include "pwm.h"

int main(void)
{
	unsigned int adc_value;
	unsigned char pwm_value;

	ADC_Init();
	PWM_Init();

	while(1)
	{
		adc_value = ADC_Read(0);

		pwm_value = adc_value / 4;

		PWM_SetDuty(pwm_value);
	}
}