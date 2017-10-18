#include "led.h"

/*使用举例*/
//	led1(ON);
// 	delay_ms(1000);
//  led1(OFF);


void led_PE_Configuration(void)		//控制PE1灯 
{
	GPIO_InitTypeDef GPIO_InitStructure;                     //申明结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE) ;    //使能GPIOE时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;                //选择GPIOC第0管脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;        // 输出速率50MHZ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;        //推挽式输出模式
	GPIO_Init(GPIOC, &GPIO_InitStructure) ;
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;                //选择GPIOC第1管脚
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;        // 输出速率50MHZ
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;        //推挽式输出模式
//	GPIO_Init(GPIOC, &GPIO_InitStructure) ;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;                //选择GPIOC第3管脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;        // 输出速率50MHZ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;        //推挽式输出模式
	GPIO_Init(GPIOC, &GPIO_InitStructure) ;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;                //选择GPIOC第3管脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;        // 输出速率50MHZ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;        //推挽式输出模式
	GPIO_Init(GPIOC, &GPIO_InitStructure) ;   	             //初始化
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);

}


		

 	



