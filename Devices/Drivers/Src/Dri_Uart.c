#include "Dri_Uart.h"



void Uart1_Init(uint32 BaudRate)
{
	UART1_Init(BaudRate);
}

void Uart3_Init(uint32 BaudRate);


uint8 Uart1_SendBytes(uint8* p_bytes, uint8 len)
{
	UART1_SendBytes(p_bytes,len);
}

uint8 Uart1_GetBytes(uint8 *p_bytes)
{
	return UART1_GetBytes(p_bytes);
}

