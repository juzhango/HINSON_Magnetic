#ifndef __CAN1_H
#define __CAN1_H	 
#include "common.h"	 
#include "stddef.h"

//////////////////////////////////////////////////////////////////////////////////	 


	

////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

extern void (*CAN1_ReceiveMsgFuncP)();  //Can1�յ���Ϣ����ʱ�ص�����ָ��
										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
//Can1�����жϳ�ʼ����Ĭ��ֻ����Can1 Rx0�ж�
void CAN1_INT_Init_ByDefault_RX0();
//Can1�����жϳ�ʼ��
void CAN1_INT_Init(uint32_t CAN_IT_KINDS, uint8_t CAN_IRQChannel);
//����Can1��Ϣ������
void CAN1_Filter_Init(uint32_t filterNumber, uint32_t slave_id);
//�����ж�
void CAN1_INIT_Start(uint32_t CAN_IT_KINDS);
//�����ж�
void CAN1_INIT_Stop(uint32_t CAN_IT_KINDS);
//�����ж�Ĭ��ΪRX0
void CAN1_INIT_Start_ByDefault_RX0();
//�����ж�Ĭ��ΪRX0
void CAN1_INIT_Stop_ByDefault_RX0();

 
/****************************************************************************
* ��		��: void initCanMessage(CanRxMsg* msg)
* ��		�ܣ���ʼ��������Ϣ��
* ��ڲ�����msg:����ָ��,���Ϊ8���ֽ�.
* ˵		������ʵ�ʲ��Դ��ڽ��ձ�׼֡��Ϣʱ�����ḳֵ��չ֡��������չ֡��Ϣ���ḳֵ��׼֡���ݵ���������Խ�����������Ҫ�ȳ�ʼ��
****************************************************************************/
void initCanMessage(CanRxMsg* msg);
 
u8 CAN1_Send_Msg(u8* msg,u8 len);						//��������
u8 CAN1_Send_Msg1(u32 stdId, u32 extId, u8 ext,u8* msg,u8 len);
/****************************************************************************
* ��		��: u8 CAN1_Receive_Msg(u8 *buf)
* ��		�ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;
# ��ڲ�����bufLength:���ݻ�������С;
* ���ز�����0,�����ݱ��յ�;
						����,���յ����ݳ���;
* ˵		����
****************************************************************************/
u8 CAN1_Receive(u8 *buf, u8 bufLength);


/****************************************************************************
* ��		��: u8u8 CAN1_Receive_ByTime(u8 *buf, u8 bufLength, int overtime_ms = 100)
* ��		�ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;
# ��ڲ�����bufLength:���ݻ�������С;
* ���ز�����0,�����ݱ��յ�;
						����,���յ����ݳ���;
* ˵		����
****************************************************************************/
u8 CAN1_Receive_ByTime(u8 *buf, u8 bufLength, int overtime_ms = 100);

/****************************************************************************
* ��		��: u8 CAN1_Receive_Msg(CanRxMsg* msg)
* ��		�ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;
* ���ز�����0,�����ݱ��յ�;
						����,���յ����ݳ���;
* ˵		����
****************************************************************************/
u8 CAN1_Receive_Msg(CanRxMsg* msg);

/****************************************************************************
* ��		��: u8 CAN1_Receive(CanRxMsg* msg, int overtime_ms = 100)
* ��		�ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;
* ���ز�����0,�����ݱ��յ�;
						����,���յ����ݳ���;
* ˵		����
****************************************************************************/
u8 CAN1_Receive_Msg_ByTime(CanRxMsg* msg, int overtime_ms = 100);


/****************************************************************************
* ��		��: u8 CAN1_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, int overtime_ms = 100)
* ��		�ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;
* ���ز�����0,�����ݱ��յ�;
						����,���յ����ݳ���;
* ˵		����
****************************************************************************/
u8 CAN1_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, int overtime_ms = 100);

/****************************************************************************
* ��		��: u8 CAN1_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, u16 index, u8 subIndex, int overtime_ms)
* ��		�ܣ�can�ڽ������ݲ�ѯ
* ��ڲ�����buf:���ݻ�����;
* ���ز�����0,�����ݱ��յ�;
						����,���յ����ݳ���;
* ˵		����
****************************************************************************/
u8 CAN1_Receive_Validate_Msg_ByTime(CanRxMsg* msg, u16 validateStdId, u16 index, u8 subIndex, int overtime_ms = 100);


#endif

















