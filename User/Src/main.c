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
	
	struct TimerTemp t2;
	ReSetTimerTemp(&t2);
	uint8 test[100];
	uint8 n=0;
	while(1)
	{
		//DelaySec_Block(1);
		
		n=Uart1_GetBytes(test);
		Uart1_SendBytes(test,n);
		if(WaitSysTime_UnBlocked(&t1,1,UINT_SEC))
		{
			//Buzzer_Negative();
			Sys_LED_Negative();
			ReSetTimerTemp(&t1);
		
		}
		
		if(WaitSysTime_UnBlocked(&t2,10,UINT_MS))
		{
			UART1_SendCtrl();
			ReSetTimerTemp(&t2);
		}
		UART1_SendCtrl();
		
	}
	
	return 0;
}

