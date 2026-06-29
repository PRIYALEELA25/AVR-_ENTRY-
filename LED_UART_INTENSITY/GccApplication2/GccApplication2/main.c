/*
 * GccApplication2.c
 *
 * Created: 24-06-2026 20:29:00
 * Author : hp
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>

#include "uart.h"
#include "pwm.h"

int main(void)
{
	char buffer[4];
	char ch;
	unsigned char brightness;
	unsigned char i;

	UART_Init();
	PWM_Init();

	UART_TxString("LED Control Ready\r\n");

	while(1)
	{
		ch = UART_RxChar();

		/* ON Command */
		if(ch == 'O')
		{
			ch = UART_RxChar();

			if(ch == 'N')
			{
				PWM_SetBrightness(100);
				UART_TxString("LED is now ON\r\n");
			}
			else if(ch == 'F')
			{
				UART_RxChar();   // Receive second 'F'

				PWM_SetBrightness(0);
				UART_TxString("LED is now OFF\r\n");
			}
		}

		/* Brightness Command */
		else if(ch >= '0' && ch <= '9')
		{
			i = 0;
			buffer[i++] = ch;

			while(i < 3)
			{
				ch = UART_RxChar();

				if(ch == '\r' || ch == '\n')
				break;

				buffer[i++] = ch;
			}

			buffer[i] = '\0';

			/* String to Integer Conversion */
			brightness = 0;

			for(i = 0; buffer[i] != '\0'; i++)
			{
				brightness = brightness * 10 + (buffer[i] - '0');
			}

			if(brightness <= 100)
			{
				PWM_SetBrightness(brightness);

				UART_TxString("Brightness Updated\r\n");
			}
			else
			{
				UART_TxString("Invalid Value\r\n");
			}
		}
	}
}

