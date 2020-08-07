#include "rs485.h"	
#include "string.h"
#include "stdlib.h"  
#include "led.h" 
#include "beep.h"
	 


  	  
//���ջ����� 	
u8 RS485_rec_cache[512];   //���ջ���,���128���ֽ�.
u8 RS485_cache_count=0;        //���յ������ݳ���
//�����жϽ���һ֡
u8 RS485_rec_str[20];
u8 RS485_rec_count = 0;
bool rs485_rec_ok = 0;
										 
//��ʼ��IO ����2   bound:������	
void RS485_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	
  //����2���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3
	
	//PG8���������485ģʽ����  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //GPIOG6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOG,&GPIO_InitStructure); //��ʼ��PG8
	
	RS485_TX_EN=0;				//��ʼ��Ĭ��Ϊ����ģʽ	
	
   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ��� 2	
	USART_ClearFlag(USART2, USART_FLAG_TC);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//���������ж�
	#if USE_UART2_IDLE
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);         //��������ж�
	#else
	USART_ITConfig(USART2, USART_IT_IDLE, DISABLE); 
	#endif
	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

//����2�����жϷ�����
void USART2_IRQHandler(void)
{
	u8 rec_data;	    
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
	{	 	
		rec_data =(u8)USART_ReceiveData(USART2);         //(USART2->DR) ��ȡ���յ�������
		RS485_rec_cache[RS485_cache_count]=rec_data;
		RS485_cache_count++;
	}  	
#if USE_UART2_IDLE	
	else if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{
		u8 free_rec = USART2->DR;  //clear idle flag
//		int i;
//		for(i=0; i<RS485_cache_count; i++)
//		{
//			RS485_rec_str[i] = RS485_rec_cache[i];
//		}
//		RS485_rec_count = RS485_cache_count;
//		RS485_cache_count = 0;
		rs485_rec_ok = 1;
	}	
#endif
} 


void RS485_Send_Data(u8 *buf,u8 len)
{
	u8 t;
	RS485_TX_EN=1;			    //����Ϊ����ģʽ
  	for(t=0;t<len;t++)		//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET){} //�ȴ����ͽ���		
    USART_SendData(USART2,buf[t]); //��������
	}	 
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);   //�ȴ����ͽ���		  
	RS485_TX_EN=0;				//����������Ϊ����ģʽ	
}

#if USE_UART2_IDLE
void RS485_Receive_Data(u8 *buf, u8 *len)
{
	int i=0;
	while(!rs485_rec_ok)		//=== �ȴ�������ɱ�־
	{
		i++;
		delay_ms(1);
		if(i>=10)
		{
			rs485_rec_ok = 1;		//=== �ȴ���ʱ
			RS485_cache_count = 0;
		}
	}									
	rs485_rec_ok = 0;														
	for(i=0; i<RS485_cache_count; i++)
	{
		buf[i] = RS485_rec_cache[i];	
	}
	*len = RS485_cache_count;
	RS485_cache_count = 0;
}
#else
void RS485_Receive_Data(u8 *buf, u8 *len)
{
	u8 rxlen = RS485_cache_count;
	u8 i = 0;
	*len = 0;				 //Ĭ��Ϊ0
	delay_ms(2);		 //�ȴ�xxms,��������xxmsû�н��յ�һ������,����Ϊ���ս���

	if(rxlen == RS485_cache_count && rxlen) //���յ�������,�ҽ��������
	{
		for(i = 0; i < rxlen; i++)
		{
				buf[i] = RS485_rec_cache[i];
		}
		*len = RS485_cache_count;	//��¼�������ݳ���
		RS485_cache_count = 0;		 //����
	}
}
#endif


