#include "TIME2.h"
#include "led.h"

/*************************************************
����: 
����: ��ʱ������
����: ��
����: ��
**************************************************/
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM2_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    
	TIM_DeInit(TIM2);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	TIM2_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM2_InitStructure.TIM_RepetitionCounter = 0;
	TIM2_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//=====================�����ʵ��ڡ�=====================================
	TIM2_InitStructure.TIM_Period = 59;        //(799,43)Ƶ��2048     //59,29(40K)   //44,19(80K)
	TIM2_InitStructure.TIM_Prescaler = 29;
//==============================================================
	TIM_TimeBaseInit(TIM2, &TIM2_InitStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   //TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //
    TIM_OCInitStructure.TIM_Pulse = 50;     //ռ�ձȣ�����0��OK��
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;   //TIM����Ƚϼ��Ե�
    TIM_OC2Init(TIM2,&TIM_OCInitStructure);
        
    TIM_InternalClockConfig(TIM2);    //����TIMx�ڲ�ʱ��
    TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);  //ʹ�ܻ�ʧ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
    TIM_UpdateDisableConfig(TIM2,DISABLE);    //ʹ�ܻ�ʧ��TIMx�����¼�
    
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //ʹ�ܻ�ʧ��ָ����TIM�ж�
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_NVIC_Configuration(void)
{
	
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}

void TIME2_Init()
{
    TIM2_NVIC_Configuration();
    TIM2_Configuration();
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)==SET)
	{
//=================��ʱ��2�жϴ�����================================
        
//====================�����ã�������ʾ����������ʱƵ�ʡ�==================         
//          if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))
//              led4(ON);
//          else
//              led4(OFF);
//===============================================================                
		TIM_ClearFlag(TIM2, TIM_IT_Update); //�������жϱ�־
	}
}
