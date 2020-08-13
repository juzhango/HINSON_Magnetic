/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   rs485���ղ��������ݣ������ж�+DMA���䣬������ڽ����жϣ���ͨ��rs485ͷ�ļ����ú�
  *          485���յ������ݿ�ͨ��usart3 ����������֤��
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	delay_init();		      //��ʱ��ʼ�� 
	uart3_init(115200);	    //���ڳ�ʼ��������Ϊ9600
	RS485_Init(115200);
	KEY_Init();
	LED_Init();		  		  //��ʼ����LED 

	while(1)
	{

		key_scan(0);
		
		if(keyup_data==KEY0_DATA)
		{
			RS485_Receive_Data(rec_buf,&buf_len);			//����
			uart3SendChars(rec_buf,buf_len);					//debug ��ʾ��������
			delay_ms(20);
			LED0=!LED0;
		}
	}
}


