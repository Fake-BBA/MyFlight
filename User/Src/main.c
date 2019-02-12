#include "stm32f30x.h"
#include "Myconfiguration.h"
#include "Devices.h"
#include <stdio.h>

int main()
{
	SystemTime_Init();
	Sys_LED_Init();
	Buzzer_Init();
	Uart1_Init(115200);
	Sys_LED_OFF();
	
	struct TimerTemp t1;
	ReSetTimerTemp(&t1);
	while(1)
	{
		//DelaySec_Block(1);
		
		
		if(WaitSysTime_UnBlocked(&t1,1,UINT_SEC))
		{
			//Buzzer_Negative();
			Sys_LED_Negative();
			ReSetTimerTemp(&t1);
			//Uart1_SendBytes("Hello World!",12);
		}
	}
	
	return 0;
}

