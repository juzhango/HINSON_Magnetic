#ifndef __SPI_H
#define __SPI_H
#include "common.h"

//////////////////////////////////////////////////////////////////////////////////	 
//CLK-PB3   MISO-PB4 CLK-PB5	    			
						
void SPI1_Init(void);			 //初始化SPI1口
void SPI1_Setclock(u8 SPI_Prescaler); //设置SPI1时钟速度   
u8 SPI1_ReadWriteByte(u8 writeData);  //SPI1总线读写一个字节
		 
#endif

