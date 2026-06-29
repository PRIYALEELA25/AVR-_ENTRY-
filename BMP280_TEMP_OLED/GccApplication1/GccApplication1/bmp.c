/*
 * bmp.c
 *
 * Created: 24-06-2026 21:01:25
 *  Author: hp
 */ #include "bmp.h"
 #include "i2c.h"

 // Calibration parameters 
 static uint16_t dig_T1;
 static int16_t  dig_T2, dig_T3;
 static uint16_t dig_P1;
 static int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
 static int32_t  t_fine;

 static uint8_t bmp280_read8(uint8_t reg) {
 i2c_start();
 i2c_write((BMP280_ADDR << 1) | 0);
 i2c_write(reg);
 i2c_start();
 i2c_write((BMP280_ADDR << 1) | 1);
 uint8_t val = i2c_read_nack();
 i2c_stop();
 return val;
 }

 static uint16_t bmp280_read16_LE(uint8_t reg) {
 i2c_start();
 i2c_write((BMP280_ADDR << 1) | 0);
 i2c_write(reg);
 i2c_start();
 i2c_write((BMP280_ADDR << 1) | 1);
 uint8_t lsb = i2c_read_ack();
 uint8_t msb = i2c_read_nack();
 i2c_stop();
 return (msb << 8) | lsb;
 }

 void bmp280_init(void) {
 
 dig_T1 = bmp280_read16_LE(0x88);
 dig_T2 = (int16_t)bmp280_read16_LE(0x8A);
 dig_T3 = (int16_t)bmp280_read16_LE(0x8C);
 dig_P1 = bmp280_read16_LE(0x8E);
 dig_P2 = (int16_t)bmp280_read16_LE(0x90);
 dig_P3 = (int16_t)bmp280_read16_LE(0x92);
 dig_P4 = (int16_t)bmp280_read16_LE(0x94);
 dig_P5 = (int16_t)bmp280_read16_LE(0x96);
 dig_P6 = (int16_t)bmp280_read16_LE(0x98);
 dig_P7 = (int16_t)bmp280_read16_LE(0x9A);
 dig_P8 = (int16_t)bmp280_read16_LE(0x9C);
 dig_P9 = (int16_t)bmp280_read16_LE(0x9E);

 
 i2c_start();
 i2c_write((BMP280_ADDR << 1) | 0);
 i2c_write(0xF5); 
 i2c_write(0x00);
 i2c_stop();


 i2c_start();
 i2c_write((BMP280_ADDR << 1) | 0);
 i2c_write(0xF4); 
 i2c_write(0x2B);
 i2c_stop();
 }

 void bmp280_read_environment(float *temperature, float *pressure) {

 i2c_start();
 i2c_write((BMP280_ADDR << 1) | 0);
 i2c_write(0xF7);
 i2c_start();
 i2c_write((BMP280_ADDR << 1) | 1);
 
 uint8_t p_msb  = i2c_read_ack();
 uint8_t p_lsb  = i2c_read_ack();
 uint8_t p_xlsb = i2c_read_ack();
 uint8_t t_msb  = i2c_read_ack();
 uint8_t t_lsb  = i2c_read_ack();
 uint8_t t_xlsb = i2c_read_nack();
 i2c_stop();

 int32_t adc_P = ((int32_t)p_msb << 12) | ((int32_t)p_lsb << 4) | (p_xlsb >> 4);
 int32_t adc_T = ((int32_t)t_msb << 12) | ((int32_t)t_lsb << 4) | (t_xlsb >> 4);

 // Compensation formula for Temperature 
 int32_t var1, var2;
 var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
 var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
 t_fine = var1 + var2;
 *temperature = (float)((t_fine * 5 + 128) >> 8) / 100.0f;

 // Compensation formula for Pressure
 int64_t v1, v2, p;
 v1 = ((int64_t)t_fine) - 128000;
 v2 = v1 * v1 * (int64_t)dig_P6;
 v2 = v2 + ((v1 * (int64_t)dig_P5) << 17);
 v2 = v2 + (((int64_t)dig_P4) << 35);
 v1 = ((v1 * v1 * (int64_t)dig_P3) >> 8) + ((v1 * (int64_t)dig_P2) << 12);
 v1 = (((((int64_t)1) << 47) + v1)) * ((int64_t)dig_P1) >> 33;

 if (v1 == 0) {
 *pressure = 0; 
 } else {
 p = 1048576 - adc_P;
 p = (((p << 31) - v2) * 3125) / v1;
 v1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
 v2 = (((int64_t)dig_P8) * p) >> 19;
 p = ((p + v1 + v2) >> 8) + (((int64_t)dig_P7) << 4);
 *pressure = (float)p / 256.0f / 100.0f; // Converted to hPa
 }
 }
