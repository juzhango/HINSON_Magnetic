#ifndef _KS136_H_
#define _KS136_H_
#include "I2C.h"
//关闭智能探测 75ms+ 0x75降噪
//降噪等级 供电模式   0x70电池, 0x71 usb, 0x72较长usb
//0x73开光电源, 0x74噪声大的开光电源, 0x75高噪声电源 精度依次减小
#define reduce_noise  0x75  
#define reg 0x02
#define turn_off_led  0xc1//探测灯显示 0xc0开   0xc1关
//探测<5m距离 0xb0/0xb4(温补)  <11m距离用0xb8 /0xbc
//25°C 环境下（后者为高精度温度补偿下的测量 精度1mm)
//噪声大用短距离测量指令
#define read_distance 0xb4 
#define read_brightness 0xa0 //亮度
#define read_temperature 0xc9 //温度
u8 KS136_ReadOneByte(u8 address,u8 reg_);
void KS136_WriteOneByte(u8 address,u8 reg_,u8 command); //address+register+command
void KS136_Init();
void KS136_ReduceNoise(u8 addr_old, u8 flag); 
u16 KS136_ReadDistacne(u16 address,u16 command);
void KS136_Change_Address(u8 addr_old, u8 addr_new);
/****************************************************************************
* 名    称: KS136_Change_Address(u8 addr_old, u8 addr_new)
* 功    能：配置杂波抑制功能（电源降噪指令，值越小抑制能力月底，越灵敏）
* 入口参数：旧地址     
* 入口参数：flag will be 0x70,0x71,0x72,0x73,0x74,0x75,0x7a,0x7b,0x7c,0x7d,0x7e
* 返回参数：无	   
* 说    明：       
****************************************************************************/
void KS136_Config_0x70_0x7d(unsigned char addr_old, unsigned char flag);
#endif
