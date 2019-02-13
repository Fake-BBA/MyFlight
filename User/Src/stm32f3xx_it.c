/* Includes ------------------------------------------------------------------*/
#include "Devices.h"
#include "stm32f3xx_it.h"

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
	extern uint32 systemTime;
	systemTime++;
}

/******************************************************************************/
/*                 STM32F3xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) , for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f3xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
void DMA1_Channel2_IRQHandler(void)
{

}

void DMA1_Channel3_IRQHandler(void)
{
	
}

void DMA1_Channel4_IRQHandler(void)
{
	
}

void DMA1_Channel5_IRQHandler(void)
{

}

void DMA1_Channel6_IRQHandler(void)
{
	
}

void DMA1_Channel7_IRQHandler(void)
{
	
}

void I2C1_EV_IRQHandler(void)
{
	
}

void I2C1_ER_IRQHandler(void)
{
	
}

typedef enum _UartEvent_
{
   E_uart_0 = 0,// 没有事件
   E_uart_tc=0x40,                  //发送完成
   E_uart_idle=0x80,               //接收完成
}UartEvent;
u16 receivelen = 0;// 声明接收数据长度
UartEvent event;//申明一个事件参数
 
//清除DMA 缓存，并终止DMA
void Uart_Dma_Clr(void)
{
    DMA_Cmd(DMA1_Channel4, DISABLE);
    DMA1_Channel4->CNDTR=0;
    DMA_Cmd(DMA1_Channel5, DISABLE);
    DMA1_Channel5->CNDTR=1024 ;
    DMA_Cmd(DMA1_Channel5, ENABLE);
}
// 获取一个事件，事件分为发送完成事件和接收完成事件，可以根据事件进行进行处理
UartEvent Uart_Get_Event(void)
{
  UartEvent e;
  if(!DMA1_Channel5->CNDTR) Uart_Dma_Clr();// 如果产生一个事件后，接收数据通道已经没有了缓存空间，进行清除DMA清空
  return event;
}

void Uart_Set_Event(UartEvent event_in)
{
	
}
// 清除对应的事件
void Uart_Clr_Event(UartEvent event_in)
{
    event&=~event_in;
}

void USART1_IRQHandler(void)
{
	extern struct UartBuffer uart1_RX_Buffer;
	extern struct UartBuffer uart1_TX_Buffer;
	
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!= RESET)
	{
		u8 tem=USART1->RDR;	//读寄存器，清空
		uart1_RX_Buffer.length =UART1_MAX_BUFF_SIZE-DMA1_Channel5->CNDTR;// 总的buf长度减去剩余buf长度，得到接收到数据的长度
		
		if(uart1_RX_Buffer.stateFlag==RECV_FREE)
			uart1_RX_Buffer.startTime=GetSystemTime();
		
		uart1_RX_Buffer.stateFlag=RECV_COMPLETE;	//接收完成
		USART_ClearITPendingBit(USART1, USART_IT_IDLE);	
	} 

	if(USART_GetITStatus(USART1,USART_IT_TC)!= RESET) // 全部数据发送完成，产生该标记**
	{
		USART_ClearITPendingBit(USART1, USART_IT_TC);   // 清除完成标记
		DMA_Cmd(DMA1_Channel4, DISABLE); // 关闭DMA
		uart1_TX_Buffer.stateFlag=SEND_COMPLETE;     //设置发送完成事件
	}
	
}

void USART3_IRQHandler(void)
{
	
}

void TIM7_IRQHandler(void)
{
	
}
