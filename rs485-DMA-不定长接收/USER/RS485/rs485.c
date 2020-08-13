#include "rs485.h"	
#include "string.h"
#include "stdlib.h"  
#include "led.h" 
#include "beep.h"
#include "stdbool.h"

//����2����  ������5  ͨ��4

  	  
//���ջ����� 	
bool RS485_rec_ok = 0;
u8 RS485_rec_str[RS485_REC_NUM];
u8 RS485_rec_count = 0;
										 
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
	
	#if USE_RS485_DMA
	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);//����DMA����
	//initialize the DMA channel.
	DMA_Config(DMA1_Stream5,DMA_Channel_4, 
						 (uint32_t)&(USART2->DR),     //����
						 (uint32_t)RS485_rec_str,//�洢��
						 DMA_DIR_PeripheralToMemory,//���赽�洢������
						 RS485_REC_NUM);//����
						 
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);         //��������ж�
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); 	
	#else
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);         //��������ж�
	USART_ITConfig(USART2, USART_IT_IDLE, DISABLE); 
	#endif
	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

/**
  * @brief  
  * @param  *DMA_Streamx: DMA������
  *         @arg DMA1_Stream0 ~ DMA1_Stream7:
  *         @arg DMA2_Stream0 ~ DMA2_Stream7:
  * @param  chx: DMAͨ��ѡ��
  *         @arg DMA_Channel_0 ~ DMA_Channel_7: ͨ��0 ~ ͨ��7
  * @param  par: �����ַ
  * @param  mar: �洢����ַ
  * @param  dir: 
  *         @arg DMA_DIR_PeripheralToMemory: 
  *         @arg DMA_DIR_MemoryToPeripheral: 
  *         @arg DMA_DIR_MemoryToMemory: 
  * @param  ndtr: ���ݴ�����
  * @retval None
  */
static void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx,uint32_t chx,uint32_t par,uint32_t mar,uint32_t dir,u16 ndtr)
{ 
 
	DMA_InitTypeDef  DMA_InitStructure;
	
	if((u32)DMA_Streamx>(u32)DMA2){
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
	}
	else{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1ʱ��ʹ�� 
	}
  DMA_DeInit(DMA_Streamx);
	
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}//�ȴ�DMA������ 
	
  /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel 								= chx;  							//ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr 			= par;								//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr 				= mar;								//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR 					    			= dir;								//direction of transmit.
  DMA_InitStructure.DMA_BufferSize 				    	= ndtr;								//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc						= DMA_PeripheralInc_Disable;		//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc 							= DMA_MemoryInc_Enable;				//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize 		  = DMA_PeripheralDataSize_Byte;		//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize 					= DMA_MemoryDataSize_Byte;			//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode 										= DMA_Mode_Normal;					// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority 								= DMA_Priority_High;				//�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode 								= DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold 			    = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst 						= DMA_MemoryBurst_Single;			//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst 		    = DMA_PeripheralBurst_Single;		//����ͻ�����δ���
  DMA_Init(DMA_Streamx, &DMA_InitStructure);
  DMA_Cmd(DMA_Streamx,ENABLE);
} 

/**
  * @brief  ����һ��DMA����
  * @param  *DMA_Streamx: DMA������
  *         @arg DMA1_Stream0 ~ DMA1_Stream7:
  *         @arg DMA2_Stream0 ~ DMA2_Stream7:
  * @param  ndtr: ���ݴ�����
  * @retval None
  */
static void DMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	DMA_Cmd(DMA_Streamx, DISABLE);                      //�ȹر�DMA,����������
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//�ȴ��������	
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //���ô������ݳ��� 
	DMA_Cmd(DMA_Streamx, ENABLE);                      //����DMA
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

#if USE_RS485_DMA
void RS485_Receive_Data(u8 *buf, u8 *len)
{
	int i=0;
	while(RS485_rec_ok==false)		//=== �ȴ�������ɱ�־
	{
		i++;
		delay_ms(1);
		if(i>=10)
		{
			RS485_rec_ok = 1;		//=== �ȴ����ճ�ʱ
			RS485_rec_count=0;
		}
	}
	for(i=0; i<RS485_rec_count; i++)
	{
		buf[i] = RS485_rec_str[i];	
	}
	*len = RS485_rec_count;
	RS485_rec_ok = 0;
}

#else
void RS485_Receive_Data(u8 *buf, u8 *len)
{
	u8 rxlen = RS485_rec_count;
	u8 i = 0;
	*len = 0;				 //Ĭ��Ϊ0
	delay_ms(2);		 //�ȴ�xxms,��������xxmsû�н��յ�һ������,����Ϊ���ս���

	if(rxlen == RS485_rec_count && rxlen) //���յ�������,�ҽ��������
	{
		for(i = 0; i < rxlen; i++)
		{
				buf[i] = RS485_rec_str[i];
		}
		*len = RS485_rec_count;	//��¼�������ݳ���
		RS485_rec_count = 0;		 //����
	}
}
#endif

//����2�����жϷ�����
void USART2_IRQHandler(void)
{	    
	#if USE_RS485_DMA
	if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)
	{
		RS485_rec_ok = true;
		RS485_rec_count=USART2->SR;
		RS485_rec_count=USART2->DR;//����������IDLE��־λ ��ֵ��Ч
		
		DMA_Cmd(DMA1_Stream5, DISABLE);//�ر�DMA��׼����������
		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);	// Clear Transfer Complete flag
		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TEIF5);	// Clear Transfer error flag	
		RS485_rec_count = RS485_REC_NUM - DMA_GetCurrDataCounter(DMA1_Stream5);//����������ݳ���
		
		uart3SendChars(RS485_rec_str,RS485_rec_count);
	}
	DMA_Enable(DMA1_Stream5,RS485_REC_NUM);//������һ��DMA����
	#else
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
	{	 	
		RS485_rec_str[RS485_rec_count] = (uint8_t)USART_ReceiveData(USART2);
		RS485_rec_count++;
	}  		
	#endif
} 
