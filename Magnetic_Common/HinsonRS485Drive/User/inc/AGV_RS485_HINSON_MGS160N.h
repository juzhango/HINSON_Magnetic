/**
  ******************************************************************************
  * @file    AGV_RS485_HINSON_MGS160N.h
  * @author  
  * @version 1.0
  * @date    2020-8-3
  * @brief   兴颂磁传感器驱动 HINSON CNS-MGS-160N
             0.设备地址，
             1.初始化选择类型 供外部文件
             2.实时数据 供外部文件
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

//传感器实时数据
extern bool MGS160N_Device_Running;//设备状态
extern uint8_t MGS160N_Induction_Status;//感应状态 4:右  2:中  1:左  0:无
extern int8_t MGS160N_Choose_Diff_MM;//当前选择磁条偏移距离(-70~70)
extern int16_t MGS160N_Choose_Strength;//当前选择磁条强度
extern uint8_t MGS160N_Choose_Range;//当前磁条范围(1~16)

extern int8_t MGS160N_Left_Diff_MM;//左磁条偏移距离(-70~70)
extern int8_t MGS160N_Centre_Diff_MM;//中磁条偏移距离(-70~70)
extern int8_t MGS160N_Right_Diff_MM;//右磁条偏移距离(-70~70)

extern int16_t MGS160N_Left_Strength;//左磁条强度
extern int16_t MGS160N_Centre_Strength;//中磁条强度
extern int16_t MGS160N_Right_Strength;//右磁条强度

//设备485地址
#define DEVICE_ADDR   					0x78

//功能码
#define MGS160N_FunId_rInputReg				0x04			//读输入寄存器		获取数据
#define MGS160N_FunId_wKeenReg				0x06			//写保持寄存器		初始化配置

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





