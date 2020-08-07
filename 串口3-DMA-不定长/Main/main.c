#include "common.h"
#include "usart3.h"
#include "led.h"
#include "beep.h"
#include "lcd.h"
#include "key.h"
uint8_t rec_buf[128];
uint8_t buf_len;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
	delay_init();		      //延时初始化 
	uart3_init(115200);	    //串口初始化波特率为9600
	KEY_Init();
	LED_Init();		  		  //初始化与LED 

	while(1)
	{

		key_scan(0);
		
		if(keyup_data==KEY0_DATA)
		{
			USART3_Receive_Data(rec_buf,&buf_len);
			uart3SendChars(rec_buf,buf_len);
			delay_ms(20);
			LED0=!LED0;
		}
		
		
	}
}


