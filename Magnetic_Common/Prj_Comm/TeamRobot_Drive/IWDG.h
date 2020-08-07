#ifndef _IWDG_H_
#define _IWDG_H_
#include "common.h"	 

/**
 * 初始化独立看门狗
 * prer:分频数:0~7(只有低 3 位有效!)
 * 分频因子=4*2^prer.但最大值只能是 256!
 * rlr:重装载寄存器值:低 11 位有效.
 * 时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
 *IWDG_Init(4,625);//初始化独立看门狗，分频数为64，重装载值为625，溢出时间计算为：64*625/40=1000ms=1s
 */
void IWDG_Init(u8 prer,u16 rlr);

/**
 * 喂独立看门狗
 */
void IWDG_Feed(void);

#endif