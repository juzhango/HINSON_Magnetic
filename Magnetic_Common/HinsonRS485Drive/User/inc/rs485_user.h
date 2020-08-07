#ifndef __RS485_USER_H
#define __RS485_USER_H			 
#include "common.h"	 	
#include "stdbool.h"
#include "usart3_user.h"	

#define USE_UART2_IDLE 1

//模式控制
#define RS485_TX_EN		PGout(6)	    //485模式控制.0,接收;1,发送.


														 
void RS485_Init(u32 bound);
void RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf, u8 *len);
#endif	   
















