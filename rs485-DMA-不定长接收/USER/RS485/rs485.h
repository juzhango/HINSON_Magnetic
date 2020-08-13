#ifndef __RS485_H
#define __RS485_H			 
#include "common.h"	 								  
#include "usart3.h"	
#define USE_RS485_DMA        	1
#define RS485_REC_NUM 				128

//模式控制
#define RS485_TX_EN		PGout(6)	    //485模式控制.0,接收;1,发送.


														 
void RS485_Init(u32 bound);
void RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf, u8 *len);



static void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx,uint32_t chx,uint32_t par,uint32_t mar,uint32_t dir,u16 ndtr);
static void DMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr);





#endif	   
















