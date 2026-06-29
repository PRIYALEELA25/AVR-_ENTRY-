/*
 * bmp.h
 *
 * Created: 24-06-2026 21:01:08
 *  Author: hp
 */ 


#ifndef BMP_H_
#define BMP_H_

#include <stdint.h>

#define BMP280_ADDR         0x76  
void bmp280_init(void);
void bmp280_read_environment(float *temperature, float *pressure);





#endif /* BMP_H_ */