/**
  ******************************************************************************
  * @file    AGV_RS485_HINSON_MGS160N.c
  * @author  
  * @version 1.0
  * @date    2020-8-3
  * @brief   ���̴Ŵ��������� HINSON CNS-MGS-160N
  *          1.�����������Ŷ�ƫ�ƾ��뷶Χ -70mm~70mm����Ч��Χ-50mm~50mm�����С��2mm����װ 20~53mm
  *          2.����������Ч��Χ-55mm~55mm������밲װ�Ƿ�ƽ���йأ����С��4mm����װ�߶� 13~40mm
  *          3.�����̴Ŷ�  ��Ч��Χ -60~60 �����С��3mm ��װ�߶�12~28mm
  *          4.��ָ�������� ��ʹ��485�������� ��ʱ 2~3ms
  *          5.��ָ�������գ����ڿ����жϣ�������ɱ�־λ, �Է����յ���������һ������ָ��ص����ݡ�
  *          
  ******************************************************************************
  */

#include "AGV_RS485_HINSON_MGS160N.h"

enum MGS160N_Parse_Type
{
	MGS160N_STATUS = 0,
	MGS160N_CHOOSE_DIFF = 1,
	MGS160N_CHOOSE_STRENGTH = 2,
	MGS160N_CHOOSE_RANGE,
	MGS160N_LEFT_DIFF,
	MGS160N_CENTRE_DIFF,
	MGS160N_RIGHT_DIFF,
	MGS160N_LEFT_STRENGTH,
	MGS160N_CENTRE_STRENGTH,
	MGS160N_RIGHT_STRENGTH,
	MGS160N_INDUCTION_STATUS,
};

/*******************************************************************************************/
//��ʼ��ָ�� ѡ���· 0:�� 1:�� 2:��  ȱʡ0
uint8_t MGS160N_CHOOSE_CENTRE_CND[8] = {0x78, 0x06, 0x07, 0xD0, 0x00, 0x00, 0x82, 0xEE};//=== ѡ�����	�Ĵ���2000 ������06
uint8_t MGS160N_CHOOSE_LEFT_CND[8] = {0x78, 0x06, 0x07, 0xD0, 0x00, 0x01, 0x43, 0x2E};//=== ѡ�����	�Ĵ���2000 ������06
uint8_t MGS160N_CHOOSE_RIGHT_CND[8] = {0x78, 0x06, 0x07, 0xD0, 0x00, 0x02, 0x03, 0x2F};//=== ѡ�����	�Ĵ���2000 ������06
//����ָ��
const uint8_t MGS160N_REQ_CMD_LEN = 8;
uint8_t MGS160N_DEVICE_STATUS_CND[8] = {0x78, 0x04, 0x03, 0xE8, 0x00, 0x01, 0xBA, 0x13};//=== �豸״̬	�Ĵ���1000
uint8_t MGS160N_INDUCTION_STATUS_CND[8] = {0x78, 0x04, 0x03, 0xE9, 0x00, 0x01, 0xEB, 0xD3};//=== ������Ӧ״̬	�Ĵ���1001	  4:��  2:��  1:��  0:��
uint8_t MGS160N_CHOOSE_DIFF_CMD[8] = {0x78, 0x04, 0x03, 0xEA, 0x00, 0x01, 0x1B, 0xD3};//=== ��ǰѡ�����ƫ��λ�� �Ĵ���1002
uint8_t MGS160N_CHOOSE_STRENGTH_CMD[8] = {0x78, 0x04, 0x03, 0xEB, 0x00, 0x01, 0x4A, 0x13};//=== ��ǰѡ�������ǿ  �Ĵ���1003
uint8_t MGS160N_CHOOSE_RANGE_CND[8] = {0x78, 0x04, 0x03, 0xEC, 0x00, 0x01, 0xFB, 0xD2};//=== ��ǰѡ�������Χ �Ĵ���1004

uint8_t MGS160N_LEFT_DIFF_CMD[8] = {0x78, 0x04, 0x03, 0xED, 0x00, 0x01, 0xAA, 0x12};//=== �����ƫ��λ�� �Ĵ���1005
uint8_t MGS160N_CENTRE_DIFF_CMD[8] = {0x78, 0x04, 0x03, 0xEE, 0x00, 0x01, 0x5A, 0x12};//=== �д���ƫ��λ�� �Ĵ���1006
uint8_t MGS160N_RIGHT_DIFF_CMD[8] = {0x78, 0x04, 0x03, 0xEF, 0x00, 0x01, 0x0B, 0xD2};//=== �Ҵ���ƫ��λ�� �Ĵ���1007
uint8_t MGS160N_LEFT_STRENGTH_CMD[8] = {0x78, 0x04, 0x03, 0xF0, 0x00, 0x01, 0x3A, 0x14};//=== �������ǿ  �Ĵ���1008
uint8_t MGS160N_CENTRE_STRENGTH_CMD[8] = {0x78, 0x04, 0x03, 0xF1, 0x00, 0x01, 0x6B, 0xD4};//=== �д�����ǿ  �Ĵ���1009
uint8_t MGS160N_RIGHT_STRENGTH_CMD[8] = {0x78, 0x04, 0x03, 0xF2, 0x00, 0x01, 0x9B, 0xD4};//=== �Ҵ�����ǿ  �Ĵ���1010




//mudbus���ݻ���
u8 MGS160N_GET_DATA_BUF[64];
u8 MGS160N_GET_DATA_COUNT = 0;

//������ʵʱ����
bool MGS160N_Device_Running = true;//�豸״̬
uint8_t MGS160N_Induction_Status = 0;//��Ӧ״̬ 4:��  2:��  1:��  0:��
int8_t MGS160N_Choose_Diff_MM = 0;//��ǰѡ�����ƫ�ƾ���(-70~70)
int16_t MGS160N_Choose_Strength = 0;//��ǰѡ�����ǿ��
uint8_t MGS160N_Choose_Range = 0;//��ǰ������Χ(1~16)

int8_t MGS160N_Left_Diff_MM = 0;//�����ƫ�ƾ���(-70~70)
int8_t MGS160N_Centre_Diff_MM = 0;//�д���ƫ�ƾ���(-70~70)
int8_t MGS160N_Right_Diff_MM = 0;//�Ҵ���ƫ�ƾ���(-70~70)

int16_t MGS160N_Left_Strength = 0;//�����ǿ��
int16_t MGS160N_Centre_Strength = 0;//�д���ǿ��
int16_t MGS160N_Right_Strength = 0;//�Ҵ���ǿ��


/**
  * @brief  ��·ѡ��
  * @param  type: 
  *         @arg MGS160N_CHOOSE_CENTRE: ��
  *         @arg MGS160N_CHOOSE_LEFT: ��
  *         @arg MGS160N_CHOOSE_RIGHT:	��
  * @retval None
  */
void MGS160N_Choose_Init(uint8_t type)
{
	uint8_t *buf;
	switch(type)
	{
		case MGS160N_CHOOSE_LEFT:
			buf = MGS160N_CHOOSE_LEFT_CND;
			break;
		case MGS160N_CHOOSE_CENTRE:
			buf = MGS160N_CHOOSE_CENTRE_CND;
			break;
		case MGS160N_CHOOSE_RIGHT:
			buf = MGS160N_CHOOSE_RIGHT_CND;
			break;
		default:
			break;
	}
	RS485_Send_Data(buf,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	if(MGS160N_GET_DATA_COUNT==8 && MGS160N_GET_DATA_BUF[5] == type)
	{
		printf("init ok");
	}
}

void debug_print()
{
	//��ʾ
//	printf("�豸����: \t%d \r\n",MGS160N_Device_Running);
//	printf("��Ӧ״̬: \t%d \r\n",MGS160N_Induction_Status);
	printf("��ǰƫ��: \t%d \r\n",MGS160N_Choose_Diff_MM);
//	printf("��ǰǿ��: \t%d \r\n",MGS160N_Choose_Strength);
//	printf("��ǰ��Χ: \t%d \r\n",MGS160N_Choose_Range);
//	printf("��ƫ��: \t%d \r\n",MGS160N_Left_Diff_MM);
//	printf("��ƫ��: \t%d \r\n",MGS160N_Centre_Diff_MM);
//	printf("��ƫ��: \t%d \r\n",MGS160N_Right_Diff_MM);
//	
//	printf("��ǿ��: \t%d \r\n",MGS160N_Left_Strength);
//	printf("��ǿ��: \t%d \r\n",MGS160N_Centre_Strength);
//	printf("��ǿ��: \t%d \r\n",MGS160N_Right_Strength);
	
//	printf("\r\n");
}

void AGV_RS485_MGS160N_Loop()
{
	getDeviceStatus();
//	getInductionStatus();
//	getChooseRange();
	getChooseDiff();
//	getChooseStrength();
//	getLeftDiff();
//	getCentreDiff();
//	getRightDiff();
//	getLeftStrength();
//	getCentreStrength();
//	getRightStrength();
	debug_print();
	
}


void getDeviceStatus()
{
	//�豸״̬
	RS485_Send_Data(MGS160N_DEVICE_STATUS_CND,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CHOOSE_DIFF);
}

void getInductionStatus()
{
	//��Ӧ״̬
	RS485_Send_Data(MGS160N_INDUCTION_STATUS_CND,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_INDUCTION_STATUS);
}
void getChooseRange()
{
	//��ǰ������Χ
	RS485_Send_Data(MGS160N_CHOOSE_RANGE_CND,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CHOOSE_RANGE);
}
void getChooseDiff()
{
	//��ǰ����ƫ��
	RS485_Send_Data(MGS160N_CHOOSE_DIFF_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CHOOSE_DIFF);
}
void getChooseStrength()
{
	//��ǰ������ǿ
	RS485_Send_Data(MGS160N_CHOOSE_STRENGTH_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CHOOSE_STRENGTH);
}
void getLeftDiff()
{
	//�����ƫ��
	RS485_Send_Data(MGS160N_LEFT_DIFF_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_LEFT_DIFF);
}
void getCentreDiff()
{
	//�д���ƫ��
	RS485_Send_Data(MGS160N_CENTRE_DIFF_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CENTRE_DIFF);
}
void getRightDiff()
{
	//�Ҵ���ƫ��
	RS485_Send_Data(MGS160N_RIGHT_DIFF_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_RIGHT_DIFF);
}
void getLeftStrength()
{
	//�������ǿ
	RS485_Send_Data(MGS160N_LEFT_STRENGTH_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_LEFT_STRENGTH);
}
void getCentreStrength()
{
	//�д�����ǿ
	RS485_Send_Data(MGS160N_CENTRE_STRENGTH_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CENTRE_STRENGTH);
}

void getRightStrength()
{
	//�Ҵ�����ǿ
	RS485_Send_Data(MGS160N_RIGHT_STRENGTH_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_RIGHT_STRENGTH);
}

/**
  * @brief  ����豸��ַ�����ֽ����Ƿ�ƥ��
  * @param  *getbuf: 485��������
  * @param  getbuf_count: 485���������ֽ���
  * @retval true: ������Ч
  */
bool MGS160N_Check_Buf(u8 * getbuf, u8 getbuf_count)
{
	if(getbuf[0] != DEVICE_ADDR){														//=== �豸��ַ
		printf("addr error!!\r\n");
		return false;
	}
	else if(getbuf[2]+5 !=  getbuf_count){						//5:�豸��ַ(1)+������(1)+���ݳ���(1)+CRCУ��(2)
		printf("getbuf count error!!\r\n");
		return false;
	}
	return true;
}


/**
  * @brief  
  * @param  *getbuf: 
  * @param  getbuf_count: 
  * @param  parse_type: switch��֧
  *         @arg MGS160N_STATUS: 
  *         @arg MGS160N_CHOOSE_DIFF: 
  *         @arg MGS160N_CHOOSE_STRENGTH: 
  *         @arg MGS160N_CHOOSE_RANGE: 
  *         @arg MGS160N_LEFT_DIFF: 
  *         @arg MGS160N_CENTRE_DIFF: 
  *         @arg MGS160N_RIGHT_DIFF: 
  *         @arg MGS160N_LEFT_STRENGTH: 
  *         @arg MGS160N_CENTRE_STRENGTH: 
  *         @arg MGS160N_RIGHT_STRENGTH: 
  *         @arg MGS160N_INDUCTION_STATUS: 
  * @retval None
  */
void MGS160N_Parse_Data(u8 *get_buf, u8 getbuf_count,u8 parse_type)
{
	if(MGS160N_Check_Buf(get_buf,getbuf_count))
	{
		switch(parse_type)
		{
			int16_t buf;

		case MGS160N_STATUS:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if(buf == 0x0)	MGS160N_Device_Running = true;
			else MGS160N_Device_Running = false;
			break;
		
		case MGS160N_CHOOSE_DIFF:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if((buf&0x8000) == 0x8000)
				MGS160N_Choose_Diff_MM = (buf - 0xffff) & 0x00ff;
			else
				MGS160N_Choose_Diff_MM = (int8_t)buf;
			break;
			
		case MGS160N_CHOOSE_STRENGTH:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if((buf&0x8000) == 0x8000)
				MGS160N_Choose_Strength = buf - 0xffff;
			else
				MGS160N_Choose_Strength = buf;
			break;
			
		case MGS160N_CHOOSE_RANGE:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			MGS160N_Choose_Range = (uint8_t) buf;
			break;
		
		case MGS160N_LEFT_DIFF:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if((buf&0x8000) == 0x8000)
				MGS160N_Left_Diff_MM = (buf - 0xffff) & 0x00ff;
			else
				MGS160N_Left_Diff_MM = (int8_t)buf;
			break;	
			
		case MGS160N_CENTRE_DIFF:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if((buf&0x8000) == 0x8000)
				MGS160N_Centre_Diff_MM = (buf - 0xffff) & 0x00ff;
			else
				MGS160N_Centre_Diff_MM = (int8_t)buf;
			break;	
			
		case MGS160N_RIGHT_DIFF:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if((buf&0x8000) == 0x8000)
				MGS160N_Right_Diff_MM = (buf - 0xffff) & 0x00ff;
			else
				MGS160N_Right_Diff_MM = (int8_t)buf;
			break;

		case MGS160N_LEFT_STRENGTH:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if((buf&0x8000) == 0x8000)
				MGS160N_Left_Strength = buf - 0xffff;
			else
				MGS160N_Left_Strength = buf;
			break;

		case MGS160N_CENTRE_STRENGTH:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if((buf&0x8000) == 0x8000)
				MGS160N_Centre_Strength = buf - 0xffff;
			else
				MGS160N_Centre_Strength = buf;
			break;	

		case MGS160N_RIGHT_STRENGTH:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if((buf&0x8000) == 0x8000)
				MGS160N_Right_Strength = buf - 0xffff;
			else
				MGS160N_Right_Strength = buf;
			break;	

		case MGS160N_INDUCTION_STATUS:
			buf = get_buf[3];
			buf = (buf<<8) | get_buf[4];
			if(buf >= 0 && buf <= 0x07)
				MGS160N_Induction_Status = (uint8_t)buf;
			break;			
		
		default:
				break;
		}
	}
}

