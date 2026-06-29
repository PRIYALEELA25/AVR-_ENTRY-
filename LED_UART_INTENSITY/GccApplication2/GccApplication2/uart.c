/*
 * uart.c
 *
 * Created: 24-06-2026 20:38:30
 *  Author: hp
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include "uart.h"

void UART_Init(void)
{
	UBRR0H = 0;
	UBRR0L = 103;

	UCSR0B = (1<<RXEN0) | (1<<TXEN0);

	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void UART_TxChar(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));

	UDR0 = data;
}

void UART_TxString(char *str)
{
	while(*str)
	{
		UART_TxChar(*str++);
	}
}

char UART_RxChar(void)
{
	while(!(UCSR0A & (1<<RXC0)));

	return UDR0;
}