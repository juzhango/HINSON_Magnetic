#ifndef __I2C_H
#define __I2C_H
#include "common.h"  

////////////////////////////////////自定义I2C 管脚/////////////////////////////////////////
//IIC_SDA线IO方向配置
#define SDA_IN()  {GPIOB->MODER&=~(3<<18);GPIOB->MODER|=0<<18;}	//PB9输入模式
#define SDA_OUT() {GPIOB->MODER&=~(3<<18);GPIOB->MODER|=1<<18;} //PB9输出模式
//IO操作函数	 
#define IIC_SCL      PBout(8) //SCL
#define IIC_SDAOUT   PBout(9) //输出SDA	 
#define IIC_SDAIN    PBin(9)  //输入SDA 

//IIC相关函数
void IIC_Init(void);          //初始化IIC的IO口				 
void IIC_Start(void);				  //发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
u8 MCU_Wait_Ack(void); 				//IIC等待ACK信号
void MCU_Send_Ack(void);		  //IIC发送ACK信号
void MCU_NOAck(void);				  //IIC不发送ACK信号
void IIC_write_OneByte(u8 Senddata);
u8 IIC_Read_OneByte(u8 ack);	



#endif
