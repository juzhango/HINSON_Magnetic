/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   rs485接收不定长数据，空闲中断+DMA传输，替代串口接收中断，可通过rs485头文件配置宏
  *          485接收到的数据可通过usart3 调试助手验证。
  *          	
  ******************************************************************************
  */




#include "common.h"
#include "usart3.h"
#include "led.h"
#include "beep.h"
#include "lcd.h"
#include "key.h"
#include "rs485.h"
uint8_t rec_buf[128];
uint8_t buf_len;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	delay_init();		      //延时初始化 
	uart3_init(115200);	    //串口初始化波特率为9600
	RS485_Init(115200);
	KEY_Init();
	LED_Init();		  		  //初始化与LED 

	while(1)
	{

		key_scan(0);
		
		if(keyup_data==KEY0_DATA)
		{
			RS485_Receive_Data(rec_buf,&buf_len);			//接收
			uart3SendChars(rec_buf,buf_len);					//debug 显示接收数据
			delay_ms(20);
			LED0=!LED0;
		}
	}
}


