#ifndef __CAN2_H
#define __CAN2_H	 
#include "common.h"	 
#include "stddef.h"

//////////////////////////////////////////////////////////////////////////////////	 


////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
	

extern void (*CAN2_ReceiveMsgFuncP)();  //Can1收到消息数据时回调函数指针
										 							 				    
u8 CAN2_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化

//Can2接收中断初始化，默认只开启Can1 Rx0中断
void CAN2_INT_Init_ByDefault_RX0();
//Can2接收中断初始化
void CAN2_INT_Init(uint32_t CAN_IT_KINDS, uint8_t CAN_IRQChannel);
//设置Can1消息过滤器
void CAN2_Filter_Init(uint32_t filterNumber, uint32_t slave_id);
//开启中断
void CAN2_INIT_Start(uint32_t CAN_IT_KINDS);
//结束中断
void CAN2_INIT_Stop(uint32_t CAN_IT_KINDS);
//开启中断默认为RX0
void CAN2_INIT_Start_ByDefault_RX0();
//结束中断默认为RX0
void CAN2_INIT_Stop_ByDefault_RX0();

u8 CAN2_Send_Msg(u8* msg,u8 len);						//发送数据

u8 CAN2_Send_Msg1(u32 stdId, u32 extId, u8 ext,u8* msg,u8 len);

/****************************************************************************
* 名		称: u8 CAN1_Receive_Msg(u8 *buf)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
# 入口参数：bufLength:数据缓存区大小;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN2_Receive(u8 *buf, u8 bufLength);


/****************************************************************************
* 名		称: u8 CAN2_receive(u8 *buf, int overtime_ms = 100)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
# 入口参数：bufLength:数据缓存区大小;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN2_Receive_ByTime(u8 *buf, u8 bufLength, int overtime_ms = 100);

/****************************************************************************
* 名		称: u8 CAN1_Receive_Msg(CanRxMsg* msg)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN2_Receive_Msg(CanRxMsg* msg);

/****************************************************************************
* 名		称: u8 CAN2_Receive(CanRxMsg* msg, int overtime_ms = 100)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN2_Receive_Msg_ByTime(CanRxMsg* msg, int overtime_ms = 100);

/****************************************************************************
* 名		称: u8 CAN2_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, int overtime_ms = 100)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN2_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, int overtime_ms = 100);
/****************************************************************************
* 名		称: u8 CAN2_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, u16 index, u8 subIndex, int overtime_ms)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN2_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, u16 index, u8 subIndex, int overtime_ms = 100);


#endif

















