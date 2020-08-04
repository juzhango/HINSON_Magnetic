#include "led.h"
#include "beep.h" 
#include "lcd.h"
#include "key.h"
#include "rs485.h"
#include "usart3.h"

#include "stdbool.h"
#include "AGV_RS485_HINSON_MGS160N.h"



int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init();       //初始化延时函数

	LED_Init();					//初始化LED 
	BEEP_Init();        //初始化蜂鸣器
	LCD_Init();					//LCD初始化 
	KEY_Init(); 				//按键初始化  
	uart3_init(115200);
	RS485_Init(115200);
	MGS160N_Choose_Init(MGS160N_CHOOSE_CENTRE);				
	while(1)
	{
		
		AGV_RS485_MGS160N_Loop();
		
		delay_ms(100);
		/*
		key_scan(0);
		if(keyup_data==KEY0_DATA)
		{
			
		}
		*/
		

	}  
}

