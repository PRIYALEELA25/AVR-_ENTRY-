/*
 * GccApplication1.c
 *
 * Created: 24-06-2026 20:59:59
 * Author : hp
 */ #define F_CPU 16000000UL
 #include <avr/io.h>
 #include <util/delay.h>
 #include <stdio.h>
 #include "i2c.h"
 #include "bmp.h"
 #include "oled.h"

 int main(void) {
 float temperature = 0.0f;
 float pressure = 0.0f;
 char temp_buffer[16];
 char pres_buffer[16];

 // Initialization
 i2c_init();
 oled_init();
 bmp280_init();

 while (1) {
 
 bmp280_read_environment(&temperature, &pressure);

 
 int temp_whole = (int)temperature;
 int temp_frac = (int)((temperature - temp_whole) * 10);
 int pres_whole = (int)pressure;

 snprintf(temp_buffer, sizeof(temp_buffer), "TEMP: %d.%d C", temp_whole, temp_frac);
 snprintf(pres_buffer, sizeof(pres_buffer), "PRES: %d HPA", pres_whole);

 
 oled_clear();
 
 oled_set_cursor(2, 10); 
 oled_print_string(temp_buffer);
 
 oled_set_cursor(4, 10); 
 oled_print_string(pres_buffer);

 
 _delay_ms(2000);
 }
 }