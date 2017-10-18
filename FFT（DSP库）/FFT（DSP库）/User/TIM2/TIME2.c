#include "TIME2.h"
#include "led.h"

/*************************************************
函数: 
功能: 定时器配置
参数: 无
返回: 无
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
//=====================采样率调节↓=====================================
	TIM2_InitStructure.TIM_Period = 59;        //(799,43)频率2048     //59,29(40K)   //44,19(80K)
	TIM2_InitStructure.TIM_Prescaler = 29;
//==============================================================
	TIM_TimeBaseInit(TIM2, &TIM2_InitStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   //TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //
    TIM_OCInitStructure.TIM_Pulse = 50;     //占空比（大于0就OK）
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;   //TIM输出比较级性低
    TIM_OC2Init(TIM2,&TIM_OCInitStructure);
        
    TIM_InternalClockConfig(TIM2);    //设置TIMx内部时钟
    TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);  //使能或失能TIMx在CCR2上的预装载寄存器
    TIM_UpdateDisableConfig(TIM2,DISABLE);    //使能或失能TIMx更新事件
    
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  //使能或失能指定的TIM中断
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
//=================定时器2中断处理函数================================
        
//====================测试用，可以用示波器测量定时频率↓==================         
//          if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3))
//              led4(ON);
//          else
//              led4(OFF);
//===============================================================                
		TIM_ClearFlag(TIM2, TIM_IT_Update); //清除溢出中断标志
	}
}
