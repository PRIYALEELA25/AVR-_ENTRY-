/*
 * adc.h
 *
 * Created: 24-06-2026 11:12:02
 *  Author: hp
 */ 


#ifndef ADC_H_
#define ADC_H_


#include <avr/io.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
uint16_t ReadTemperature(void);





#endif /* ADC_H_ */