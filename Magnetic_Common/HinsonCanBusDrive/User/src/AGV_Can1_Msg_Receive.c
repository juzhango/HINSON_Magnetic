#include "AGV_Can1_Msg_Receive.h"
#include "AGV_CANBUS_HINSON_MGS160N.h"
CANopen canopen;


void AGV_Can1_Msg_Receive_Init()
{
	CAN1_INT_Init(CAN_IT_FMP0,CAN1_RX0_IRQn);
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	CAN1_ReceiveMsgFuncP = &AGVCan1MsgReceiveProc;
}


void DispatchCan1ReceiveMsg(CanRxMsg* msg)
{
	switch(msg->StdId)
	{
		case MGS160N_ADDR:
			Dispatch_MGS160N_Data(*msg);
			break;
		default:
		  break;
	}
}

//Can1收到消息的回调函数
void AGVCan1MsgReceiveProc()
{
	CanRxMsg msg;
	if(canopen.receiveMsg(&msg))
		DispatchCan1ReceiveMsg(&msg);
}








