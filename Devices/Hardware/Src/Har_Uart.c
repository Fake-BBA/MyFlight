#include "Har_Uart.h"
#include <stdio.h>
#include <string.h>

struct UartBuffer uart1_RX_Buffer;
struct UartBuffer uart1_TX_Buffer;

void _uart1_dma_configuration();

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

	USART_ClearFlag(USART1, USART_FLAG_TC); 
	USART_ClearFlag(USART1,USART_IT_RXNE);
	
	//uint8 t=USART1->RDR; //读取数据，才能清空缓冲区
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);// 采用空闲中断，目的是在产生空闲中断时，说明接收或者发送已经结束，此时可以读取DMA中的数据了。
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//接收缓冲区不为空中断
	USART_ITConfig(USART1, USART_IT_TC, ENABLE);	//发送完成中断,空闲中断不触发发送完成中断
	_uart1_dma_configuration();	//DMA初始化
	
	uart1_RX_Buffer.length=0;
	uart1_TX_Buffer.length=0;
	
	uart1_RX_Buffer.stateFlag=SEND_FREE;
	uart1_TX_Buffer.stateFlag=RECV_FREE;
}


static void _uart1_dma_configuration()
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/* DMA1 Channel5 (triggered by USART1 Rx event) Config */
	DMA_DeInit(DMA1_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->RDR;// 初始化外设地址  
	DMA_InitStructure.DMA_MemoryBaseAddr =uart1_RX_Buffer.buffer;// 内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//外设作为数据来源
	DMA_InitStructure.DMA_BufferSize = UART1_MAX_BUFF_SIZE ;// 缓存容量
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址不递增,串口的读寄存器是不变的
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// 内存递增，
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外设字节宽度
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;// 内存字节宽度
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 正常模式，即满了就不在接收了，而不是循环存储
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;// 优先级很高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // 内存与外设通信，而非内存到内存 
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);//

	DMA_Cmd(DMA1_Channel5, ENABLE);// 启动DMA

	/* DMA1 Channel4 (triggered by USART1 Tx event) Config */
	DMA_DeInit(DMA1_Channel4);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->TDR;  // 外设地址，串口1
	DMA_InitStructure.DMA_MemoryBaseAddr =uart1_TX_Buffer.buffer;// 发送内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;// 外设为传送数据目的地，即发送数据
	DMA_InitStructure.DMA_BufferSize = 0;  //发送长度为0
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);//初始化

	USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);// 使能DMA串口发送和接受请求
}

uint8 UART1_SendCtrl()
{
	if(uart1_TX_Buffer.length==0) return 0;
	if(uart1_TX_Buffer.stateFlag==SEND_BUSY) return 0;
	//while(DMA_GetCurrDataCounter(DMA1_Channel4));// 检查DMA发送通道内是否还有数据
	//DMA发送数据-要先关 设置发送长度 开启DMA
	DMA_Cmd(DMA1_Channel4, DISABLE);
	DMA1_Channel4->CNDTR = uart1_TX_Buffer.length;// 设置发送长度
	uart1_TX_Buffer.length=0;	//清空
	DMA_Cmd(DMA1_Channel4, ENABLE);  // 启动DMA发送
	uart1_TX_Buffer.stateFlag=SEND_BUSY;	//正在发送
}

uint8 UART1_SendBytes(uint8* p_bytes, uint8 len)
{
	extern struct UartBuffer uart1_TX_Buffer;
	memcpy(uart1_TX_Buffer.buffer+uart1_TX_Buffer.length,p_bytes,len);
	uart1_TX_Buffer.length+=len;			
}

uint8 UART1_GetBytes(uint8 *p_bytes)
{
	extern struct UartBuffer uart1_RX_Buffer;
	uint8 len=uart1_RX_Buffer.length;
	
	if(uart1_RX_Buffer.length==0) return 0;	//未有数据
	
	uart1_RX_Buffer.length=0;	//提取完数据后置零
	uart1_RX_Buffer.stateFlag=RECV_FREE;	//数据已读
	
	DMA_Cmd(DMA1_Channel5, DISABLE); // 关闭DMA
	memcpy(p_bytes,uart1_RX_Buffer.buffer,len);
	DMA_SetCurrDataCounter(DMA1_Channel5,UART1_MAX_BUFF_SIZE);	//设置DMA大小，才能清空之前的接收区
	DMA_Cmd(DMA1_Channel5, ENABLE); // 开启DMA
	return len;
}



void UART3_Init(uint32 BaudRate)
{
	
}

