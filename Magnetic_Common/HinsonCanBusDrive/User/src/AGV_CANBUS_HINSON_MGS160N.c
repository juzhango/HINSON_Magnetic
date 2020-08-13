/**
  ******************************************************************************
  * @file    
  * @author  
  * @version V1.0
  * @date    2020-8-7
  * @brief   ���̴Ŵ��������� HINSON CNS-MGS-160N
  *          1.�����������Ŷ�ƫ�ƾ��뷶Χ -70mm~70mm����Ч��Χ-50mm~50mm�����С��2mm����װ 20~53mm
  *          2.����������Ч��Χ-55mm~55mm������밲װ�Ƿ�ƽ���йأ����С��4mm����װ�߶� 13~40mm
  *          3.�����̴Ŷ�  ��Ч��Χ -60~60 �����С��3mm ��װ�߶�12~28mm
  *          
  *          4.ͨѶЭ��CANBUS�����ù㲥ģʽ���㲥��� 35ms
  *          5.��ʼ��������ȱʡ���ý���λ������
  *          6.�����120ŷ�ն˵���
  *          
  *          	
  ******************************************************************************
  */
#include "AGV_CANBUS_HINSON_MGS160N.h"
#include "AGV_Can1_Msg_Receive.h"


const uint8_t MGS160N_REQ_LEN = 2;
uint8_t MGS160N_REQ_CENTRE_Diff_CMD[MGS160N_REQ_LEN]={0x88, 0x00};//===��·ѡ�� 0���м�  1�����  2���Ҳ�
uint8_t MGS160N_REQ_LEFT_Diff_CMD[MGS160N_REQ_LEN]={0x88, 0x01};
uint8_t MGS160N_REQ_RIGHT_Diff_CMD[MGS160N_REQ_LEN]={0x88, 0x02};

bool MGS160N_Device_Running = true;//�豸״̬
uint8_t MGS160N_Induction_Status = 0;//��Ӧ״̬ 4:��  2:��  1:��  0:��
int8_t MGS160N_Diff_MM = 0;//��ǰѡ�����ƫ�ƾ���(-70~70)
uint16_t MGS160N_KGL;


/**
  * @brief  ��ʼ��������Ϊ�����м��·��λ������
  * @param  
  * @retval None
  */
void MGS160N_Init()
{
	MGS160N_ReqCentreDiff();
}

void MGS160N_ReqCentreDiff()
{
	// ��ַ+0x80 ����λ������
	canopen.sendMsg1(0x80+MGS160N_ADDR, 0, 0, MGS160N_REQ_CENTRE_Diff_CMD, MGS160N_REQ_LEN);
}
void MGS160N_ReqLeftDiff()
{
	// ��ַ+0x80 ����λ������
	canopen.sendMsg1(0x80+MGS160N_ADDR, 0, 0, MGS160N_REQ_LEFT_Diff_CMD, MGS160N_REQ_LEN);
}
void MGS160N_ReqRightDiff()
{
	// ��ַ+0x80 ����λ������
	canopen.sendMsg1(0x80+MGS160N_ADDR, 0, 0, MGS160N_REQ_RIGHT_Diff_CMD, MGS160N_REQ_LEN);
}




/**
  * @brief  ����MGS160N��Ӧ������
  * @param  msg: CAN1���յ�����
  * @retval None
  */
void Dispatch_MGS160N_Data(CanRxMsg msg)
{
	uint8_t i;
	uint8_t rec_buf[8];
	uint8_t len = msg.DLC;
	for(i = 0; i < len; i++){
		rec_buf[i] = msg.Data[i];
	}
	
	if(len==4){  																	//===λ������
		
		if(rec_buf[0] != 0) MGS160N_Device_Running = false;
		else MGS160N_Device_Running = true;
		
		MGS160N_Induction_Status = rec_buf[1];
		
		MGS160N_Diff_MM = rec_buf[2]<<8 & 0xFF00;
		MGS160N_Diff_MM |= rec_buf[3]; 
	}
	else if(len==3){																//=== ����������
		MGS160N_KGL = rec_buf[2] & 0x0001;										//=== S16
		MGS160N_KGL = (MGS160N_KGL<<8) | (rec_buf[1]);				//=== S15~S8
		MGS160N_KGL = (MGS160N_KGL<<7) | (rec_buf[0] >> 1);		//=== S7~S1
	}
}





