#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "common.h"  

////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

#define USART1_REC_NUM  			100  	//�����������ֽ��� 200
#define USART2_REC_NUM  			200  	//�����������ֽ��� 123
#define RS485_REC_NUM  			128  	//�����������ֽ��� 123
#define RS485_TX_EN		PGout(6)	    //485ģʽ����.0,����;1,����.
#define UART4_REC_NUM  			200  	//�����������ֽ��� 123
#define UART5_REC_NUM  			200  	//�����������ֽ��� 123
#define USART6_REC_NUM  			200  	//�����������ֽ��� 123
extern u8 uart1_byte_count;          //uart_byte_countҪС��USART_REC_LEN
extern u8 uart1_receive_str[USART1_REC_NUM];  
extern u8 RS485_receive_str[RS485_REC_NUM]; 	//���ջ���,���128���ֽ�
extern u8 uart2_byte_count;   			  //���յ������ݳ���
extern u8 RS485_byte_count;   			  //���յ������ݳ���
/**************************************************************
*  MAX485оƬ��TX=PA2,RX=PA3,ģʽ����=PG6(0,����;1,����)
***************************************************************/
extern u8 UART4_receive_str[UART4_REC_NUM]; 	//���ջ���,���128���ֽ�
extern u8 uart4_byte_count;   			  //���յ������ݳ���
extern u8 uart5_receive_str[UART5_REC_NUM];  
extern u8 uart5_byte_count;   			  //���յ������ݳ���  	
extern u8 uart6_byte_count;   			  //���յ������ݳ���

void uart1_init(u32 baudRate);
void uart1SendChars(u8 *str, u8 strlen);	

void uart2_init(u32 baudRate);
void uart2SendChars(u8 *str, u8 strlen);					 
void RS485_Init(u32 baudRate);
void RS485_Send_Data(u8 *buf,u8 len);
/****************************************************************************
* ��    ��: void RS485_Receive_Data(u8 *buf,u8 *len)
* ��    �ܣ�RS485��ѯ���յ�������
* ��ڲ�����buf:���ջ����׵�ַ
            len:���������ݳ���
* ���ز�������
* ˵    ���� Ĭ�ϵȴ�����ʱ��Ϊ10ms
****************************************************************************/
void RS485_Receive_Data(u8 *buf, u8 *len);
/****************************************************************************
* ��    ��: void RS485_Receive_Data(u8 *buf, u8 *len, u8 wait_time_ms)
* ��    �ܣ�RS485��ѯ���յ�������
* ��ڲ�����buf:���ջ����׵�ַ
            len:���������ݳ���
			wait_time_ms:�ȴ����յ�ʱ��
* ���ز�������
* ˵    ����
****************************************************************************/
void RS485_Receive_Data(u8 *buf, u8 *len, u8 wait_time_ms);

void uart4_init(u32 baudRate);
void uart4SendChars(u8 *str, u8 strlen);	

void uart5_init(u32 baudRate);
void uart5SendChars(u8 *str, u8 strlen);	

void uart6_init(u32 baudRate);
void uart6SendChars(u8 *str, u8 strlen);	
#endif


