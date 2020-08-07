#include "usart3.h"
#include "string.h"
#include "stdlib.h"  

bool uart3_rec_ok = false;
u8 uart3_rec_str[USART3_REC_NUM];    
u8 uart3_byte_count=0;

/**
  * @brief  
  * @param  bound:
  * @retval None
  */
void uart3_init(u32 bound)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
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
	GPIO_Init(GPIOB,&GPIO_InitStructure);
   //USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);	
  USART_Cmd(USART3, ENABLE);
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
	
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//���������ж�
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);//����DMA����
	USART_Cmd(USART3, ENABLE);
	
	//initialize the DMA channel.
	DMA_Config(DMA1_Stream1,DMA_Channel_4, 
						 (uint32_t)&(USART3->DR),     //����DR�Ĵ���
						 (uint32_t)uart3_rec_str,//�Զ���Ľ�������buf
						 DMA_DIR_PeripheralToMemory,//���赽�洢������
						 USART3_REC_NUM);//����

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

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
void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx,uint32_t chx,uint32_t par,uint32_t mar,uint32_t dir,u16 ndtr)
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
void DMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	DMA_Cmd(DMA_Streamx, DISABLE);                      //�ȹر�DMA,����������
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//�ȴ��������	
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //���ô������ݳ��� 
	DMA_Cmd(DMA_Streamx, ENABLE);                      //����DMA
}	  

void uart3SendChar(u8 ch)
{      
	while((USART3->SR&0x40)==0){}  
	USART3->DR = (u8) ch;      
}

void uart3SendChars(u8 *str, u16 strlen)
{ 
	u16 k= 0;
	do { uart3SendChar(*(str + k)); k++; }
	while (k < strlen);
} 


void USART3_IRQHandler(void)  
{
	if(USART_GetITStatus(USART3,USART_IT_IDLE)!=RESET)
	{
		uart3_rec_ok = true;
		uart3_byte_count=USART3->SR;
		uart3_byte_count=USART3->DR;//����������IDLE��־λ ��ֵ��Ч
		
		DMA_Cmd(DMA1_Stream1, DISABLE);//�ر�DMA��׼����������
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);	// Clear Transfer Complete flag
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TEIF1);	// Clear Transfer error flag	
		uart3_byte_count = USART3_REC_NUM - DMA_GetCurrDataCounter(DMA1_Stream1);//����������ݳ���
	}
	DMA_Enable(DMA1_Stream1,USART3_REC_NUM);//������һ��DMA����
} 


/**
  * @brief  
  * @param  *buf: ����buf
  * @param  *len: ���泤��
  * @retval None
  */
void USART3_Receive_Data(u8 *buf, u8 *len)
{
	int i=0;
	while(!uart3_rec_ok)		//=== �ȴ�������ɱ�־
	{
		i++;
		delay_ms(1);
		if(i>=10)
		{
			uart3_rec_ok = 1;		//=== �ȴ���ʱ
		}
	}
	for(i=0; i<uart3_byte_count; i++)
	{
		buf[i] = uart3_rec_str[i];	
	}
	*len = uart3_byte_count;
	uart3_rec_ok = 0;
}

int fputc(int ch, FILE *f)
{
	while((USART3->SR&0x40)==0){}  
    USART3->DR = (u8) ch;   
	return ch;
}
