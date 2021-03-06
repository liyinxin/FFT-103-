#include "key.h"

/// 不精确的延时
static void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

void Key_PB12_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口�  的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief   检测是否有按键按下
  * @param   具体的端口和端口位
  *		@arg GPIOx: x可以是（A...G） 
  *		@arg GPIO_PIN 可以是GPIO_PIN_x（x可以是1...16）
  * @retval  按键的状态
  *		@arg KEY_ON:按键按下
  *		@arg KEY_OFF:按键没按下
  */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	{	   
		/*延时消抖*/
		Delay(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
		{	 
			/*等待按键释放 */
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
// 						/*LED取反*/
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


