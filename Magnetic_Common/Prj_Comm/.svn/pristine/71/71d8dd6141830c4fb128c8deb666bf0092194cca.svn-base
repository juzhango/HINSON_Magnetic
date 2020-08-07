#ifndef __CAN1_H
#define __CAN1_H	 
#include "common.h"	 
#include "stddef.h"

//////////////////////////////////////////////////////////////////////////////////	 


	

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

extern void (*CAN1_ReceiveMsgFuncP)();  //Can1收到消息数据时回调函数指针
										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN初始化
//Can1接收中断初始化，默认只开启Can1 Rx0中断
void CAN1_INT_Init_ByDefault_RX0();
//Can1接收中断初始化
void CAN1_INT_Init(uint32_t CAN_IT_KINDS, uint8_t CAN_IRQChannel);
//设置Can1消息过滤器
void CAN1_Filter_Init(uint32_t filterNumber, uint32_t slave_id);
//开启中断
void CAN1_INIT_Start(uint32_t CAN_IT_KINDS);
//结束中断
void CAN1_INIT_Stop(uint32_t CAN_IT_KINDS);
//开启中断默认为RX0
void CAN1_INIT_Start_ByDefault_RX0();
//结束中断默认为RX0
void CAN1_INIT_Stop_ByDefault_RX0();

 
/****************************************************************************
* 名		称: void initCanMessage(CanRxMsg* msg)
* 功		能：初始化接收消息体
* 入口参数：msg:数据指针,最大为8个字节.
* 说		明：因实际测试存在接收标准帧消息时，不会赋值扩展帧；接收扩展帧消息不会赋值标准帧数据的情况，所以结束的数据需要先初始化
****************************************************************************/
void initCanMessage(CanRxMsg* msg);
 
u8 CAN1_Send_Msg(u8* msg,u8 len);						//发送数据
u8 CAN1_Send_Msg1(u32 stdId, u32 extId, u8 ext,u8* msg,u8 len);
/****************************************************************************
* 名		称: u8 CAN1_Receive_Msg(u8 *buf)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
# 入口参数：bufLength:数据缓存区大小;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN1_Receive(u8 *buf, u8 bufLength);


/****************************************************************************
* 名		称: u8u8 CAN1_Receive_ByTime(u8 *buf, u8 bufLength, int overtime_ms = 100)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
# 入口参数：bufLength:数据缓存区大小;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN1_Receive_ByTime(u8 *buf, u8 bufLength, int overtime_ms = 100);

/****************************************************************************
* 名		称: u8 CAN1_Receive_Msg(CanRxMsg* msg)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN1_Receive_Msg(CanRxMsg* msg);

/****************************************************************************
* 名		称: u8 CAN1_Receive(CanRxMsg* msg, int overtime_ms = 100)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN1_Receive_Msg_ByTime(CanRxMsg* msg, int overtime_ms = 100);


/****************************************************************************
* 名		称: u8 CAN1_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, int overtime_ms = 100)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN1_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, int overtime_ms = 100);

/****************************************************************************
* 名		称: u8 CAN1_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, u16 index, u8 subIndex, int overtime_ms)
* 功		能：can口接收数据查询
* 入口参数：buf:数据缓存区;
* 返回参数：0,无数据被收到;
						其他,接收的数据长度;
* 说		明：
****************************************************************************/
u8 CAN1_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, u16 index, u8 subIndex, int overtime_ms = 100);


#endif

















