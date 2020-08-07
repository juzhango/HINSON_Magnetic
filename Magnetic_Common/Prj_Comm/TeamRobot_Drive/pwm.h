#ifndef _PWM_H
#define _PWM_H
#include "common.h"
 	

/****************************************************************************
* 名    称: void TIM4_PWM_Init(u32 auto_data,u32 fractional)
* 功    能：PWM输出初始化
* 入口参数：auto_data: 自动重装值
*           fractional: 时钟预分频数
* 返回参数：无
* 说    明：设置PD12(TIM4_CH1)输出PWM波      
****************************************************************************/
void TIM4_PWM_Init(u32 auto_data,u32 fractional);

//TIM_SetCompare1(TIM4,pwmzkb);	
//TIM_SetCompare2(TIM4,pwmzkb);	
//TIM_SetCompare3(TIM4,pwmzkb);	
//TIM_SetCompare4(TIM4,pwmzkb);	
#endif
