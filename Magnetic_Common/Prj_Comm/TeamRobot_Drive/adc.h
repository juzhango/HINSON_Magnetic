#ifndef __ADC_H
#define __ADC_H	
#include "common.h" 

/****************************************************************************
* 名    称:ADC3_Collect_Init()
* 功    能:ADC3采集初始化配置 //PF3 4 5 通道9,14,15
* 入口参数：
* 返回参数：
* 说    明:主要为电池电量采集和调速器采集、预留一路ADC
****************************************************************************/
void ADC3_Collect_Init(void);
u16 Get_ADC3Data(u8 ch);
u16 Get_ADC3Data_Average(u8 ch,u8 times);



/****************************************************************************
* 名    称:ADC12_Collect_Init()
* 功    能:ADC12采集初始化配置,对应管脚为PA6  VBAT ADC 对应 ADC12_IN6(与ADC1、ADC2的通道6重合)
* 入口参数：
* 返回参数：
* 说    明:主要为下位机供电输入口的ADC采集，用于检测输入电压值
****************************************************************************/
void ADC12_Collect_Init(void);
u16 Get_ADC12Data(u8 ch);
u16 Get_ADC12Data_Average(u8 ch,u8 times);
#endif 















