#include "rs485.h"	
#include "string.h"
#include "stdlib.h"  
#include "led.h" 
#include "beep.h"
	 


  	  
//接收缓存区 	
u8 RS485_rec_cache[512];   //接收缓冲,最大128个字节.
u8 RS485_cache_count=0;        //接收到的数据长度
//空闲中断接收一帧
u8 RS485_rec_str[20];
u8 RS485_rec_count = 0;
bool rs485_rec_ok = 0;
										 
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
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启接受中断
	#if USE_UART2_IDLE
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);         //开启相关中断
	#else
	USART_ITConfig(USART2, USART_IT_IDLE, DISABLE); 
	#endif
	//Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
}

//串口2接收中断服务函数
void USART2_IRQHandler(void)
{
	u8 rec_data;	    
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 	
		rec_data =(u8)USART_ReceiveData(USART2);         //(USART2->DR) 读取接收到的数据
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
	RS485_TX_EN=1;			    //设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET){} //等待发送结束		
    USART_SendData(USART2,buf[t]); //发送数据
	}	 
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);   //等待发送结束		  
	RS485_TX_EN=0;				//发送完设置为接收模式	
}

#if USE_UART2_IDLE
void RS485_Receive_Data(u8 *buf, u8 *len)
{
	int i=0;
	while(!rs485_rec_ok)		//=== 等待接收完成标志
	{
		i++;
		delay_ms(1);
		if(i>=10)
		{
			rs485_rec_ok = 1;		//=== 等待超时
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
	*len = 0;				 //默认为0
	delay_ms(2);		 //等待xxms,连续超过xxms没有接收到一个数据,则认为接收结束

	if(rxlen == RS485_cache_count && rxlen) //接收到了数据,且接收完成了
	{
		for(i = 0; i < rxlen; i++)
		{
				buf[i] = RS485_rec_cache[i];
		}
		*len = RS485_cache_count;	//记录本次数据长度
		RS485_cache_count = 0;		 //清零
	}
}
#endif


