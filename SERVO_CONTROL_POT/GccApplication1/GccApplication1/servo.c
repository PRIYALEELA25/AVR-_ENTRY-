/*
 * servo.c
 *
 * Created: 24-06-2026 11:28:05
 *  Author: hp
 */ 
#include "servo.h"

void Servo_Init(void)
{
	DDRB |= (1 << PORTB1);      // OC1A output

	/* Timer1 Fast PWM, TOP = ICR1 */
	TCCR1A = (1 << COM1A1) |
	(1 << WGM11);

	TCCR1B = (1 << WGM13) |
	(1 << WGM12) |
	(1 << CS11);   // Prescaler 8

	ICR1 = 39999;           // 50Hz PWM
}

void Servo_SetPosition(uint16_t adc_value)
{
	uint16_t pulse_width;

	
	pulse_width = 2000 + ((uint32_t)adc_value * 2000) / 1023;

	OCR1A = pulse_width;
}