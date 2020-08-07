#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"	
#include "common.h" 
#include "stdbool.h"

//////////////////////////////////////////////////////////////////////////////////	 

#define USE_UART3_IDLE  					0

#define USART3_REC_NUM  			100  	//定义最大接收字节数 200
extern u8 uart_byte_count;          //uart_byte_count要小于USART_REC_LEN
extern u8 receive_str[USART3_REC_NUM];  


//test
extern bool flag;




void uart3_init(u32 bound);
void uart3SendChars(u8 *str, u16 strlen);
void usar3_Receive_Data(u8 *buf, u8 *len);
#endif


