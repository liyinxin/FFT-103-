#include "USART1.h"
#include <stdio.h>

void USART1_Configuration(void)         
{	
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;                 //申明结构体
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);                                             //开启USART1和GPIOA时钟
	
	/*配置USART1-TX(PA.09)*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOA, &GPIO_InitStructure);     
	
	/*配置USART1-RX(PA.10)*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    
    GPIO_Init(GPIOA, &GPIO_InitStructure);      
	/*配置USRAT1模式*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//设置优先级分组长度
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//选择通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		// 设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//设置主从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//使能
	NVIC_Init(&NVIC_InitStructure);	
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
		
}

void Uart1_PutChar(u8 ch)
{
  USART_SendData(USART1,ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
}

/*重定向c库函数printf到USART1*/
int fputc(int ch, FILE *f)
{
			/* 发送一个字节数据到USART1 */
	USART_SendData(USART1, (uint8_t) ch);
			
			/* 等待发送完毕 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
		
	return (ch);
}

///*重定向c库函数scanf到USART1*/
//int fgetc(FILE *f)
//{
//		/* 等待串口1输入数据 */
//		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

//		return (int)USART_ReceiveData(USART1);
//}

