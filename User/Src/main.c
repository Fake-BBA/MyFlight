#include "stm32f30x.h"
#include "Myconfiguration.h"
#include "Devices.h"
#include <stdio.h>

int main()
{
	SystemTime_Init();
	Sys_LED_Init();
	Buzzer_Init();
	Uart1_Init(1500000);
	
	//printf("%s","Hello World!");
	//Uart1_SendBytes("System initialization successful!",33);
	Sys_LED_OFF();
	while(1)
	{
		DelayMS(1);
		Sys_LED_Negative();
		//printf("%s","Hello World!");
		Uart1_SendBytes("Hello World!",12);
		//Buzzer_ON();
		//DelayMS(30);
		//Buzzer_OFF();
		
		
	}
	
	return 0;
}

