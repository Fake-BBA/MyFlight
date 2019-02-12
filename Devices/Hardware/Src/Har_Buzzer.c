#include "Har_Buzzer.h"

void Buzzer_PinInit()
{
	
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	/* GPIOE Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	return;
} 

void Buzzer_PinSet()
{
	GPIO_SetBits(GPIOC,GPIO_Pin_15); 
	return;
}

void Buzzer_PinReSet()
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_15);
	return;
}

/*
	引脚电平取反

*/
void Buzzer_PinNegative()
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_15,1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_15));
	return;
}

uint8 Buzzer_PinState()
{
	return GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_15);
}