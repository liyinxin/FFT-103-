/**********************************************
*
*滤波程序
*
***********************************************/
//ADC滤波函数
#include "lvbo.h"

void filter_t(float num[N],float a[M])
{
	float temp;
	int i,j,k;
	for(j = 0;j < N-1;j++)
	{
		for(i = j+1;i<N;i++)
		{
			if(num[j] > num[i])
			{
				temp = num[j];
				num[j] = num[i];
				num[i] = temp;
			}
		}
	}
	for(i = (N-M)/2,k = 0;i<(N+M)/2;i++)
	{
		a[k] = num[i];
		k++;
	
	}
}

float value_RC=0;

float RC_filter(float in)
{
	float new_value;
	new_value = in;
	return 1.0*(1.0*(100 - RC)*value_RC + 1.0*RC*new_value)/100.0;	
}


float GYRO_Filter(float ADValue)
{
      #define GYRO_Filter_N 5               //我个人觉得这个队列不能太长
      u8   count = 0   ;
      float   sum  = 0   ;
      static float GYRO_buf[GYRO_Filter_N] = {0 ,0,0};

      GYRO_buf[(GYRO_Filter_N - 1)] = ADValue;

      for ( count = 0;count<GYRO_Filter_N;count++)
      {

          sum += GYRO_buf[count];

          if( count < (GYRO_Filter_N - 1))
          {
              GYRO_buf[count] = GYRO_buf[ count + 1 ];
          }
      }
      return (sum/GYRO_Filter_N);
}
