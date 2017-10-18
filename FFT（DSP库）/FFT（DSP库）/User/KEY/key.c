#include "key.h"

/// ����ȷ����ʱ
static void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

void Key_PB12_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ک  ��ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief   ����Ƿ��а�������
  * @param   ����Ķ˿ںͶ˿�λ
  *		@arg GPIOx: x�����ǣ�A...G�� 
  *		@arg GPIO_PIN ������GPIO_PIN_x��x������1...16��
  * @retval  ������״̬
  *		@arg KEY_ON:��������
  *		@arg KEY_OFF:����û����
  */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	{	   
		/*��ʱ����*/
		Delay(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
		{	 
			/*�ȴ������ͷ� */
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			return 	KEY_ON;	 
		}
		else
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}



// #include "stm32f10x.h"
// #include "led.h"
// #include "key.h"

// int main(void)
// {
// 	led_PC0_Configuration() ;
// 	Key_PB12_Configuration() ;
// 	GPIO_SetBits(GPIOC,GPIO_Pin_0) ;
// 	
// 	while(1)
// 		{	
// 			 if( Key_Scan(GPIOB,GPIO_Pin_12) == KEY_ON  )
// 			 {
// 						/*LEDȡ��*/
//  				  GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)((1-
// 				 GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0))));
// // 				 if(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_0)== 1)
// // 					GPIO_ResetBits(GPIOC,GPIO_Pin_0) ;
// // 				 else
// // 					 GPIO_SetBits(GPIOC,GPIO_Pin_0) ;
// // 				 
// 	
// 			 }
// 		}
// 		
// }


