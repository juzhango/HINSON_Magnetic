#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "common.h"  

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

#define USART1_REC_NUM  			100  	//定义最大接收字节数 200
#define USART2_REC_NUM  			200  	//定义最大接收字节数 123
#define RS485_REC_NUM  			128  	//定义最大接收字节数 123
#define RS485_TX_EN		PGout(6)	    //485模式控制.0,接收;1,发送.
#define UART4_REC_NUM  			200  	//定义最大接收字节数 123
#define UART5_REC_NUM  			200  	//定义最大接收字节数 123
#define USART6_REC_NUM  			200  	//定义最大接收字节数 123
extern u8 uart1_byte_count;          //uart_byte_count要小于USART_REC_LEN
extern u8 uart1_receive_str[USART1_REC_NUM];  
extern u8 RS485_receive_str[RS485_REC_NUM]; 	//接收缓冲,最大128个字节
extern u8 uart2_byte_count;   			  //接收到的数据长度
extern u8 RS485_byte_count;   			  //接收到的数据长度
/**************************************************************
*  MAX485芯片：TX=PA2,RX=PA3,模式控制=PG6(0,接收;1,发送)
***************************************************************/
extern u8 UART4_receive_str[UART4_REC_NUM]; 	//接收缓冲,最大128个字节
extern u8 uart4_byte_count;   			  //接收到的数据长度
extern u8 uart5_receive_str[UART5_REC_NUM];  
extern u8 uart5_byte_count;   			  //接收到的数据长度  	
extern u8 uart6_byte_count;   			  //接收到的数据长度

void uart1_init(u32 baudRate);
void uart1SendChars(u8 *str, u8 strlen);	

void uart2_init(u32 baudRate);
void uart2SendChars(u8 *str, u8 strlen);					 
void RS485_Init(u32 baudRate);
void RS485_Send_Data(u8 *buf,u8 len);
/****************************************************************************
* 名    称: void RS485_Receive_Data(u8 *buf,u8 *len)
* 功    能：RS485查询接收到的数据
* 入口参数：buf:接收缓存首地址
            len:读到的数据长度
* 返回参数：无
* 说    明： 默认等待接收时间为10ms
****************************************************************************/
void RS485_Receive_Data(u8 *buf, u8 *len);
/****************************************************************************
* 名    称: void RS485_Receive_Data(u8 *buf, u8 *len, u8 wait_time_ms)
* 功    能：RS485查询接收到的数据
* 入口参数：buf:接收缓存首地址
            len:读到的数据长度
			wait_time_ms:等待接收的时间
* 返回参数：无
* 说    明：
****************************************************************************/
void RS485_Receive_Data(u8 *buf, u8 *len, u8 wait_time_ms);

void uart4_init(u32 baudRate);
void uart4SendChars(u8 *str, u8 strlen);	

void uart5_init(u32 baudRate);
void uart5SendChars(u8 *str, u8 strlen);	

void uart6_init(u32 baudRate);
void uart6SendChars(u8 *str, u8 strlen);	
#endif


