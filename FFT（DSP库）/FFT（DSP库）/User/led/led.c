#include "led.h"

/*ʹ�þ���*/
//	led1(ON);
// 	delay_ms(1000);
//  led1(OFF);


void led_PE_Configuration(void)		//����PE1�� 
{
	GPIO_InitTypeDef GPIO_InitStructure;                     //�����ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE) ;    //ʹ��GPIOEʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;                //ѡ��GPIOC��0�ܽ�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;        // �������50MHZ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;        //����ʽ���ģʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure) ;
	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;                //ѡ��GPIOC��1�ܽ�
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;        // �������50MHZ
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;        //����ʽ���ģʽ
//	GPIO_Init(GPIOC, &GPIO_InitStructure) ;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;                //ѡ��GPIOC��3�ܽ�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;        // �������50MHZ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;        //����ʽ���ģʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure) ;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;                //ѡ��GPIOC��3�ܽ�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;        // �������50MHZ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;        //����ʽ���ģʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure) ;   	             //��ʼ��
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);

}


		

 	



