#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "USART1.h"
#include "adc.h"
#include "TIME2.h" 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32_dsp.h"
#include "table_fft.h"

#define PI2 6.28318530717959
#define Fs  40000                  //����Ƶ�� Hz
#define NPT 1024                    //��������

u16 ADC_input1[NPT];
u16 ADC_input2[NPT];

u32 input1[NPT];
u32 input2[NPT];

u32 output1[NPT],output2[NPT],Mag[NPT];

float Fn[NPT/2];     				   //�������Ƶ��
float Mag_max;
u16 ADC_DataNum = 0;
s16 Fn_Num;
u16 ADC_flag = 0;


extern __IO uint16_t ADC_ConvertedValue[];    // ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM	
/**********************ԭ����*********************************************/

/***************�����ֵ*****************/
void PowerMag1(u16 FFT_NPT)  
{

	s16 lx, ly;
	u32 i;
	float mag, x, y;
	
	for (i = 0; i < FFT_NPT/2; i++ )
	{

		lx = (output1[i]<<16)>>16;
		ly = (output1[i]>>16);
		
		 x = FFT_NPT*((float)lx)/32768;
		 y = FFT_NPT*((float)ly)/32768;
		mag = sqrt(x*x+y*y)/FFT_NPT;		
		Mag[i] = (u32)(mag*65536);		
	}
	Mag[0] = Mag[0]/2;	
}


void PowerMag2(u16 FFT_NPT)  
{

	s16 lx, ly;
	u32 i;
	float mag, x, y;
	
	for (i = 0; i < FFT_NPT/2; i++ )
	{

		lx = (output2[i]<<16)>>16;
		ly = (output2[i]>>16);
		
		 x = FFT_NPT*((float)lx)/32768;
		 y = FFT_NPT*((float)ly)/32768;
		mag = sqrt(x*x+y*y)/FFT_NPT;		
		Mag[i] = (u32)(mag*65536);		
	}
	Mag[0] = Mag[0]/2;	
}


/***********ȡ���ֵ************/
void Compare_Max()
{
	u16 i;
	Mag_max = Mag[1]; 
    for(i=1; i < NPT/2; i++)
    {
		if(Mag_max < Mag[i])
		{
			Fn_Num = i;
			Mag_max = Mag[i];
		}
    }

}

/********FFT�任**********/
void DSP1_FFT1024()
{
	u16 i;	
    
	for (i = 0; i <NPT ; i++)
	{
         input1[i] = ADC_input1[i]<<16;
    }
	
	cr4_fft_1024_stm32(output1,input1,NPT);   //FFT�任
	PowerMag1(NPT);

}


void DSP2_FFT1024()
{
	u16 i;	
    
	for (i = 0; i <NPT ; i++)
	{
         input2[i] = ADC_input2[i]<<16;
    }
	
	cr4_fft_1024_stm32(output2,input2,NPT);   //FFT�任
	PowerMag2(NPT);

}
int main(void)
{  
    u16 i ;
	delay_init(72);    
    TIME2_Init();
	ADC1_Init();	 
	USART1_Configuration() ;
    while (1)
	{  
		if(ADC_flag == 1)
		{
			TIM_Cmd(TIM2,DISABLE);
            DMA_Cmd(DMA1_Channel1,DISABLE);
			ADC_flag = 0;
			DSP1_FFT1024();
            for(i = 0; i < NPT/2; i++)
            {
                Fn[i] = ((float)i*Fs/NPT);			
            }

            Compare_Max();
            printf("F1 = %f,\r\n",Fn[Fn_Num]);	
            DSP2_FFT1024();
            for(i = 0; i < NPT/2; i++)
            {
                Fn[i] = ((float)i*Fs/NPT);			
            }

            Compare_Max();
            printf("F2 = %f,\r\n",Fn[Fn_Num]);
            DMA_Cmd(DMA1_Channel1,ENABLE);
            TIM_Cmd(TIM2,ENABLE);    //������ʱ��2
        }
	}
}
/***********************************************************************************/




void DMA1_Channel1_IRQHandler()  
{  
    int  i;
    if(DMA_GetITStatus(DMA_IT_TC))                      //�ж�DMA��������ж�  
    {      
            for(i=0;i<NPT*2;i++)
            {
							 if(i%2==0)
                ADC_input1[i/2] = ADC_ConvertedValue[i];
						  else
								ADC_input2[i/2+1] = ADC_ConvertedValue[i];
            }
            ADC_flag = 1;
    }
    DMA_ClearITPendingBit(DMA_IT_TC);                   //���DMA�жϱ�־λ  
}  
