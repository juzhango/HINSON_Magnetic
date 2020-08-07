#include "usart3.h"
#include "led.h"
#include "beep.h"
#include "lcd.h"
#include "key.h"

/*********************************************************************************
*********************�������� STM32F407Ӧ�ÿ�����(�����)*************************
**********************************************************************************
* �ļ�����: USART3�������������main.c                                           *
* �ļ�������USART3�������ʹ��                                                   *
* �������ڣ�2017.08.30                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    �������ô��ڵ������־���USART3����LED�������������գ���KEY0���ڷ�����  *
            �ݵ����ڵ�������                                                     * 
* �Ա����̣�https://shop125046348.taobao.com                                     *
**********************************************************************************
*********************************************************************************/

int main(void)
{   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����ϵͳ�ж����ȼ�����2
	delay_init();		      //��ʱ��ʼ�� 
	uart3_init(9600);	    //���ڳ�ʼ��������Ϊ9600
	KEY_Init();
	LED_Init();		  		  //��ʼ����LED 
	BEEP_Init();          //��������ʼ��
	USART3_DMA_Config();

	while(1)
	{
		if(receive_flag==1)
		{
			uart3SendChars("UART3 TEST",11);
			uart3SendChars(uart3_rec_str,uart3_byte_count);
			receive_flag = 0;
		}
		key_scan(0);
		
		if(keyup_data==KEY0_DATA)
		  {
		   uart3SendChars("UART3 TEST",11);
		  }
	}
}

