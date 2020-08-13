#include "rs485.h"	
#include "string.h"
#include "stdlib.h"  
#include "led.h" 
#include "beep.h"
#include "stdbool.h"

//串口2接收  数据流5  通道4

  	  
//接收缓存区 	
bool RS485_rec_ok = 0;
u8 RS485_rec_str[RS485_REC_NUM];
u8 RS485_rec_count = 0;
										 
//初始化IO 串口2   bound:波特率	
void RS485_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	
  //串口2引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2
	
	//USART2    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3
	
	//PG8推挽输出，485模式控制  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //GPIOG6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOG,&GPIO_InitStructure); //初始化PG8
	
	RS485_TX_EN=0;				//初始化默认为接收模式	
	
   //USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
	USART_Cmd(USART2, ENABLE);  //使能串口 2	

	USART_ClearFlag(USART2, USART_FLAG_TC);
	
	#if USE_RS485_DMA
	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);//开启DMA接收
	//initialize the DMA channel.
	DMA_Config(DMA1_Stream5,DMA_Channel_4, 
						 (uint32_t)&(USART2->DR),     //外设
						 (uint32_t)RS485_rec_str,//存储器
						 DMA_DIR_PeripheralToMemory,//外设到存储器方向
						 RS485_REC_NUM);//长度
						 
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);         //开启相关中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); 	
	#else
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);         //开启相关中断
	USART_ITConfig(USART2, USART_IT_IDLE, DISABLE); 
	#endif
	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
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
static void DMA_Config(DMA_Stream_TypeDef *DMA_Streamx,uint32_t chx,uint32_t par,uint32_t mar,uint32_t dir,u16 ndtr)
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
static void DMA_Enable(DMA_Stream_TypeDef *DMA_Streamx,u16 ndtr)
{
	DMA_Cmd(DMA_Streamx, DISABLE);                      //先关闭DMA,才能设置它
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//等待传输结束	
	DMA_SetCurrDataCounter(DMA_Streamx,ndtr);          //设置传输数据长度 
	DMA_Cmd(DMA_Streamx, ENABLE);                      //开启DMA
}	  




void RS485_Send_Data(u8 *buf,u8 len)
{
	u8 t;
	RS485_TX_EN=1;			    //设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET){} //等待发送结束		
    USART_SendData(USART2,buf[t]); //发送数据
	}	 
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);   //等待发送结束		  
	RS485_TX_EN=0;				//发送完设置为接收模式	
}

#if USE_RS485_DMA
void RS485_Receive_Data(u8 *buf, u8 *len)
{
	int i=0;
	while(RS485_rec_ok==false)		//=== 等待接收完成标志
	{
		i++;
		delay_ms(1);
		if(i>=10)
		{
			RS485_rec_ok = 1;		//=== 等待接收超时
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
	*len = 0;				 //默认为0
	delay_ms(2);		 //等待xxms,连续超过xxms没有接收到一个数据,则认为接收结束

	if(rxlen == RS485_rec_count && rxlen) //接收到了数据,且接收完成了
	{
		for(i = 0; i < rxlen; i++)
		{
				buf[i] = RS485_rec_str[i];
		}
		*len = RS485_rec_count;	//记录本次数据长度
		RS485_rec_count = 0;		 //清零
	}
}
#endif

//串口2接收中断服务函数
void USART2_IRQHandler(void)
{	    
	#if USE_RS485_DMA
	if(USART_GetITStatus(USART2,USART_IT_IDLE)!=RESET)
	{
		RS485_rec_ok = true;
		RS485_rec_count=USART2->SR;
		RS485_rec_count=USART2->DR;//软件序列清除IDLE标志位 赋值无效
		
		DMA_Cmd(DMA1_Stream5, DISABLE);//关闭DMA，准备重新配置
		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);	// Clear Transfer Complete flag
		DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TEIF5);	// Clear Transfer error flag	
		RS485_rec_count = RS485_REC_NUM - DMA_GetCurrDataCounter(DMA1_Stream5);//计算接收数据长度
		
		uart3SendChars(RS485_rec_str,RS485_rec_count);
	}
	DMA_Enable(DMA1_Stream5,RS485_REC_NUM);//开启下一次DMA接收
	#else
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 	
		RS485_rec_str[RS485_rec_count] = (uint8_t)USART_ReceiveData(USART2);
		RS485_rec_count++;
	}  		
	#endif
} 
