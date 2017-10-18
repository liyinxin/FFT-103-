/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"
#include <stdio.h>



/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */

void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{	
}



/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
// extern void TimingDelay_Decrement(void);
void SysTick_Handler(void)
{		
}



// extern volatile u32 time;
// void TIM2_IRQHandler(void)
// {
// 	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
// 	{	
// 		time ++;
// 		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  		 
// 	}		 	
// }


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 
  
  
void EXTI9_5_IRQHandler(void)
{
	
	if(EXTI_GetITStatus(EXTI_Line8) != RESET) //ȷ���Ƿ������EXTI Line8�ж�
	{
	led1(ON);
		printf("\r\n  STM32  \r\n");
	
		
		
		EXTI_ClearITPendingBit(EXTI_Line8);     //����жϱ�־λ
	}  
	
	
	if(EXTI_GetITStatus(EXTI_Line9) != RESET) //ȷ���Ƿ������EXTI Line9�ж�
	{
	

		
		EXTI_ClearITPendingBit(EXTI_Line9);     //����жϱ�־λ
	}  
	
	
}


void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET) //ȷ���Ƿ������EXTI Line10�ж�
	{

		
		
		EXTI_ClearITPendingBit(EXTI_Line10);     //����жϱ�־λ
	}  
	
	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET) //ȷ���Ƿ������EXTI Line11�ж�
	{
		

		
		EXTI_ClearITPendingBit(EXTI_Line11);     //����жϱ�־λ
	}  
	
	
	if(EXTI_GetITStatus(EXTI_Line12) != RESET) //ȷ���Ƿ������EXTI Line12�ж�
	{
		
	
		
		EXTI_ClearITPendingBit(EXTI_Line12);     //����жϱ�־λ
	}  
	
	
	if(EXTI_GetITStatus(EXTI_Line13) != RESET) //ȷ���Ƿ������EXTI Line13�ж�
	{
		

		
		EXTI_ClearITPendingBit(EXTI_Line13);     //����жϱ�־λ
	}  
	  

}

void USART1_IRQHandler(void)
{
	uint8_t ch;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
	    //ch = USART1->DR;
			ch = USART_ReceiveData(USART1);
	  	printf( "%c", ch );    //�����ܵ�������ֱ�ӷ��ش�ӡ
	} 
	 
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
