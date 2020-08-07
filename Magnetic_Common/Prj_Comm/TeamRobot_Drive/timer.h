#ifndef _TIMER_H
#define _TIMER_H
#include "common.h"	
/****************************************************************************
* 名    称: TIM2_Init(u16 auto_data,u16 fractional)
* 功    能：定时器2初始化
* 入口参数：auto_data: 自动重装值
*           fractional: 时钟预分频数
* 返回参数：无
* 说    明：定时器溢出时间计算方法:Tout=((auto_data+1)*(fractional+1))/Ft(us)  Ft定时器时钟
****************************************************************************/
void TIM2_Init(u16 auto_data,u16 fractional);
u32 millis();//获取当前毫秒时间
//延时指定毫秒数范围可超过999
bool OSTimeDly_MS(uint32_t ms_value);
#endif
