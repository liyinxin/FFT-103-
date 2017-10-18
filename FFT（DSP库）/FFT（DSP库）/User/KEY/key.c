#include "key.h"

/// ²»¾«È·µÄÑÓÊ±
static void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

void Key_PB12_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*¿ªÆô°´¼ü¶Ë¿Ú©  µÄÊ±ÖÓ*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief   ¼ì²âÊÇ·ñÓÐ°´¼ü°´ÏÂ
  * @param   ¾ßÌåµÄ¶Ë¿ÚºÍ¶Ë¿ÚÎ»
  *		@arg GPIOx: x¿ÉÒÔÊÇ£¨A...G£© 
  *		@arg GPIO_PIN ¿ÉÒÔÊÇGPIO_PIN_x£¨x¿ÉÒÔÊÇ1...16£©
  * @retval  °´¼üµÄ×´Ì¬
  *		@arg KEY_ON:°´¼ü°´ÏÂ
  *		@arg KEY_OFF:°´¼üÃ»°´ÏÂ
  */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
	/*¼ì²âÊÇ·ñÓÐ°´¼ü°´ÏÂ */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	{	   
		/*ÑÓÊ±Ïû¶¶*/
		Delay(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
		{	 
			/*µÈ´ý°´¼üÊÍ·Å */
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
// 						/*LEDÈ¡·´*/
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


