/*
 * motor.c
 *
 * Created: 24-06-2026 11:12:25
 *  Author: hp
 */ 
#include "motor.h"

uint8_t CalculateSpeed(uint16_t temp)
{
	if(temp < 25)
	return 64;

	else if(temp < 35)
	return 128;

	else if(temp < 45)
	return 191;

	else
	return 255;
}

void SetMotorSpeed(uint8_t speed)
{
	OCR0A = speed;
}
