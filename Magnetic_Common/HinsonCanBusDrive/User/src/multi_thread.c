#include "TeamRobot_Drive.h"

#include "AGV_Can1_Msg_Receive.h"
#include "AGV_CANBUS_HINSON_MGS160N.h"
#include "usart3_user.h"



void thread_init()
{
	System_Init();
	delay_init();
	LED_Init();
	KEY_Init();
	uart3_init(115200);
	canopen.setup(CAN_125KBPS);
	AGV_Can1_Msg_Receive_Init();
	
	delay_ms(30);	//=== 等待总线
	MGS160N_Init();
	
}
void thread_start()
{
	while(1)
	{
		key_scan(0);
		if(keydown_data==KEY0_DATA)
		{		
			printf("切换到了左岔路\r\n");
			MGS160N_ReqLeftDiff();
			LED0=!LED0;			
		}
		printf("%d\r\n",MGS160N_Centre_Diff_MM);
		delay_ms(30);
	}
}






