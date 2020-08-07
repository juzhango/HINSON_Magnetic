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
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //使能USART3时钟 	

	
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);  //GPIOB10复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10与GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);
   //USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);	
  USART_Cmd(USART3, ENABLE);
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
	
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//开启空闲中断
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);//开启DMA接收
	USART_Cmd(USART3, ENABLE);
	
	//initialize the DMA channel.
	DMA_Config(DMA1_Stream1,DMA_Channel_4, 
						 (uint32_t)&(USART3->DR),     //串口DR寄存器
						 (uint32_t)uart3_rec_str,//自定义的接收数据buf
						 DMA_DIR_PeripheralToMemory,//外设到存储器方向
						 USART3_REC_NUM);//长度

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

}
/**
  * @brief  
  * @param  *DMA_Streamx: DMA数据流
  *         @arg DMA1_Stream0 ~ DMA1_Stream7:
  *         @arg DMA2_Stream0 ~ DMA2_Stream7:
  * @param  chx: DMA通道选择
  *         @arg DMA_Channel_0 ~ DMA_Channel_7: 通道0 ~ 通道7
  * @param  par: 外设地址
  * @param  mar: 存储器地址
  * @param  dir: 
  *         @arg DMA_DIR_PeripheralToMemory: 
  *         @arg DMA_DIR_MemoryToPeripheral: 
  *         @arg DMA_DIR_MemoryToMemory: 
  * @param  ndtr: 数据传输量
  * @retval None
  */
void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx,uint32_t chx,uint32_t par,uint32_t mar,uint32_t dir,u16 ndtr)
{ 
 
	DMA_InitTypeDef  DMA_InitStructure;
	
	if((u32)DMA_Streamx>(u32)DMA2){
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能 
	}
	else{
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA1时钟使能 
	}
  DMA_DeInit(DMA_Streamx);
	
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}//等待DMA可配置 
	
  /* 配置 DMA Stream */
  DMA_InitStructure.DMA_Channel 								= chx;  							//通道选择
  DMA_InitStructure.DMA_PeripheralBaseAddr 			= par;								//DMA外设地址
  DMA_InitStructure.DMA_Memory0BaseAddr 				= mar;								//DMA 存储器0地址
  DMA_InitStructure.DMA_DIR 					    			= dir;								//direction of transmit.
  DMA_InitStructure.DMA_BufferSize 				    	= ndtr;								//数据传输量 
  DMA_InitStructure.DMA_PeripheralInc						= DMA_PeripheralInc_Disable;		//外设非增量模式
  DMA_InitStructure.DMA_MemoryInc 							= DMA_MemoryInc_Enable;				//存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize 		  = DMA_PeripheralDataSize_Byte;		//外设数据长度:8位
  DMA_InitStructure.DMA_MemoryDataSize 					= DMA_MemoryDataSize_Byte;			//存储器数据长度:8位
  DMA_InitStructure.DMA_Mode 										= DMA_Mode_Normal;					// 使用普通模式 
  DMA_InitStructure.DMA_Priority 								= DMA_Priority_High;				//中等优先级
  DMA_InitStructure.DMA_FIFOMode 								= DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold 			    = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst 						= DMA_MemoryBurst_Single;			//存储器突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst 		    = DMA_PeripheralBurst_Single;		//外设突发单次传输
  DMA_Init(DMA_Streamx, &DMA_InitStructure);
  DMA_Cmd(DMA_Streamx,ENABLE);
} 

/**
  * @brief  开启一次DMA传输
  * @param  *DMA_Streamx: DMA数据流
  *         @arg DMA1_Stream0 ~ DMA1_Stream7:
  *         @arg DMA2_Stream0 ~ DMA2_Stream7:
  * @param  ndtr: 数据传输量
  * @retval None
  */
void DMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	DMA_Cmd(DMA_Streamx, DISABLE);                      //先关闭DMA,才能设置它
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//等待传输结束	
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //设置传输数据长度 
	DMA_Cmd(DMA_Streamx, ENABLE);                      //开启DMA
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
		uart3_byte_count=USART3->DR;//软件序列清除IDLE标志位 赋值无效
		
		DMA_Cmd(DMA1_Stream1, DISABLE);//关闭DMA，准备重新配置
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);	// Clear Transfer Complete flag
		DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TEIF1);	// Clear Transfer error flag	
		uart3_byte_count = USART3_REC_NUM - DMA_GetCurrDataCounter(DMA1_Stream1);//计算接收数据长度
	}
	DMA_Enable(DMA1_Stream1,USART3_REC_NUM);//开启下一次DMA接收
} 


/**
  * @brief  
  * @param  *buf: 保存buf
  * @param  *len: 保存长度
  * @retval None
  */
void USART3_Receive_Data(u8 *buf, u8 *len)
{
	int i=0;
	while(!uart3_rec_ok)		//=== 等待接收完成标志
	{
		i++;
		delay_ms(1);
		if(i>=10)
		{
			uart3_rec_ok = 1;		//=== 等待超时
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
