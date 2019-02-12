#include "Har_LED.h"

void Sys_LED_PinInit()
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	/* GPIOE Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
	return;
}

void Sys_LED_PinSet()
{
	/* Set PB3 */
    GPIO_SetBits(GPIOB,GPIO_Pin_3); 
	
	return;
}

void Sys_LED_PinReSet()
{
	 /*Reset PB3*/
    GPIO_ResetBits(GPIOB,GPIO_Pin_3); 
	return;
}

/*
	引脚电平取反

*/
void Sys_LED_PinNegative()
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_3,1-GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_3));
	return;
}

/*
	返还引脚输出的值
*/
uint8 Sys_LED_PinState()
{
	return GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_3);
}