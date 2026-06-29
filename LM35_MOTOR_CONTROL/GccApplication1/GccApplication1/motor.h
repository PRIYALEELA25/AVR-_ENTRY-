/*
 * motor.h
 *
 * Created: 24-06-2026 11:12:48
 *  Author: hp
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_


#include <avr/io.h>

uint8_t CalculateSpeed(uint16_t temp);
void SetMotorSpeed(uint8_t speed);






#endif /* MOTOR_H_ */