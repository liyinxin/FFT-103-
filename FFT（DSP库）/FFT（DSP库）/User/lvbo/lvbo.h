#ifndef __LVBO_H_
#define __LVBO_H_


#include "stm32f10x.h"


#define RC 91
extern float value_RC;


#define N 100
#define M 20


float GYRO_Filter(float ADValue);
float RC_filter(float in);
void filter_t(float num[N],float a[M]);


#endif
