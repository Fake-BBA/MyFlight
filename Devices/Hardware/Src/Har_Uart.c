#include "Har_Uart.h"



void UART1_Init(uint32 BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);    
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate =BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	
	//IO状态设置 10pin_上拉输入  9pin_推挽输出

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearFlag(USART1, USART_FLAG_TC); /* 清发送完成标志，Transmission Complete flag */
	USART_ClearFlag(USART1,USART_IT_RXNE);
	//USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);// 采用空闲中断，目的是在产生空闲中断时，说明接收或者发送已经结束，此时可以读取DMA中的数据了。
	
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//接收缓冲区不为空中断
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);	//发送完成中断


}

void UART1_SendByte(uint8 byte)
{
	USART1->TDR = (byte & (uint16_t)0x01FF);
	
}

uint8 UART1_GetByte()
{
	return (uint16_t)(USART1->RDR & (uint16_t)0x01FF);
}

void UART3_Init(uint32 BaudRate)
{
	
}

