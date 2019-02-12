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


void USART1_IRQHandler(void)
{
	extern Queue Uart1_Tx_Queue;
	extern Queue Uart1_Rx_Queue;
	extern struct UartBuffer uart1_RX_Buffer;
	extern struct UartBuffer uart1_Tx_Buffer;
	//接收完成中断
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
	{
		uart1_RX_Buffer.stateFlag=1;
		uart1_RX_Buffer.buffer[uart1_RX_Buffer.length++]=USART1->RDR;
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //清接收完成标志位	
	}
	
	//发送完成中断
	if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
	{   
		
		if(uart1_Tx_Buffer.length>0)
		{
			uart1_Tx_Buffer.length--;
			USART1->RDR=uart1_Tx_Buffer.buffer[uart1_Tx_Buffer.length];		
		}
		else
			uart1_Tx_Buffer.stateFlag=0;
		
		
		USART_ClearFlag(USART1, USART_FLAG_TC); //清发送完成标志位		
	}
	
}

void USART3_IRQHandler(void)
{
	
}

void TIM7_IRQHandler(void)
{
	
}
