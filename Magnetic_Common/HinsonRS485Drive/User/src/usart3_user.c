#include "usart3_user.h"
#include "string.h"
#include "stdlib.h"  
#include "led.h" 
#include "beep.h" 
#include "stdio.h"


u8 uart3_rec_cache[USART3_REC_NUM];
u8 uart3_rec_count=0;

/****************************************************************************
* 名    称: void uart3_init(u32 bound)
* 功    能：USART1初始化
* 入口参数：bound：波特率
* 返回参数：无
* 说    明： 
****************************************************************************/
void uart3_init(u32 bound)
{   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟 
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
	GPIO_Init(GPIOB,&GPIO_InitStructure);          //初始化PB10，PB11
   //USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART3, &USART_InitStructure); //初始化串口1	
  USART_Cmd(USART3, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);         //开启相关中断
#if USE_UART3_IDLE
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);         //开启相关中断
#endif
	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;      //串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		   //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			   //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	  //根据指定的参数初始化VIC寄存器、
}

//串口1发送一个字符
void uart3SendChar(u8 ch)
{      
	while((USART3->SR&0x40)==0){} 
    USART3->DR = (u8) ch;      
}
/****************************************************************************
* 名    称: void uart1SendChars(u8 *str, u16 strlen)
* 功    能：串口1发送一字符串
* 入口参数：*str：发送的字符串
            strlen：字符串长度
* 返回参数：无
* 说    明： 
****************************************************************************/
void uart3SendChars(u8 *str, u16 strlen)
{ 
	  u16 k= 0 ; 
   do { uart3SendChar(*(str + k)); k++; }   //循环发送,直到发送完毕   
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
	*len = 0;				 //默认为0
	delay_ms(5);		 //等待xxms,连续超过xxms没有接收到一个数据,则认为接收结束

	if(rxlen == uart3_rec_count && rxlen) //接收到了数据,且接收完成了
	{
		for(i = 0; i < rxlen; i++)
		{
				buf[i] = uart3_rec_cache[i];
		}
		*len = uart3_rec_count;	//记录本次数据长度
		uart3_rec_count = 0;		 //清零
	}
}
#endif

//串口1中断服务程序
void USART3_IRQHandler(void)  
{
	u8 rec_data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断 
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









