/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

char USART_Init(const long int baudrate);
void Write_USART(uint8_t a);
void Write_USART_String(char *a);
char UART_Init(const long int baudrate);
uint8_t Read_USART(void);
void Read_USART_String(char *Output, unsigned int length);
      

#endif	/* XC_HEADER_TEMPLATE_H */

