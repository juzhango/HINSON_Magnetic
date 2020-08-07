#ifndef PID_H
#define PID_H

#define MaxOutput 100					//最大输出
#define MinOutput  0					//最小输出

#ifdef  PID_C
#define PID_C
#else
#define PID_C extern 
#endif

typedef struct PID						//定义PID结构体
{
	double	SetPoint;	  				//设定目标值
	double	SumError;	  				//总误差

	double	Proportion;	  				//比例常数k(p)
	double	Integral;	  				//积分常数k(i)
	double	Derivative;	 				//微分常数k(d)

	double	LastError;	  				//微分部分的最新偏差e(k)
	double	PrevError;	  				//微分部分的前一次偏差e(k-1)
}PID;

double IncPIDCalc(PID *sptr , double NextPoint);	//增量式PID算法
double PID_Local( PID *sptr , double NextPoint);	//位置式PID算法

#endif

