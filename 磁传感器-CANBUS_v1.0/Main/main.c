#include "common.h"
#include "led.h"
#include "beep.h" 
#include "lcd.h"
#include "key.h"
#include "stdbool.h"
#include "AGV_CANBUS_HINSON_MGS160N.h"
#include "usart3.h"


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	
	LED_Init();
	BEEP_Init();
	LCD_Init();
	KEY_Init();
	uart3_init(115200);
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,24,CAN_Mode_Normal);
	delay_ms(30);
	MGS160N_Init();
	while(1)
	{
		key_scan(0);
		if(keyup_data==KEY0_DATA)
		{
			LED0=!LED0;
			delay_ms(10);
		}
		printf("%d\r\n",MGS160N_Centre_Diff_MM);
		delay_ms(40);
	}  
}

