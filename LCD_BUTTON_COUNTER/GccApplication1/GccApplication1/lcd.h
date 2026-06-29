/*
 * lcd.h
 *
 * Created: 24-06-2026 11:36:46
 *  Author: hp
 */ 


#ifndef LCD_H_
#define LCD_H_


#include <avr/io.h>

void LCD_Init(void);
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char data);
void LCD_String(char *str);
void LCD_Clear(void);
void UpdateLCD(unsigned long count);





#endif /* LCD_H_ */