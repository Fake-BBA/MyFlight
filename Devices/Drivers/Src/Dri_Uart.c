#include "Dri_Uart.h"
#include <stdio.h>

Queue Uart1_Tx_Queue;
Queue Uart1_Rx_Queue;

uint8 TX_Stop=1;		//串口发送停止标志位

void Uart1_Init(uint32 BaudRate)
{
	UART1_Init(BaudRate);
	InitQueue(&Uart1_Tx_Queue);
}

void Uart3_Init(uint32 BaudRate);

void Uart1_SendBytes(uint8* p_bytes, uint8 len)
{
	uint8 i=0;
	uint8 temp;
	
	while(i<len)
	{
		//若插入队列成功，则继续插入下一个，否则等待
		if(InsertQueue(&Uart1_Tx_Queue,*(p_bytes+i)))
			i++;
		else __NOP;	
	}

	
	//temp=USART1->ISR;
	//USART1->ISR &=~(1<<6);
	//USART1->ISR |=1<<6;		//向发送完成寄存器置1产出发送完成中断
	//如果发送未完成==RESET，完成==SET
	if(TX_Stop)		//若发送停止了
	{
		DeleteQueue(&Uart1_Tx_Queue,&temp);
		UART1_SendByte(temp);	//重新激活硬件发送
	}
}

//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	UART1_SendByte(ch);
	return ch;
}


uint8 Uart1_GetBytes();
