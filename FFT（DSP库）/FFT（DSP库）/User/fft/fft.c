#include <math.h>
#include "fft.h"

float *SIN_TAB;//定义正弦表的存放空间
long FFT_N = 8192;//定义采样点大小 
/*******************************************************************
函数原型：struct compx EE(struct compx b1,struct compx b2)
函数功能：对两个复数进行乘法运算
输入参数：两个以联合体定义的复数a,b
输出参数：a和b的乘积，以联合体的形式输出
*******************************************************************/
struct compx EE(struct compx a,struct compx b)
{
 struct compx c;
 c.real=a.real*b.real-a.imag*b.imag;
 c.imag=a.real*b.imag+a.imag*b.real;
 return(c);
}

/******************************************************************
函数原型：void create_sin_tab(float *sin_t，int PointNum)
函数功能：创建一个正弦采样表，采样点数与福利叶变换点数相同
输入参数：*sin_t存放正弦表的数组指针,PointNum采样点数
输出参数：无
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
函数原型：void sin_tab(float pi)
函数功能：采用查表的方法计算一个数的正弦值
输入参数：pi 所要计算正弦值弧度值，范围0--2*PI，不满足时需要转换
输出参数：输入值pi的正弦值
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
函数原型：void cos_tab(float pi)
函数功能：采用查表的方法计算一个数的余弦值
输入参数：pi 所要计算余弦值弧度值，范围0--2*PI，不满足时需要转换
输出参数：输入值pi的余弦值
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
函数原型：void FFT(struct compx *xin)
函数功能：对输入的复数组进行快速傅里叶变换（FFT）
输入参数：*xin复数结构体组的首地址指针，struct型
输出参数：无
*****************************************************************/
void FFT(struct compx *xin,long PointNum)
{
  long f,m,i,k,l,j=0;
  register int nv2,nm1;
  struct compx u,w,t;

	 FFT_N=PointNum;
   nv2=FFT_N/2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
   nm1=FFT_N-1;
   for(i=0;i<nm1;i++)
   {
    if(i<j)                    //如果i<j,即进行变址
     {
      t=xin[j];
      xin[j]=xin[i];
      xin[i]=t;
     }
    k=nv2;                    //求j的下一个倒位序
    while(k<=j)               //如果k<=j,表示j的最高位为1
     {
      j=j-k;                 //把最高位变成0
      k=k/2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
     }
   j=j+k;                   //把0改为1
  }

  {
   int le,lei,ip;                            //FFT运算核，使用蝶形运算完成FFT运算
    f=FFT_N;
   for(l=1;(f=f/2)!=1;l++)                  //计算l的值，即计算蝶形级数
           ;
  for(m=1;m<=l;m++)                         // 控制蝶形结级数
   {                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）N
    le=2<<(m-1);                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点  2^m
    lei=le/2;                               //同一蝶形结中参加运算的两点的距离           2^m-1
    u.real=1.0;                             //u为蝶形结运算系数，初始值为1
    u.imag=0.0;
    w.real=cos(PI/lei);                  //不适用查表法计算sin值和cos值
    w.imag=-sin(PI/lei);
    //w.real=cos_tab(PI/lei);                //w为系数商，即当前系数与前一个系数的商
    //w.imag=-sin_tab(PI/lei);
    for(j=0;j<=lei-1;j++)                  //控制计算不同种蝶形结，即计算系数不同的蝶形结 2^m-1
     {
      for(i=j;i<=FFT_N-1;i=i+le)           //控制同一蝶形结运算，即计算系数相同蝶形结
       {
        ip=i+lei;                          //i，ip分别表示参加蝶形运算的两个节点
        t=EE(xin[ip],u);                   //蝶形运算，详见公式  对两个复数进行乘法运算
        xin[ip].real=xin[i].real-t.real;
        xin[ip].imag=xin[i].imag-t.imag;
        xin[i].real=xin[i].real+t.real;
        xin[i].imag=xin[i].imag+t.imag;
       }
      u=EE(u,w);                          //改变系数，进行下一个蝶形运算
     }
   }
  }
}

/*****************************************************************
函数原型：IFFT(struct compx *xin,long PointNum)
函数功能：对输入的复数组进行快速傅里叶反变换（IFFT）
输入参数：*xin复数结构体组的首地址指针，struct型，
         PointNum：Xin傅里叶反变换的个数

输出参数：无
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
函数原型：void mcztfft(struct compx *x1,int n,int m,int maxnm,float dltomg,
float omg0,float fs)；
函数功能：对输入的复数组进行chirp_Z变换（CZT变换）
输入参数：*x1复数结构体组的首地址指针，struct型，
         n：    输入参与CZT变换的个数  x(i),i=0,..,N-1
         m：    输出的点数             x(i),i=0,..,M-1;
         maxnm：循环卷积的长度     L》N+M-1;
				 dltomg:CZT变换的精度    （HZ）
				 omg0  :起始变换的角度   （HZ）
         fs    ：采样频率        （HZ）
输出参数：无
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
            work1[nfft-i].imag=work2[i].imag;  //work1[i] 后半段 H[n]
            }
        if(n+m!=nfft)
        for(i=m;i<=nfft-n;i++)
           {work1[i].real=0.;
            work1[i].imag=0.;
            }
        FFT(work1,nfft); //快速傅里叶变换  
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
				FFT(x,nfft); //快速傅里叶变换						
/*------------------------ TO COMPUTE g(n)*h(n)---------------*/ 
        for(i=0;i<nfft;i++)
           {z.real=x[i].real;
            z.imag=x[i].imag;
            x[i].real=z.real*work1[i].real-z.imag*work1[i].imag;
            x[i].imag=z.real*work1[i].imag+z.imag*work1[i].real;
            }
				IFFT(x,nfft); //快速傅里叶反变换 
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
函数原型：filter(float *data0,int N)   y(n)=∑h(m)x(n-m);(m: 0～(N-1)).
函数功能：输入的数据通过滤波器
输入参数：data0：输入的数据
          N   ：输入数据的长度

输出参数：无
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
