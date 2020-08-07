/**
  ******************************************************************************
  * @file    AGV_RS485_HINSON_MGS160N.c
  * @author  
  * @version 1.0
  * @date    2020-8-3
  * @brief   兴颂磁传感器驱动 HINSON CNS-MGS-160N
  *          1.测量单个长磁钉偏移距离范围 -70mm~70mm，有效范围-50mm~50mm。误差小于2mm。安装 20~53mm
  *          2.测量磁条有效范围-55mm~55mm，误差与安装是否平行有关，误差小于4mm。安装高度 13~40mm
  *          3.测量短磁钉  有效范围 -60~60 ，误差小于3mm 安装高度12~28mm
  *          4.单指令发送与接收 可使用485接收数据 延时 2~3ms
  *          5.多指令发送与接收：串口空闲中断，接收完成标志位, 以防接收的数据是上一条请求指令返回的数据。
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
//初始化指令 选择岔路 0:中 1:左 2:右  缺省0
uint8_t MGS160N_CHOOSE_CENTRE_CND[8] = {0x78, 0x06, 0x07, 0xD0, 0x00, 0x00, 0x82, 0xEE};//=== 选择磁条	寄存器2000 功能码06
uint8_t MGS160N_CHOOSE_LEFT_CND[8] = {0x78, 0x06, 0x07, 0xD0, 0x00, 0x01, 0x43, 0x2E};//=== 选择磁条	寄存器2000 功能码06
uint8_t MGS160N_CHOOSE_RIGHT_CND[8] = {0x78, 0x06, 0x07, 0xD0, 0x00, 0x02, 0x03, 0x2F};//=== 选择磁条	寄存器2000 功能码06
//请求指令
const uint8_t MGS160N_REQ_CMD_LEN = 8;
uint8_t MGS160N_DEVICE_STATUS_CND[8] = {0x78, 0x04, 0x03, 0xE8, 0x00, 0x01, 0xBA, 0x13};//=== 设备状态	寄存器1000
uint8_t MGS160N_INDUCTION_STATUS_CND[8] = {0x78, 0x04, 0x03, 0xE9, 0x00, 0x01, 0xEB, 0xD3};//=== 磁条感应状态	寄存器1001	  4:右  2:中  1:左  0:无
uint8_t MGS160N_CHOOSE_DIFF_CMD[8] = {0x78, 0x04, 0x03, 0xEA, 0x00, 0x01, 0x1B, 0xD3};//=== 当前选择磁条偏移位置 寄存器1002
uint8_t MGS160N_CHOOSE_STRENGTH_CMD[8] = {0x78, 0x04, 0x03, 0xEB, 0x00, 0x01, 0x4A, 0x13};//=== 当前选择磁条场强  寄存器1003
uint8_t MGS160N_CHOOSE_RANGE_CND[8] = {0x78, 0x04, 0x03, 0xEC, 0x00, 0x01, 0xFB, 0xD2};//=== 当前选择磁条范围 寄存器1004

uint8_t MGS160N_LEFT_DIFF_CMD[8] = {0x78, 0x04, 0x03, 0xED, 0x00, 0x01, 0xAA, 0x12};//=== 左磁条偏移位置 寄存器1005
uint8_t MGS160N_CENTRE_DIFF_CMD[8] = {0x78, 0x04, 0x03, 0xEE, 0x00, 0x01, 0x5A, 0x12};//=== 中磁条偏移位置 寄存器1006
uint8_t MGS160N_RIGHT_DIFF_CMD[8] = {0x78, 0x04, 0x03, 0xEF, 0x00, 0x01, 0x0B, 0xD2};//=== 右磁条偏移位置 寄存器1007
uint8_t MGS160N_LEFT_STRENGTH_CMD[8] = {0x78, 0x04, 0x03, 0xF0, 0x00, 0x01, 0x3A, 0x14};//=== 左磁条场强  寄存器1008
uint8_t MGS160N_CENTRE_STRENGTH_CMD[8] = {0x78, 0x04, 0x03, 0xF1, 0x00, 0x01, 0x6B, 0xD4};//=== 中磁条场强  寄存器1009
uint8_t MGS160N_RIGHT_STRENGTH_CMD[8] = {0x78, 0x04, 0x03, 0xF2, 0x00, 0x01, 0x9B, 0xD4};//=== 右磁条场强  寄存器1010




//mudbus数据缓存
u8 MGS160N_GET_DATA_BUF[64];
u8 MGS160N_GET_DATA_COUNT = 0;

//传感器实时数据
bool MGS160N_Device_Running = true;//设备状态
uint8_t MGS160N_Induction_Status = 0;//感应状态 4:右  2:中  1:左  0:无
int8_t MGS160N_Choose_Diff_MM = 0;//当前选择磁条偏移距离(-70~70)
int16_t MGS160N_Choose_Strength = 0;//当前选择磁条强度
uint8_t MGS160N_Choose_Range = 0;//当前磁条范围(1~16)

int8_t MGS160N_Left_Diff_MM = 0;//左磁条偏移距离(-70~70)
int8_t MGS160N_Centre_Diff_MM = 0;//中磁条偏移距离(-70~70)
int8_t MGS160N_Right_Diff_MM = 0;//右磁条偏移距离(-70~70)

int16_t MGS160N_Left_Strength = 0;//左磁条强度
int16_t MGS160N_Centre_Strength = 0;//中磁条强度
int16_t MGS160N_Right_Strength = 0;//右磁条强度


/**
  * @brief  岔路选择
  * @param  type: 
  *         @arg MGS160N_CHOOSE_CENTRE: 中
  *         @arg MGS160N_CHOOSE_LEFT: 左
  *         @arg MGS160N_CHOOSE_RIGHT:	右
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
	//显示
//	printf("设备运行: \t%d \r\n",MGS160N_Device_Running);
//	printf("感应状态: \t%d \r\n",MGS160N_Induction_Status);
	printf("当前偏移: \t%d \r\n",MGS160N_Choose_Diff_MM);
//	printf("当前强度: \t%d \r\n",MGS160N_Choose_Strength);
//	printf("当前范围: \t%d \r\n",MGS160N_Choose_Range);
//	printf("左偏移: \t%d \r\n",MGS160N_Left_Diff_MM);
//	printf("中偏移: \t%d \r\n",MGS160N_Centre_Diff_MM);
//	printf("右偏移: \t%d \r\n",MGS160N_Right_Diff_MM);
//	
//	printf("左强度: \t%d \r\n",MGS160N_Left_Strength);
//	printf("中强度: \t%d \r\n",MGS160N_Centre_Strength);
//	printf("右强度: \t%d \r\n",MGS160N_Right_Strength);
	
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
	//设备状态
	RS485_Send_Data(MGS160N_DEVICE_STATUS_CND,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CHOOSE_DIFF);
}

void getInductionStatus()
{
	//感应状态
	RS485_Send_Data(MGS160N_INDUCTION_STATUS_CND,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_INDUCTION_STATUS);
}
void getChooseRange()
{
	//当前磁条范围
	RS485_Send_Data(MGS160N_CHOOSE_RANGE_CND,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CHOOSE_RANGE);
}
void getChooseDiff()
{
	//当前磁条偏移
	RS485_Send_Data(MGS160N_CHOOSE_DIFF_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CHOOSE_DIFF);
}
void getChooseStrength()
{
	//当前磁条场强
	RS485_Send_Data(MGS160N_CHOOSE_STRENGTH_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CHOOSE_STRENGTH);
}
void getLeftDiff()
{
	//左磁条偏移
	RS485_Send_Data(MGS160N_LEFT_DIFF_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_LEFT_DIFF);
}
void getCentreDiff()
{
	//中磁条偏移
	RS485_Send_Data(MGS160N_CENTRE_DIFF_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CENTRE_DIFF);
}
void getRightDiff()
{
	//右磁条偏移
	RS485_Send_Data(MGS160N_RIGHT_DIFF_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_RIGHT_DIFF);
}
void getLeftStrength()
{
	//左磁条场强
	RS485_Send_Data(MGS160N_LEFT_STRENGTH_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_LEFT_STRENGTH);
}
void getCentreStrength()
{
	//中磁条场强
	RS485_Send_Data(MGS160N_CENTRE_STRENGTH_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_CENTRE_STRENGTH);
}

void getRightStrength()
{
	//右磁条场强
	RS485_Send_Data(MGS160N_RIGHT_STRENGTH_CMD,MGS160N_REQ_CMD_LEN);
	RS485_Receive_Data(MGS160N_GET_DATA_BUF,&MGS160N_GET_DATA_COUNT);
	MGS160N_Parse_Data(MGS160N_GET_DATA_BUF,MGS160N_GET_DATA_COUNT,MGS160N_RIGHT_STRENGTH);
}

/**
  * @brief  检查设备地址，与字节数是否匹配
  * @param  *getbuf: 485接收数据
  * @param  getbuf_count: 485接收数据字节数
  * @retval true: 数据有效
  */
bool MGS160N_Check_Buf(u8 * getbuf, u8 getbuf_count)
{
	if(getbuf[0] != DEVICE_ADDR){														//=== 设备地址
		printf("addr error!!\r\n");
		return false;
	}
	else if(getbuf[2]+5 !=  getbuf_count){						//5:设备地址(1)+功能码(1)+数据长度(1)+CRC校验(2)
		printf("getbuf count error!!\r\n");
		return false;
	}
	return true;
}


/**
  * @brief  
  * @param  *getbuf: 
  * @param  getbuf_count: 
  * @param  parse_type: switch分支
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

