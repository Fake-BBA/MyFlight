#include "Dri_Uart.h"
#include <stdio.h>
#include<string.h>

Queue Uart1_Tx_Queue;
Queue Uart1_Rx_Queue;

struct UartBuffer uart1_RX_Buffer;
struct UartBuffer uart1_Tx_Buffer;

uint8 TX_Stop=1;		//串口发送停止标志位

void Uart1_Init(uint32 BaudRate)
{
	UART1_Init(BaudRate);
}

void Uart3_Init(uint32 BaudRate);


uint8 Uart1_SendBytes(uint8* p_bytes, uint8 len)
{
	while(uart1_Tx_Buffer.stateFlag);	//若果发送区繁忙，则阻塞等
	memcpy(uart1_Tx_Buffer.buffer+uart1_Tx_Buffer.length,p_bytes,len);
	uart1_Tx_Buffer.length+=len;
	uart1_Tx_Buffer.stateFlag=1;	
}