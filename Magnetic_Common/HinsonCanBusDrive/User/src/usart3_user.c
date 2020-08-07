#include "usart3_user.h"
#include "string.h"
#include "stdlib.h"  
#include "led.h" 
#include "beep.h" 
#include "stdio.h"


u8 uart3_rec_cache[USART3_REC_NUM];
u8 uart3_rec_count=0;

/****************************************************************************
* ��    ��: void uart3_init(u32 bound)
* ��    �ܣ�USART1��ʼ��
* ��ڲ�����bound��������
* ���ز�������
* ˵    ���� 
****************************************************************************/
void uart3_init(u32 bound)
{   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ�� 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //ʹ��USART3ʱ�� 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);  //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10��GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);          //��ʼ��PB10��PB11
   //USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART3, &USART_InitStructure); //��ʼ������1	
  USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);         //��������ж�
#if USE_UART3_IDLE
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);         //��������ж�
#endif
	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;      //����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		   //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			   //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	  //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

//����1����һ���ַ�
void uart3SendChar(u8 ch)
{      
	while((USART3->SR&0x40)==0){} 
    USART3->DR = (u8) ch;      
}
/****************************************************************************
* ��    ��: void uart1SendChars(u8 *str, u16 strlen)
* ��    �ܣ�����1����һ�ַ���
* ��ڲ�����*str�����͵��ַ���
            strlen���ַ�������
* ���ز�������
* ˵    ���� 
****************************************************************************/
void uart3SendChars(u8 *str, u16 strlen)
{ 
	  u16 k= 0 ; 
   do { uart3SendChar(*(str + k)); k++; }   //ѭ������,ֱ���������   
    while (k < strlen); 
} 
#if USE_UART3_IDLE
void usar3_Receive_Data(u8 *buf, u8 *len)
{
	int i;
	*len = uart3_rec_count;
	for(i=0; i<uart3_rec_count; i++)
	{
		buf[i] = uart3_rec_cache[i];
	}
	uart3_rec_count = 0;
}
#else
void usar3_Receive_Data(u8 *buf, u8 *len)
{
	u8 rxlen = uart3_rec_count;
	u8 i = 0;
	*len = 0;				 //Ĭ��Ϊ0
	delay_ms(5);		 //�ȴ�xxms,��������xxmsû�н��յ�һ������,����Ϊ���ս���

	if(rxlen == uart3_rec_count && rxlen) //���յ�������,�ҽ��������
	{
		for(i = 0; i < rxlen; i++)
		{
				buf[i] = uart3_rec_cache[i];
		}
		*len = uart3_rec_count;	//��¼�������ݳ���
		uart3_rec_count = 0;		 //����
	}
}
#endif

//����1�жϷ������
void USART3_IRQHandler(void)  
{
	u8 rec_data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж� 
	{
		rec_data =(u8)USART_ReceiveData(USART3);  
		uart3_rec_cache[uart3_rec_count] = rec_data;
		uart3_rec_count++;
	}
#if USE_UART3_IDLE
	else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		rec_data = USART3->DR;
		flag = 1;
	}
#endif	
}


int std::fputc(int ch, std::FILE *f)
{
	uart3SendChar((u8)ch);
	return ch;
}









