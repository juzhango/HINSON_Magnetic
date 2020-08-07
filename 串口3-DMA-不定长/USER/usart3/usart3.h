#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "common.h" 

//////////////////////////////////////////////////////////////////////////////////	 

#define USART3_REC_NUM  			128  	//定义最大接收字节数 200
extern u8 receive_flag;
extern u8 uart3_rec_str[USART3_REC_NUM];    
extern u8 uart3_byte_count;

void uart3_init(u32 bound);
void uart3SendChars(u8 *str, u16 strlen);





void USART3_DMA_Config(void);
void MYDMA_Enable(DMA_Stream_TypeDef* DMAy_Streamx);



#endif


