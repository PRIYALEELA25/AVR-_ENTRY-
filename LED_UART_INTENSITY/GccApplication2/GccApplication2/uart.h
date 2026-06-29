/*
 * uart.h
 *
 * Created: 24-06-2026 20:38:15
 *  Author: hp
 */ 


#ifndef UART_H_
#define UART_H_



void UART_Init(void);
void UART_TxChar(char data);
void UART_TxString(char *str);
char UART_RxChar(void);





#endif /* UART_H_ */