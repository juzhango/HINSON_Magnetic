#ifndef _IWDG_H_
#define _IWDG_H_
#include "common.h"	 

/**
 * ��ʼ���������Ź�
 * prer:��Ƶ��:0~7(ֻ�е� 3 λ��Ч!)
 * ��Ƶ����=4*2^prer.�����ֵֻ���� 256!
 * rlr:��װ�ؼĴ���ֵ:�� 11 λ��Ч.
 * ʱ�����(���):Tout=((4*2^prer)*rlr)/40 (ms).
 *IWDG_Init(4,625);//��ʼ���������Ź�����Ƶ��Ϊ64����װ��ֵΪ625�����ʱ�����Ϊ��64*625/40=1000ms=1s
 */
void IWDG_Init(u8 prer,u16 rlr);

/**
 * ι�������Ź�
 */
void IWDG_Feed(void);

#endif