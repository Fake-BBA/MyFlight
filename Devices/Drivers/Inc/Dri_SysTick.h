#ifndef _DRI_SYSTICK_H__
#define _DRI_SYSTICK_H__

#include "Har_SysTick.h"

//一个标准时间单位会包含多少个芯片的计时单位
#define SYSTEM_MS	1
#define SYSTEM_SEC	SYSTEM_MS*1000
#define SYSTEM_MIN	SYSTEM_SEC*60
#define SYSTEM_HOUR	SYSTEM_MIN*60

#define MILLISECOND 1
#define SECOND		2
#define MINUTE		3
#define HOUR		4

uint8 SystemTime_Init();
//void Delay_us(uint32 nTime);
void DelayMS(uint32 nTime);
void DelaySec(uint32 nTime);
void DelayMin(uint32 nTime);
void DelayHour(uint32 nTime);

uint32 GetSystemTime();

uint8 WaitSystemTime(uint32 *systemTime,uint32 expectation,uint8 UNIT);

#endif