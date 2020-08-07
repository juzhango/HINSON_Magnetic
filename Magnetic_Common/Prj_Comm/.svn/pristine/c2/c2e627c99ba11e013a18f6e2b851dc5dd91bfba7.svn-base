#ifndef _CANOPEN_H_
#define _CANOPEN_H_
#include "common.h"
#include "timer.h"
//#include "AGV_Can1_Msg_Receive.h"

#define CANopen_SUCCESS 1
#define CANopen_FAILURE 0
#define DEFAULT_NODE_ID 0x0001


#define DEFAULT_OVERTIME_MS 100

// Service Data Object (SDO)
// ------------------------------------
#define SDO_COMMAND_ID_BASE 0x600
#define SDO_REPLY_ID_BASE 0x580

// PDO
#define PDO1_COMMAND_ID_TX_BASE 0x180
#define PDO1_COMMAND_ID_RX_BASE 0x200
#define PDO2_COMMAND_ID_TX_BASE 0x280
#define PDO2_COMMAND_ID_RX_BASE 0x300


// DATA-Types
//       8Bit  16Bit 24Bit	32Bit
// write 0x2F  0x2B  0x27		0x23
// read  0x4F  0x4B  0x47		0x43
#define SDO_REQUEST_READ 0x40 			 //读取数据
#define SDO_RESPONSE_READ_8BIT 0x4F  //返回数据长度为1个字节时
#define SDO_RESPONSE_READ_16BIT 0x4B //返回数据长度为2个字节时
#define SDO_RESPONSE_READ_24BIT 0x47 //返回数据长度为3个字节时
#define SDO_RESPONSE_READ_32BIT 0x43 //返回数据长度为4个字节时


#define SDO_REQUEST_WRITE_8BIT 0x2F  //写入数据长度为1个字节
#define SDO_REQUEST_WRITE_16BIT 0x2B //写入数据长度为2个字节
#define SDO_REQUEST_WRITE_24BIT 0x27 //写入数据长度为3个字节
#define SDO_REQUEST_WRITE_32BIT 0x23 //写入数据长度为4个字节

#define SDO_RESPONSE_WRITE 0x60  		//成功响应写入的数据命令
#define SDO_RESPONSE_READ_WRITE_ERROR //读取或写入失败


#define SDO_ERROR_CODE 0x80

//波特率
#define CAN_50KBPS   60
#define CAN_100KBPS  30
#define CAN_125KBPS  24
#define CAN_200KBPS  15
#define CAN_250KBPS  12
#define CAN_500KBPS  6
#define CAN_1000KBPS 3
//extern ST_Can_Sdo_Rec_Data g_StCanRecData;
typedef struct
{
		CanRxMsg RxMessage;
		u32			 u32FrameId;
		bool     bSdoRecFlag;
}ST_Can_Sdo_Rec_Data;

class CANopen
{
public:
	CANopen(){}
	void setup(u8 canSpeed);//设置波特率
	
	u8 sendMsg(u8* msg,u8 len);						//发送数据
	u8 sendMsg1(u32 stdId, u32 extId, u8 ext,u8* msg,u8 len);
	u8 sendMsg2(u32 Id, u8 ext,u8* msg,u8 len);
	
	/****************************************************************************
	* 名		称: u8 receive_Msg(u8 *buf)
	* 功		能：can口接收数据查询
	* 入口参数：buf:数据缓存区;
	# 入口参数：bufLength:数据缓存区大小;
	* 返回参数：0,无数据被收到;
							其他,接收的数据长度;
	* 说		明：接收数据，没有接收到数据,直接退出
	****************************************************************************/
	u8 receive(u8 *buf, u8 bufLength);

	/****************************************************************************
	* 名		称: u8 receive(u8 *buf, int overtime_ms = 100)
	* 功		能：can口接收数据查询
	* 入口参数：buf:数据缓存区;
	# 入口参数：bufLength:数据缓存区大小;
	* 返回参数：0,无数据被收到;
							其他,接收的数据长度;
	* 说		明：//接收数据，大于一百毫秒没接收到就退出
	****************************************************************************/
	u8 receiveByTime(u8 *buf, u8 bufLength, int overtime_ms = 100);

	/****************************************************************************
	* 名		称: u8 CAN1_Receive_Msg(CanRxMsg* msg)
	* 功		能：can口接收数据查询
	* 入口参数：buf:数据缓存区;
	* 返回参数：0,无数据被收到;
							其他,接收的数据长度;
	* 说		明：接收数据，没有接收到数据,直接退出
	****************************************************************************/
	u8 receiveMsg(CanRxMsg* msg);

	/****************************************************************************
	* 名		称: u8 CAN1_Receive(CanRxMsg* msg, int overtime_ms = 100)
	* 功		能：can口接收数据查询
	* 入口参数：buf:数据缓存区;
	* 返回参数：0,无数据被收到;
							其他,接收的数据长度;
	* 说		明：//接收数据，大于一百毫秒没接收到就退出
	****************************************************************************/
	u8 receiveMsgByTime(CanRxMsg* msg, int overtime_ms = 100);
	
	u8 read(u16 index, u8 subIndex, u32* data, u16 id=DEFAULT_NODE_ID);
	u8 read8bit(u16 index, u8 subIndex, u8* data, u16 id=DEFAULT_NODE_ID);
	u8 Sdo_Read8bit(u16 index, u8 subIndex, u8* data,ST_Can_Sdo_Rec_Data* p, u16 id);
	u8 read16bit(u16 index, u8 subIndex, u16* data, u16 id=DEFAULT_NODE_ID);
	u8 Sdo_Read16bit(u16 index, u8 subIndex, u16* data,ST_Can_Sdo_Rec_Data* p, u16 id);
	u8 read32bit(u16 index, u8 subIndex, u32* data, u16 id=DEFAULT_NODE_ID);
	u8 Sdo_Read32bit(u16 index, u8 subIndex, u32* data,ST_Can_Sdo_Rec_Data* p, u16 id);
	
	u8 write8bit(u16 index, u8 subIndex, u8 data, u16 id=DEFAULT_NODE_ID);
	u8 Sdo_Write8bit(u16 index, u8 subIndex, u8 data,ST_Can_Sdo_Rec_Data* p, u16 id);
	u8 write16bit(u16 index, u8 subIndex, u16 data, u16 id=DEFAULT_NODE_ID);
	u8 Sdo_Write16bit(u16 index, u8 subIndex, u16 data,ST_Can_Sdo_Rec_Data* p, u16 id);
	u8 write32bit(u16 index, u8 subIndex, u32 data, u16 id=DEFAULT_NODE_ID);
	u8 Sdo_Write32bit(u16 index, u8 subIndex, u32 data,ST_Can_Sdo_Rec_Data* p, u16 id);
	
	void composeMsg(u8 type_byte,u16 index,u8 subIndex);
	private:
};

class CANopen2
{
public:
	CANopen2(){}
	void setup(u8 canSpeed);//设置波特率
	u8 sendMsg(u8* msg,u8 len);						//发送数据
	u8 sendMsg1(u32 stdId, u32 extId, u8 ext,u8* msg,u8 len);
	u8 sendMsg2(u32 Id, u8 ext,u8* msg,u8 len);
	/****************************************************************************
	* 名		称: u8 receive_Msg(u8 *buf)
	* 功		能：can口接收数据查询
	* 入口参数：buf:数据缓存区;
	# 入口参数：bufLength:数据缓存区大小;
	* 返回参数：0,无数据被收到;
							其他,接收的数据长度;
	* 说		明：接收数据，没有接收到数据,直接退出
	****************************************************************************/
	u8 receive(u8 *buf, u8 bufLength);

	/****************************************************************************
	* 名		称: u8 receive(u8 *buf, int overtime_ms = 100)
	* 功		能：can口接收数据查询
	* 入口参数：buf:数据缓存区;
	# 入口参数：bufLength:数据缓存区大小;
	* 返回参数：0,无数据被收到;
							其他,接收的数据长度;
	* 说		明：//接收数据，大于一百毫秒没接收到就退出
	****************************************************************************/
	u8 receiveByTime(u8 *buf, u8 bufLength, int overtime_ms = 100);

	/****************************************************************************
	* 名		称: u8 CAN1_Receive_Msg(CanRxMsg* msg)
	* 功		能：can口接收数据查询
	* 入口参数：buf:数据缓存区;
	* 返回参数：0,无数据被收到;
							其他,接收的数据长度;
	* 说		明：接收数据，没有接收到数据,直接退出
	****************************************************************************/
	u8 receiveMsg(CanRxMsg* msg);

	/****************************************************************************
	* 名		称: u8 CAN1_Receive(CanRxMsg* msg, int overtime_ms = 100)
	* 功		能：can口接收数据查询
	* 入口参数：buf:数据缓存区;
	* 返回参数：0,无数据被收到;
							其他,接收的数据长度;
	* 说		明：//接收数据，大于一百毫秒没接收到就退出
	****************************************************************************/
	u8 receiveMsgByTime(CanRxMsg* msg, int overtime_ms = 100);
	
	u8 read(u16 index, u8 subIndex, u32* data, u16 id=DEFAULT_NODE_ID);
	u8 read8bit(u16 index, u8 subIndex, u8* data, u16 id=DEFAULT_NODE_ID);
	u8 read16bit(u16 index, u8 subIndex, u16* data, u16 id=DEFAULT_NODE_ID);
	u8 read32bit(u16 index, u8 subIndex, u32* data, u16 id=DEFAULT_NODE_ID);
	
	u8 write8bit(u16 index, u8 subIndex, u8 data, u16 id=DEFAULT_NODE_ID);
	u8 write16bit(u16 index, u8 subIndex, u16 data, u16 id=DEFAULT_NODE_ID);
	u8 write32bit(u16 index, u8 subIndex, u32 data, u16 id=DEFAULT_NODE_ID);
	
	void composeMsg(u8 type_byte,u16 index,u8 subIndex);
	private:
};

#endif
