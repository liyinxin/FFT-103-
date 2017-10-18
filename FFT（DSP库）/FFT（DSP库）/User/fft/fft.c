#include <math.h>
#include "fft.h"

float *SIN_TAB;//�������ұ�Ĵ�ſռ�
long FFT_N = 8192;//����������С 
/*******************************************************************
����ԭ�ͣ�struct compx EE(struct compx b1,struct compx b2)
�������ܣ��������������г˷�����
��������������������嶨��ĸ���a,b
���������a��b�ĳ˻��������������ʽ���
*******************************************************************/
struct compx EE(struct compx a,struct compx b)
{
 struct compx c;
 c.real=a.real*b.real-a.imag*b.imag;
 c.imag=a.real*b.imag+a.imag*b.real;
 return(c);
}

/******************************************************************
����ԭ�ͣ�void create_sin_tab(float *sin_t��int PointNum)
�������ܣ�����һ�����Ҳ��������������븣��Ҷ�任������ͬ
���������*sin_t������ұ������ָ��,PointNum��������
�����������
******************************************************************/
void create_sin_tab(float *sin_t,int PointNum)
{
  int i;
  SIN_TAB=sin_t;
  FFT_N=PointNum;
  for(i=0;i<=FFT_N/4;i++)
	SIN_TAB[i]=sin(2*PI*i/FFT_N);
}
/******************************************************************
����ԭ�ͣ�void sin_tab(float pi)
�������ܣ����ò��ķ�������һ����������ֵ
���������pi ��Ҫ��������ֵ����ֵ����Χ0--2*PI��������ʱ��Ҫת��
�������������ֵpi������ֵ
******************************************************************/
float sin_tab(float pi)
{
  int n=0;
  float a=0;
   n=(int)(pi*FFT_N/2/PI);

  if(n>=0&&n<=FFT_N/4)
    a=SIN_TAB[n];
  else if(n>FFT_N/4&&n<FFT_N/2)
    {
     n-=FFT_N/4;
     a=SIN_TAB[FFT_N/4-n];
    }
  else if(n>=FFT_N/2&&n<3*FFT_N/4)
    {
     n-=FFT_N/2;
     a=-SIN_TAB[n];
   }
  else if(n>=3*FFT_N/4&&n<3*FFT_N)
    {
     n=FFT_N-n;
     a=-SIN_TAB[n];
   }

  return a;
}
/******************************************************************
����ԭ�ͣ�void cos_tab(float pi)
�������ܣ����ò��ķ�������һ����������ֵ
���������pi ��Ҫ��������ֵ����ֵ����Χ0--2*PI��������ʱ��Ҫת��
�������������ֵpi������ֵ
******************************************************************/
float cos_tab(float pi)
{
   float a,pi2;
   pi2=pi+PI/2;
   if(pi2>2*PI)
     pi2-=2*PI;
   a=sin_tab(pi2);
   return a;
}
/*****************************************************************
����ԭ�ͣ�void FFT(struct compx *xin)
�������ܣ�������ĸ�������п��ٸ���Ҷ�任��FFT��
���������*xin�����ṹ������׵�ַָ�룬struct��
�����������
*****************************************************************/
void FFT(struct compx *xin,long PointNum)
{
  long f,m,i,k,l,j=0;
  register int nv2,nm1;
  struct compx u,w,t;

	 FFT_N=PointNum;
   nv2=FFT_N/2;                  //��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
   nm1=FFT_N-1;
   for(i=0;i<nm1;i++)
   {
    if(i<j)                    //���i<j,�����б�ַ
     {
      t=xin[j];
      xin[j]=xin[i];
      xin[i]=t;
     }
    k=nv2;                    //��j����һ����λ��
    while(k<=j)               //���k<=j,��ʾj�����λΪ1
     {
      j=j-k;                 //�����λ���0
      k=k/2;                 //k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
     }
   j=j+k;                   //��0��Ϊ1
  }

  {
   int le,lei,ip;                            //FFT����ˣ�ʹ�õ����������FFT����
    f=FFT_N;
   for(l=1;(f=f/2)!=1;l++)                  //����l��ֵ����������μ���
           ;
  for(m=1;m<=l;m++)                         // ���Ƶ��νἶ��
   {                                        //m��ʾ��m�����Σ�lΪ���μ�����l=log��2��N
    le=2<<(m-1);                            //le���ν���룬����m�����εĵ��ν����le��  2^m
    lei=le/2;                               //ͬһ���ν��вμ����������ľ���           2^m-1
    u.real=1.0;                             //uΪ���ν�����ϵ������ʼֵΪ1
    u.imag=0.0;
    w.real=cos(PI/lei);                  //�����ò������sinֵ��cosֵ
    w.imag=-sin(PI/lei);
    //w.real=cos_tab(PI/lei);                //wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
    //w.imag=-sin_tab(PI/lei);
    for(j=0;j<=lei-1;j++)                  //���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν� 2^m-1
     {
      for(i=j;i<=FFT_N-1;i=i+le)           //����ͬһ���ν����㣬������ϵ����ͬ���ν�
       {
        ip=i+lei;                          //i��ip�ֱ��ʾ�μӵ�������������ڵ�
        t=EE(xin[ip],u);                   //�������㣬�����ʽ  �������������г˷�����
        xin[ip].real=xin[i].real-t.real;
        xin[ip].imag=xin[i].imag-t.imag;
        xin[i].real=xin[i].real+t.real;
        xin[i].imag=xin[i].imag+t.imag;
       }
      u=EE(u,w);                          //�ı�ϵ����������һ����������
     }
   }
  }
}

/*****************************************************************
����ԭ�ͣ�IFFT(struct compx *xin,long PointNum)
�������ܣ�������ĸ�������п��ٸ���Ҷ���任��IFFT��
���������*xin�����ṹ������׵�ַָ�룬struct�ͣ�
         PointNum��Xin����Ҷ���任�ĸ���

�����������
*****************************************************************/
void IFFT(struct compx *xin,long PointNum)
{ 
	int i;
	FFT_N=PointNum;
  for(i=0;i<FFT_N;i++)
 	  xin[i].imag=(-1)*xin[i].imag;
	FFT(xin,FFT_N);
  for(i=0;i<FFT_N;i++)
   {
	    xin[i].imag=(-1)*xin[i].imag/FFT_N ; 
      xin[i].real=xin[i].real/FFT_N;
   }
}


/*****************************************************************
����ԭ�ͣ�void mcztfft(struct compx *x1,int n,int m,int maxnm,float dltomg,
float omg0,float fs)��
�������ܣ�������ĸ��������chirp_Z�任��CZT�任��
���������*x1�����ṹ������׵�ַָ�룬struct�ͣ�
         n��    �������CZT�任�ĸ���  x(i),i=0,..,N-1
         m��    ����ĵ���             x(i),i=0,..,M-1;
         maxnm��ѭ������ĳ���     L��N+M-1;
				 dltomg:CZT�任�ľ���    ��HZ��
				 omg0  :��ʼ�任�ĽǶ�   ��HZ��
         fs    ������Ƶ��        ��HZ��
�����������
*****************************************************************/
void mcztfft(struct compx *x1,int n,int m,int maxnm,float dltomg,
float omg0,float fs)
{
/*----------------------------------------------------------------------
 Routine CZTFFT:To perform a CHIRP-Z Transform.
 input parameters:
   N     : numbers of input signal to be transformed by CZT,
           x(i),i=0,..,N-1;
   M     : numbers of output signal transformed by CZT,
           x(i),i=0,..,M-1;
 maxnm (L): the dimension of x must be MAXNM,otherwise the result
           will be error!
   dltomg: increasing angle of frequncy domain, in Hz;
   omg0  : start angle of CZT, in Hz;
   fs    : sampling frequency in Hz.

 output parameters:
   x    : MAXNM dimensioned complex array. the CZT result is stored
           in x(0) to x(M-1).
   Note  : In this program the largest length to do CZT MAXCZT=1024,
           if you want to increase the length to do CZT please change
           MAXCZT and  the dimension of X,WORK1 and WORK2 .
                                       in Chapter 5
--------------------------------------------------------------------*/
        struct compx a,z;
        struct compx x[1024],work1[1024],work2[1024];
        float pi,ph,alpha,ang;
        int nfft,i,ntest;
//        m1=max(n,m);
//        if(maxnm<m1)
//           return;
/*-------------------------------- TO COMPUTE W**(-N**2/2)-----*///H[n] = work1[i]
        nfft=n+m;
        for(i=0;i<=10;i++)
           {ntest=pow(2,i);
            if(ntest>=nfft)
               break;
               }
        nfft=ntest;
  
        pi=4.*atan(1.);
        ph=-2.*pi*dltomg/fs;
        for(i=0;i<maxnm;i++)
           {alpha=-ph*i*i/2.;
            work1[i].real=cos(alpha);
            work1[i].imag=sin(alpha);       //work1[i] = w ^(-n^2/2)
            work2[i].real=work1[i].real;
            work2[i].imag=work1[i].imag;    //work2[i] = w ^(-n^2/2)
            }
        for(i=1;i<n;i++)
           {work1[nfft-i].real=work2[i].real;
            work1[nfft-i].imag=work2[i].imag;  //work1[i] ���� H[n]
            }
        if(n+m!=nfft)
        for(i=m;i<=nfft-n;i++)
           {work1[i].real=0.;
            work1[i].imag=0.;
            }
        FFT(work1,nfft); //���ٸ���Ҷ�任  
/*------------------------ TO COMPUTE A**(-N)*W**(N**2/2)-----*///g[n] =x[i]
        ang=-omg0*pi*2./fs;
        for(i=0;i<n;i++)
           {a.real=cos(ang*i);
            a.imag=sin(ang*i);               //A**(-N)
            z.real=work2[i].real*a.real+work2[i].imag*a.imag;
            z.imag=work2[i].real*a.imag-work2[i].imag*a.real;
            x[i].real=z.real*x1[i].real-z.imag*x1[i].imag;
            x[i].imag=z.real*x1[i].imag+z.imag*x1[i].real;
            } 
        for(i=n;i<nfft;i++)
           {x[i].real=0.;
            x[i].imag=0.;
            }  
				FFT(x,nfft); //���ٸ���Ҷ�任						
/*------------------------ TO COMPUTE g(n)*h(n)---------------*/ 
        for(i=0;i<nfft;i++)
           {z.real=x[i].real;
            z.imag=x[i].imag;
            x[i].real=z.real*work1[i].real-z.imag*work1[i].imag;
            x[i].imag=z.real*work1[i].imag+z.imag*work1[i].real;
            }
				IFFT(x,nfft); //���ٸ���Ҷ���任 
/*-------------------------- TO MULTIPLY BY W**(K**2/2)--------*/
        for(i=0;i<m;i++)
           {z.real=x[i].real;
            z.imag=x[i].imag;
            a.real=work2[i].real;
            a.imag=-work2[i].imag;
            x1[i].real=z.real*a.real-z.imag*a.imag;
            x1[i].imag=z.imag*a.real+z.real*a.imag;
            }
        return;
         }


/*****************************************************************
����ԭ�ͣ�filter(float *data0,int N)   y(n)=��h(m)x(n-m);(m: 0��(N-1)).
�������ܣ����������ͨ���˲���
���������data0�����������
          N   ���������ݵĳ���

�����������
*****************************************************************/				 
void filter(float *data0,int N)
{
	int i,j;
	long sum;
	float x1[4096];
	float h[19]={ -0.0027, -0.0025, 0.0050, 0.0157, -0.0000, -0.0471, -0.0482, 0.0838, 0.2953, 0.4013,
				0.2953, 0.0838, -0.0482, -0.0471, -0.0000,0.0157, 0.0050, -0.0025, -0.0027};
	for(i=0;i<N;i++)
	x1[i] = data0[i];
	for(i=0;i<N;i++)
	{
		sum=0.0;
		for(j=0;j<19;j++)
		{
			if(i >= j)
			sum+=h[j]*x1[i-j];
			else
			;
		}
		data0[i]=(float)sum;
	}
	for(i=0;i<(N-20);i++)
	{
		data0[i] = data0[i+20];
	}
}
