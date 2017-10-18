#ifndef __led_H
#define	__led_H

#include "stm32f10x.h"

#define ON  0
#define OFF 1

void led_PE_Configuration(void);

/* 带参宏，可以像内联函数一样使用 */
#define led1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_2)

//#define led2(a)	if (a)	\
//					GPIO_SetBits(GPIOC,GPIO_Pin_1);\
//					else		\
//					GPIO_ResetBits(GPIOC,GPIO_Pin_1)

#define led3(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_4)
	
#define led4(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_3);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_3)					
		

#endif /* __EXTI_H */
