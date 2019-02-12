#include "Dri_SysTick.h"

uint32 systemTime;
//һ����׼ʱ�䵥λ��������ٸ�оƬ�ļ�ʱ��λ
const uint32 SYSTEM_HZ=1;	//1us
const uint32 SYSTEM_US=SYSTEM_HZ;
const uint32 SYSTEM_MS=SYSTEM_US*1000;
const uint32 SYSTEM_SEC=SYSTEM_MS*1000;
const uint32 SYSTEM_MIN=SYSTEM_SEC*60;
const uint32 SYSTEM_HOUR=SYSTEM_MIN*60;

uint8 SystemTime_Init()
{
	return SysTick_Init();
}

uint32 GetSystemTime()
{
	return systemTime;
}

BOOL CompareSysTime(const uint32 *obj,uint32 expect,uint8 UINT)
{
	switch(UINT)
	{
		case UINT_US:
		expect*=SYSTEM_US;
		break;
		case UINT_MS:
		expect*=SYSTEM_MS;
		break;
		case UINT_SEC:
		expect*=SYSTEM_SEC;
		break;
		case UINT_MIN:
		expect*=SYSTEM_MIN;
		break;
		case UINT_HOUR:
		expect*=SYSTEM_HOUR;
		break;
	}
	if(systemTime>=*obj+expect)
	{
		return TRUE;
	}
	return FALSE;
}

//������ʱ��ȴ�
void DelayUs_Block(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_US;
	while(systemTime<t1) __NOP;
	return;
}
	
void DelayMS_Block(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_MS;
	while(systemTime<t1) __NOP;
	return;
}
	
void DelaySec_Block(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_SEC;
	while(systemTime<t1) __NOP;
	return;
}

void DelayMin_Block(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_MIN;
	while(systemTime<t1) __NOP;
	return;
}

void DelayHour_Block(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_HOUR;
	while(systemTime<t1) __NOP;
	return;
}

//��������ʱ��ȴ�
/*
	timerTemp:ʱ���¼��
	expect:�����ȴ���ʱ��
	UINT:ʱ�䵥λ ��д UINT_HZ��UINT_SEC��UINT_MIN��UINT_HOUR

*/
BOOL WaitSysTime_UnBlocked(struct TimerTemp *timerTemp,uint32 expect,uint8 UINT)
{
	switch(timerTemp->state)
	{
		case UN_INIT:
			timerTemp->Time=systemTime;	//��ʼ��ʱ��
			timerTemp->state=COUNTING;	//��ʼ��ʱ״̬
			return FALSE;
			break;
			
		case COUNTING:
			return CompareSysTime(&timerTemp->Time,expect,UINT);		//�Ƚ�ʱ��
					
			break;
		case PAUSE:
			//timerTemp->Time=systemTime;	//ֹͣ��ʱʱ��
			return FALSE;
			break;
	}
	
	return FALSE;	
}

void ReSetTimerTemp(struct TimerTemp *timerTemp)
{
	timerTemp->state=UN_INIT;
	return;
}