#ifndef _HAR_UART_H__
#define _HAR_UART_H__

#include "stm32f30x.h"
#include "MyConfiguration.h"


void UART1_Init(uint32 BaudRate);
void UART3_Init(uint32 BaudRate);

void UART1_SendByte(uint8 byte);
uint8 UART1_GetByte();

#define UART1_MAX_BUFF_SIZE	1000
enum BufferState{
	SEND_BUSY=0,	//正在发送
	SEND_FREE=1,	//不在发送
	SEND_COMPLETE=2,//发送完成
	
	RECV_BUSY=0,	//正在接收
	RECV_FREE=1,	//接收数据已读
	RECV_COMPLETE=2	//接收完成
	
};

struct UartBuffer{
	enum BufferState stateFlag;	//发送:0正在发送 1：发送完成 接收0：正在接收，1：接收完成
	uint8 length;	//内容长度
	uint32 startTime;	//开始接收时间
	uint32 lastTime;	//上一次接收时间
	uint8 buffer[UART1_MAX_BUFF_SIZE];	//最大数据容量为100
	
};
uint8 UART1_SendCtrl();
uint8 UART1_SendBytes(uint8* p_bytes, uint8 len);
uint8 UART1_GetBytes(uint8 *p_bytes);

#endif