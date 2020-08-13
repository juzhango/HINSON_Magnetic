/**
  ******************************************************************************
  * @file    
  * @author  
  * @version V1.0
  * @date    2020-8-7
  * @brief   兴颂磁传感器驱动 HINSON CNS-MGS-160N
  *          1.测量单个长磁钉偏移距离范围 -70mm~70mm，有效范围-50mm~50mm。误差小于2mm。安装 20~53mm
  *          2.测量磁条有效范围-55mm~55mm，误差与安装是否平行有关，误差小于4mm。安装高度 13~40mm
  *          3.测量短磁钉  有效范围 -60~60 ，误差小于3mm 安装高度12~28mm
  *          
  *          4.通讯协议CANBUS，配置广播模式，广播间隔 35ms
  *          5.初始化函数，缺省设置接收位置数据
  *          6.必须接120欧终端电阻
  *          
  *          	
  ******************************************************************************
  */
#include "AGV_CANBUS_HINSON_MGS160N.h"
#include "AGV_Can1_Msg_Receive.h"


const uint8_t MGS160N_REQ_LEN = 2;
uint8_t MGS160N_REQ_CENTRE_Diff_CMD[MGS160N_REQ_LEN]={0x88, 0x00};//===岔路选择 0：中间  1：左侧  2：右侧
uint8_t MGS160N_REQ_LEFT_Diff_CMD[MGS160N_REQ_LEN]={0x88, 0x01};
uint8_t MGS160N_REQ_RIGHT_Diff_CMD[MGS160N_REQ_LEN]={0x88, 0x02};

bool MGS160N_Device_Running = true;//设备状态
uint8_t MGS160N_Induction_Status = 0;//感应状态 4:右  2:中  1:左  0:无
int8_t MGS160N_Diff_MM = 0;//当前选择磁条偏移距离(-70~70)
uint16_t MGS160N_KGL;


/**
  * @brief  初始化传感器为接收中间岔路的位置数据
  * @param  
  * @retval None
  */
void MGS160N_Init()
{
	MGS160N_ReqCentreDiff();
}

void MGS160N_ReqCentreDiff()
{
	// 地址+0x80 设置位置数据
	canopen.sendMsg1(0x80+MGS160N_ADDR, 0, 0, MGS160N_REQ_CENTRE_Diff_CMD, MGS160N_REQ_LEN);
}
void MGS160N_ReqLeftDiff()
{
	// 地址+0x80 设置位置数据
	canopen.sendMsg1(0x80+MGS160N_ADDR, 0, 0, MGS160N_REQ_LEFT_Diff_CMD, MGS160N_REQ_LEN);
}
void MGS160N_ReqRightDiff()
{
	// 地址+0x80 设置位置数据
	canopen.sendMsg1(0x80+MGS160N_ADDR, 0, 0, MGS160N_REQ_RIGHT_Diff_CMD, MGS160N_REQ_LEN);
}




/**
  * @brief  解析MGS160N回应的数据
  * @param  msg: CAN1接收的数据
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
	
	if(len==4){  																	//===位置数据
		
		if(rec_buf[0] != 0) MGS160N_Device_Running = false;
		else MGS160N_Device_Running = true;
		
		MGS160N_Induction_Status = rec_buf[1];
		
		MGS160N_Diff_MM = rec_buf[2]<<8 & 0xFF00;
		MGS160N_Diff_MM |= rec_buf[3]; 
	}
	else if(len==3){																//=== 开关量数据
		MGS160N_KGL = rec_buf[2] & 0x0001;										//=== S16
		MGS160N_KGL = (MGS160N_KGL<<8) | (rec_buf[1]);				//=== S15~S8
		MGS160N_KGL = (MGS160N_KGL<<7) | (rec_buf[0] >> 1);		//=== S7~S1
	}
}





