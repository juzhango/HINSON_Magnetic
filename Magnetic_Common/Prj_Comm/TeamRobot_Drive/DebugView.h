#ifndef __DEBUGVIEW_H__
#define __DEBUGVIEW_H__
#include <stdio.h>

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数 并且可以通过DebugViewer功能来调试时查看数据，STM32F407 Core频率为168M

#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
	
	///////////// 输出到串口1  /////////////////////
	//while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	//USART1->DR = (u8) ch;
	
	///////////// 输出到Debug Viewer  /////////////////////
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}


//////////////////////////////////////////////////////////////////
#endif
