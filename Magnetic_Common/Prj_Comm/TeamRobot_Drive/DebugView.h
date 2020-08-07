#ifndef __DEBUGVIEW_H__
#define __DEBUGVIEW_H__
#include <stdio.h>

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf���� ���ҿ���ͨ��DebugViewer����������ʱ�鿴���ݣ�STM32F407 CoreƵ��Ϊ168M

#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
	
	///////////// ���������1  /////////////////////
	//while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	//USART1->DR = (u8) ch;
	
	///////////// �����Debug Viewer  /////////////////////
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}


//////////////////////////////////////////////////////////////////
#endif
