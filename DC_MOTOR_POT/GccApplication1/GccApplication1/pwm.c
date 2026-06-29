/*
 * pwm.c
 *
 * Created: 24-06-2026 20:47:29
 *  Author: hp
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include "pwm.h"

void PWM_Init(void)
{
	DDRD |= (1<<PORTD6);

	TCCR0A = (1<<COM0A1) |(1<<WGM01)  |(1<<WGM00);

	TCCR0B = (1<<CS01) |(1<<CS00);

	OCR0A = 0;
}

void PWM_SetDuty(unsigned char duty)
{
	OCR0A = duty;
}