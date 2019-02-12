#include "Dri_SysTick.h"

uint32 systemTime;

uint8 SystemTime_Init()
{
	return SysTick_Init();
}
	
uint32 GetSystemTime()
{	
	return systemTime;
}

uint8 WaitSystemTime(uint32 *systemTime,uint32 expectation,uint8 UNIT)
{
	switch(UNIT)
	{
		case MILLISECOND:
			expectation*=SYSTEM_MS;
			break;
		case SECOND:
			expectation*=SYSTEM_SEC;
			break;
		case MINUTE:
			expectation*=SYSTEM_MIN;
			break;
		case HOUR:
			expectation*=SYSTEM_HOUR;
			break;
	}
	
	if(systemTime>=expectation)
		return TRUE;
	else
		return FALSE;
}

void DelayMS(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_MS;
	while(systemTime<t1) __NOP;
	return;
}
	
void DelaySec(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_SEC;
	while(systemTime<t1) __NOP;
	return;
}

void DelayMin(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_MIN;
	while(systemTime<t1) __NOP;
	return;
}

void DelayHour(uint32 nTime)
{
	uint32 t1=systemTime+nTime*SYSTEM_HOUR;
	while(systemTime<t1) __NOP;
	return;
}
