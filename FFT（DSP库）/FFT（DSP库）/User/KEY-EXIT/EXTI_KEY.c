#include "EXTI_KEY.h"

/*NVIC����*/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;							//�����ṹ��
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//�������ȼ����鳤��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ѡ��ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		// ������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//�����������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ʹ��
	NVIC_Init(&NVIC_InitStructure);									//��ʼ��
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//�������ȼ����鳤��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ѡ��ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		// ������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				//�����������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ʹ��
	NVIC_Init(&NVIC_InitStructure);									//��ʼ��
	
}


void EXTI_PE_Configuration(void)
{	
	
	
	EXTI_InitTypeDef EXTI_InitStructure;		//�����ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
	
	NVIC_Configuration() ;
	
	/*GPIO����PE8����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource8);	//ѡ���ⲿ�ж�����
	EXTI_InitStructure.EXTI_Line = EXTI_Line8; 					//ѡ��˿�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//�½���Ϊ�ж�����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//ʹ��
	EXTI_Init(&EXTI_InitStructure);							
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);	//ѡ���ⲿ�ж�����
	EXTI_InitStructure.EXTI_Line = EXTI_Line9; 					//ѡ��˿�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//�½���Ϊ�ж�����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//ʹ��
	EXTI_Init(&EXTI_InitStructure);							


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource10);	//ѡ���ⲿ�ж�����
	EXTI_InitStructure.EXTI_Line = EXTI_Line10; 					//ѡ��˿�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//�½���Ϊ�ж�����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//ʹ��
	EXTI_Init(&EXTI_InitStructure);							


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource11);	//ѡ���ⲿ�ж�����
	EXTI_InitStructure.EXTI_Line = EXTI_Line11; 					//ѡ��˿�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//�½���Ϊ�ж�����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//ʹ��
	EXTI_Init(&EXTI_InitStructure);		

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource12);	//ѡ���ⲿ�ж�����
	EXTI_InitStructure.EXTI_Line = EXTI_Line12; 					//ѡ��˿�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//�½���Ϊ�ж�����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//ʹ��
	EXTI_Init(&EXTI_InitStructure);	



	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource13);	//ѡ���ⲿ�ж�����
	EXTI_InitStructure.EXTI_Line = EXTI_Line13; 					//ѡ��˿�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 			//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 		//�½���Ϊ�ж�����
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 						//ʹ��
	EXTI_Init(&EXTI_InitStructure);							


}

/*�жϳ���*/
// void EXTI15_10_IRQHandler(void)
// {
// 	if(EXTI_GetITStatus(EXTI_Line12) != RESET) //ȷ���Ƿ������EXTI Line�ж�
// 	{
// 		// LED 	
// 		GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)((1-
// 				 GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0))));
// 		
// 		
// 		EXTI_ClearITPendingBit(EXTI_Line12);     //����жϱ�־λ
// 	}  
// }

