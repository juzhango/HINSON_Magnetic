#ifndef __AGV_CAN1_MSG_RECEIVE_H__
#define __AGV_CAN1_MSG_RECEIVE_H__
#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#include "can1.h"
#include "CANopen.h"

extern CANopen canopen;

void AGV_Can1_Msg_Receive_Init(void);
void AGVCan1MsgReceiveProc(void);


#endif





