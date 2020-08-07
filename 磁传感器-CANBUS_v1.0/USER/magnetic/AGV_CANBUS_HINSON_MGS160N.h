/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  */
#ifndef _AGV_CANBUS_HINSON_MGS160N_H
#define _AGV_CANBUS_HINSON_MGS160N_H
#include "common.h"
#include "can1.h"


#define MGS160N_ADDR   							0x78



extern bool MGS160N_Device_Running;//�豸״̬
extern uint8_t MGS160N_Induction_Status;//��Ӧ״̬ 4:��  2:��  1:��  0:��
extern int8_t MGS160N_Centre_Diff_MM;//��ǰѡ�����ƫ�ƾ���(-70~70)


void MGS160N_Init(void);
void Can1GetReviveData(void);
void DispatchCan1ReceiveMsg(CanRxMsg *msg);
void Dispatch_MGS160N_Data(CanRxMsg msg);
void MGS160N_ReqCentreDiff(void);
void MGS160N_ReqLeftDiff(void);
void MGS160N_ReqRightDiff(void);


#endif




