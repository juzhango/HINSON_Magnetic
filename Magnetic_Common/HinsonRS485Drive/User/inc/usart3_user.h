#ifndef __USART3_USER_H
#define __USART3_USER_H
#include "stdio.h"	
#include "common.h" 
#include "stdbool.h"

//////////////////////////////////////////////////////////////////////////////////	 


#define USART3_REC_NUM  			100  	//�����������ֽ��� 200
extern u8 uart_byte_count;          //uart_byte_countҪС��USART_REC_LEN
extern u8 receive_str[USART3_REC_NUM];  



//test
extern bool flag;






void uart3_init(u32 bound);
void uart3SendChars(u8 *str, u16 strlen);
void usar3_Receive_Data(u8 *buf, u8 *len);
#endif


