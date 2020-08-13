#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "common.h" 
#include "stdbool.h"
//////////////////////////////////////////////////////////////////////////////////	 

#define USART3_REC_NUM  			128  	//定义最大接收字节数

extern u8 receive_flag;
extern u8 uart3_rec_str[USART3_REC_NUM];    
extern u8 uart3_byte_count;

void uart3_init(u32 bound);
void uart3SendChars(u8 *str, u16 strlen);
void USART3_Receive_Data(u8 *buf, u8 *len);

static void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx,uint32_t chx,uint32_t par,uint32_t mar,uint32_t dir,u16 ndtr);
static void DMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr);
#endif


