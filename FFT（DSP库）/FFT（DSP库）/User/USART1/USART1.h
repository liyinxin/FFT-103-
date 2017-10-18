#ifndef __USART1_H
#define __USART1_H

#include <stdio.h>
#include "stm32f10x.h"

void USART1_Configuration(void);  

extern void Uart1_PutChar(u8 ch);

#endif
