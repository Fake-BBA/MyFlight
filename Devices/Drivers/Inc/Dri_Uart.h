#ifndef _DRI_UART_H__
#define _DRI_UART_H__

#include "Har_Uart.h"

void Uart1_Init(uint32 BaudRate);
void Uart3_Init(uint32 BaudRate);

struct UartBuffer{
	bool stateFlag;	//0 is free,1:is busy
	uint8 length;	//���ݳ���
	uint8 buffer[100];	//�����������Ϊ100
	
};

uint8 Uart1_SendBytes(uint8* p_bytes, uint8 len);
uint8 Uart1_GetByte();
#endif