/*
 * lcd.c
 *
 * Created: 24-06-2026 11:37:07
 *  Author: hp
 */ 

	
#define F_CPU 16000000UL
#include "lcd.h"
#include <util/delay.h>

#define LCD_PORT PORTB
#define LCD_DDR DDRB

#define RS PB0
#define EN PB1

void LCD_Command(unsigned char cmd)
{
	LCD_PORT = (cmd & 0xF0);
	LCD_PORT &= ~(1 << RS);

	LCD_PORT |= (1 << EN);
	_delay_ms(2);
	LCD_PORT &= ~(1 << EN);

	LCD_PORT = ((cmd << 4) & 0xF0);

	LCD_PORT |= (1 << EN);
	_delay_ms(2);
	LCD_PORT &= ~(1 << EN);
}

void LCD_Char(unsigned char data)
{
	LCD_PORT = (data & 0xF0);
	LCD_PORT |= (1 << RS);

	LCD_PORT |= (1 << EN);
	_delay_ms(2);
	LCD_PORT &= ~(1 << EN);

	LCD_PORT = ((data << 4) & 0xF0);
	LCD_PORT |= (1 << RS);

	LCD_PORT |= (1 << EN);
	_delay_ms(2);
	LCD_PORT &= ~(1 << EN);
}

void LCD_Init(void)
{
	LCD_DDR = 0xFF;

	_delay_ms(20);

	LCD_Command(0x02);
	LCD_Command(0x28);
	LCD_Command(0x0C);
	LCD_Command(0x06);
	LCD_Command(0x01);
}

void LCD_String(char *str)
{
	while(*str)
	{
		LCD_Char(*str++);
	}
}

void LCD_Clear(void)
{
	LCD_Command(0x01);
}

void UpdateLCD(unsigned long count)
{
	LCD_Clear();

	LCD_Char((count / 100000000) % 10 + '0');
	LCD_Char((count / 10000000) % 10 + '0');
	LCD_Char((count / 1000000) % 10 + '0');
	LCD_Char((count / 100000) % 10 + '0');
	LCD_Char((count / 10000) % 10 + '0');
	LCD_Char((count / 1000) % 10 + '0');
	LCD_Char((count / 100) % 10 + '0');
	LCD_Char((count / 10) % 10 + '0');
	LCD_Char((count % 10) + '0');
}