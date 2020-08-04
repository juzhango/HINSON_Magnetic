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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();       //��ʼ����ʱ����

	LED_Init();					//��ʼ��LED 
	BEEP_Init();        //��ʼ��������
	LCD_Init();					//LCD��ʼ�� 
	KEY_Init(); 				//������ʼ��  
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

