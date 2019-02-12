#ifndef _HAR_UART_H__
#define _HAR_UART_H__

#include "stm32f30x.h"
#include "MyConfiguration.h"


void UART1_Init(uint32 BaudRate);
void UART3_Init(uint32 BaudRate);

void UART1_SendByte(uint8 byte);
uint8 UART1_GetByte();
#endif