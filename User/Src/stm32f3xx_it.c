/* Includes ------------------------------------------------------------------*/
#include "Devices.h"
#include "stm32f3xx_it.h"
  
/* Private typedef -----------------------------------------------------------*/
/*extern DMA_HandleTypeDef hdma_i2c1_rx;
extern DMA_HandleTypeDef hdma_i2c1_tx;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim7;
*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

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
	static elementype temp;
	
	//接收完成中断
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //清接收完成标志位
		InsertQueue(&Uart1_Rx_Queue,UART1_GetByte());
	}
	
	//发送完成中断
	if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
	{   
		extern uint8 TX_Stop;
		USART_ClearFlag(USART1, USART_FLAG_TC); //清发送完成标志位
		
		if(DeleteQueue(&Uart1_Tx_Queue, &temp)) //如果队列不为空
		{
			UART1_SendByte(temp);
			TX_Stop=0;
		}
		else
			TX_Stop=1;	//发送停止
	}
	
}

void USART3_IRQHandler(void)
{
	
}

void TIM7_IRQHandler(void)
{
	
}
