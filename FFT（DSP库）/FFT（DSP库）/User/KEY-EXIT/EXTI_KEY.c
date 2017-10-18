#include "EXTI_KEY.h"

/*NVIC配置*/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;							//申明结构体
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//设置优先级分组长度
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//选择通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		// 设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//设置主从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//使能
	NVIC_Init(&NVIC_InitStructure);									//初始化
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//设置优先级分组长度
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//选择通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		// 设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				//设置主从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//使能
	NVIC_Init(&NVIC_InitStructure);									//初始化
	
}


void EXTI_PE_Configuration(void)
{	
	
	
	EXTI_InitTypeDef EXTI_InitStructure;		//申明结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
	
	NVIC_Configuration() ;
	
	/*GPIO——PE8设置*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource8);	//选择外部中断引脚
	EXTI_InitStructure.EXTI_Line = EXTI_Line8; 					//选择端口
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//下降沿为中断请求
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//使能
	EXTI_Init(&EXTI_InitStructure);							
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);	//选择外部中断引脚
	EXTI_InitStructure.EXTI_Line = EXTI_Line9; 					//选择端口
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//下降沿为中断请求
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//使能
	EXTI_Init(&EXTI_InitStructure);							


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource10);	//选择外部中断引脚
	EXTI_InitStructure.EXTI_Line = EXTI_Line10; 					//选择端口
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//下降沿为中断请求
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//使能
	EXTI_Init(&EXTI_InitStructure);							


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource11);	//选择外部中断引脚
	EXTI_InitStructure.EXTI_Line = EXTI_Line11; 					//选择端口
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//下降沿为中断请求
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//使能
	EXTI_Init(&EXTI_InitStructure);		

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource12);	//选择外部中断引脚
	EXTI_InitStructure.EXTI_Line = EXTI_Line12; 					//选择端口
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//下降沿为中断请求
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//使能
	EXTI_Init(&EXTI_InitStructure);	



	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource13);	//选择外部中断引脚
	EXTI_InitStructure.EXTI_Line = EXTI_Line13; 					//选择端口
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//下降沿为中断请求
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//使能
	EXTI_Init(&EXTI_InitStructure);							


}

/*中断程序*/
// void EXTI15_10_IRQHandler(void)
// {
// 	if(EXTI_GetITStatus(EXTI_Line12) != RESET) //确保是否产生了EXTI Line中断
// 	{
// 		// LED 	
// 		GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)((1-
// 				 GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0))));
// 		
// 		
// 		EXTI_ClearITPendingBit(EXTI_Line12);     //清除中断标志位
// 	}  
// }

