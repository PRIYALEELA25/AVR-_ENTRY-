/*
 * servo.h
 *
 * Created: 24-06-2026 11:28:20
 *  Author: hp
 */ 


#ifndef SERVO_H_
#define SERVO_H_



#include <avr/io.h>

void Servo_Init(void);
void Servo_SetPosition(uint16_t adc_value);





#endif /* SERVO_H_ */