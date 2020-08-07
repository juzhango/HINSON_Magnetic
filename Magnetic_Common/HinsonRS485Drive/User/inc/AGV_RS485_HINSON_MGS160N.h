/**
  ******************************************************************************
  * @file    AGV_RS485_HINSON_MGS160N.h
  * @author  
  * @version 1.0
  * @date    2020-8-3
  * @brief   ���̴Ŵ��������� HINSON CNS-MGS-160N
             0.�豸��ַ��
             1.��ʼ��ѡ������ ���ⲿ�ļ�
             2.ʵʱ���� ���ⲿ�ļ�
  ******************************************************************************
  */


#ifndef _HINSON_CNS_MGS_160N_H
#define _HINSON_CNS_MGS_160N_H
#include "common.h"
#include "usart3.h"
#include "stdbool.h"
#include "stdint.h"
#include "rs485_user.h"	
#include "crc16.h"


enum MGS160N_Init_Type
{
	MGS160N_CHOOSE_CENTRE = 0,
	MGS160N_CHOOSE_LEFT,
	MGS160N_CHOOSE_RIGHT,
};

//������ʵʱ����
extern bool MGS160N_Device_Running;//�豸״̬
extern uint8_t MGS160N_Induction_Status;//��Ӧ״̬ 4:��  2:��  1:��  0:��
extern int8_t MGS160N_Choose_Diff_MM;//��ǰѡ�����ƫ�ƾ���(-70~70)
extern int16_t MGS160N_Choose_Strength;//��ǰѡ�����ǿ��
extern uint8_t MGS160N_Choose_Range;//��ǰ������Χ(1~16)

extern int8_t MGS160N_Left_Diff_MM;//�����ƫ�ƾ���(-70~70)
extern int8_t MGS160N_Centre_Diff_MM;//�д���ƫ�ƾ���(-70~70)
extern int8_t MGS160N_Right_Diff_MM;//�Ҵ���ƫ�ƾ���(-70~70)

extern int16_t MGS160N_Left_Strength;//�����ǿ��
extern int16_t MGS160N_Centre_Strength;//�д���ǿ��
extern int16_t MGS160N_Right_Strength;//�Ҵ���ǿ��

//�豸485��ַ
#define DEVICE_ADDR   					0x78

//������
#define MGS160N_FunId_rInputReg				0x04			//������Ĵ���		��ȡ����
#define MGS160N_FunId_wKeenReg				0x06			//д���ּĴ���		��ʼ������

void debug_print(void);

void MGS160N_Choose_Init(uint8_t type);
bool MGS160N_Check_Buf(u8 * getbuf, u8 getbuf_count);
void MGS160N_Parse_Data(u8 *get_buf, u8 getbuf_count,u8 parse_type);

void AGV_RS485_MGS160N_Loop(void);
void getDeviceStatus(void);
void getInductionStatus(void);
void getChooseRange(void);
void getChooseDiff(void);
void getChooseStrength(void);
void getLeftDiff(void);
void getCentreDiff(void);
void getRightDiff(void);
void getLeftStrength(void);
void getCentreStrength(void);
void getRightStrength(void);


#endif





