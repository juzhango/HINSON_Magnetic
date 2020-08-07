#ifndef _TIMER_H
#define _TIMER_H
#include "common.h"	
/****************************************************************************
* ��    ��: TIM2_Init(u16 auto_data,u16 fractional)
* ��    �ܣ���ʱ��2��ʼ��
* ��ڲ�����auto_data: �Զ���װֵ
*           fractional: ʱ��Ԥ��Ƶ��
* ���ز�������
* ˵    ������ʱ�����ʱ����㷽��:Tout=((auto_data+1)*(fractional+1))/Ft(us)  Ft��ʱ��ʱ��
****************************************************************************/
void TIM2_Init(u16 auto_data,u16 fractional);
u32 millis();//��ȡ��ǰ����ʱ��
//��ʱָ����������Χ�ɳ���999
bool OSTimeDly_MS(uint32_t ms_value);
#endif
