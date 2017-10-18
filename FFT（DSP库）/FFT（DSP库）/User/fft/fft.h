#ifndef __FFT_H_
#define __FFT_H_
                                                 //定义福利叶变换的点数
#define PI 3.1415926535897932384626433832795028841971               //定义圆周率值

struct compx{float real,imag;};                                    //定义一个复数结构

extern void create_sin_tab(float *sin_t,int PointNum);
extern void FFT(struct compx *xin,long PointNum);
extern void IFFT(struct compx *xin,long PointNum);
extern void mcztfft(struct compx *x1,int n,int m,int maxnm,float dltomg,float omg0,float fs);

#endif // FFT_H
