#include "stm32f10x.h"
#include "led.h"
#include "EXTI_KEY.h"
#include "delay.h"
#include "USART1.h"
#include "adc.h"
#include "SDS.h"
#include "lvbo.h"

float cunchu[5000];
u16 num=5000,num1=0;

float vol_data;
float a[N],fa[M],average1 = 0,D_value1;

int main(void)
{
    int i;
	float scap_data[4]; //����ʾ������ʾ
	extern __IO uint16_t ADC_ConvertedValue;    // ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
	float ADC_ConvertedValueLocal; 
	
	delay_init(72);
	//EXTI_PE_Configuration() ;
	led_PE_Configuration();
	 
	USART1_Configuration() ;
	ADC1_Init();
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    led1(ON);
	/**/while (1)//num--
	{        
        for(i=0;i<N;i++)
        {
            ADC_ConvertedValueLocal =(float) ADC_ConvertedValue; // ��ȡת����ADֵ
            a[i] = GYRO_Filter(ADC_ConvertedValueLocal) ; 
        }
        filter(a,fa);

        for(i = 0;i < M;i++)
        {
            average1 = average1 + fa[i] ;
        }				              
        average1 = average1/M;                                    
        average1 = RC_filter(average1);//һ���ͺ��˲�1
        value_RC=average1;
                         
        vol_data = average1/4096*3.3;
        scap_data[0] =  vol_data*1000;		//��λ����ʾ����
        SDS_OutPut_Data(scap_data);	//��λ����ʾ����
//        cunchu[num1++] = vol_data;
//        delay_us(100);
//        printf("\r\n The current AD value = %f V \r\n",vol_data);
	}/**/
//    led1(OFF);
//    for(i=0;i<5000;i++)
//        printf("%f,",cunchu[i]);
//    while(1);
//==================���˲�======================================��
    /*while (1)
	{  
//        ADC_SoftwareStartConvCmd(ADC1, ENABLE);         
        scap_data[0] =  (float) ADC_ConvertedValue;		//��λ����ʾ����
        SDS_OutPut_Data(scap_data);	//��λ����ʾ����           
        vol_data = average1/4096*3.3;
//        printf("\r\n The current AD value = %f V \r\n",vol_data);
	}*/
}
