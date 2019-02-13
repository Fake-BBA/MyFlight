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
	SEND_BUSY=0,	//���ڷ���
	SEND_FREE=1,	//���ڷ���
	SEND_COMPLETE=2,//�������
	
	RECV_BUSY=0,	//���ڽ���
	RECV_FREE=1,	//���������Ѷ�
	RECV_COMPLETE=2	//�������
	
};

struct UartBuffer{
	enum BufferState stateFlag;	//����:0���ڷ��� 1��������� ����0�����ڽ��գ�1���������
	uint8 length;	//���ݳ���
	uint32 startTime;	//��ʼ����ʱ��
	uint32 lastTime;	//��һ�ν���ʱ��
	uint8 buffer[UART1_MAX_BUFF_SIZE];	//�����������Ϊ100
	
};
uint8 UART1_SendCtrl();
uint8 UART1_SendBytes(uint8* p_bytes, uint8 len);
uint8 UART1_GetBytes(uint8 *p_bytes);

#endif