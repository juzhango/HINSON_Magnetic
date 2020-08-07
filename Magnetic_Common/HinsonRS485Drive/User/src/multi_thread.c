#include "TeamRobot_Drive.h"

#include "AGV_RS485_HINSON_MGS160N.h"
#include "usart3_user.h"
#include "rs485_user.h"



void thread_init()
{
	System_Init();
	delay_init();
	LED_Init();
	KEY_Init();
	uart3_init(115200);
	RS485_Init(115200);
	
	delay_ms(30);	//=== µÈ´ý×ÜÏß
	MGS160N_Choose_Init(MGS160N_CHOOSE_CENTRE);
	
}
void thread_start()
{
	while(1)
	{
		key_scan(0);
		if(keydown_data==KEY0_DATA)
		{		
			printf("test running\r\n");
			LED0=!LED0;			
		}
		
		AGV_RS485_MGS160N_Loop();
		delay_ms(30);
	}
}






