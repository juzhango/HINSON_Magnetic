#ifndef _CAN1_H
#define _CAN1_H
#include "common.h"


//CAN1接收RX0中断使能
#define CAN1_RX0_INT_ENABLE	1		//0,不使能;1,使能.								    


										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);
uint8_t CAN1_Send_Msg(uint32_t id, uint32_t extid, uint8_t ide, uint8_t rtr, uint8_t* msg, uint8_t len);
uint8_t CAN1_Send_Data_Msg(uint32_t stdId,uint8_t* msg, uint8_t len);
u8 CAN1_Receive_Msg(u8 *buf);			






#endif

