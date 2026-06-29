/*
 * i2c.h
 *
 * Created: 24-06-2026 21:04:40
 *  Author: hp
 */ 


#ifndef I2C_H_
#define I2C_H_


#define F_CPU 16000000UL
#include <avr/io.h>

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);



#endif /* I2C_H_ */