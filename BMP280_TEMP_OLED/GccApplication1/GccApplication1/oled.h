/*
 * oled.h
 *
 * Created: 24-06-2026 21:01:58
 *  Author: hp
 */ 


#ifndef OLED_H_
#define OLED_H_
#include <stdint.h>

#define OLED_ADDR   0x3C

void oled_init(void);
void oled_clear(void);
void oled_set_cursor(uint8_t page, uint8_t column);
void oled_print_char(char c);
void oled_print_string(const char *str);






#endif /* OLED_H_ */