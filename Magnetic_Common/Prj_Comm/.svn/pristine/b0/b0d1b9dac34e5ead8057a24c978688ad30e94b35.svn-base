#ifndef __STM32HARDWARE_H__
#define __STM32HARDWARE_H__

#include "ros_includes.h" 
#include <stdint.h>

class Stm32Hardware
{
	public:
		Stm32Hardware(){};
		void init(void)
        {
            baud_ = 230400;  //0: 115200  1: 230400  STM32板最大支持：450000bit/s
            Usart_Configuration(baud_);
        }
        
        int getBaud(){return baud_;}
        
        void setBaud(long baud)
        {
            this->baud_= baud;
        }
        
		int read(void)
        {
            if(Usart_DataAvailable())
            {
                return Usart_Getch();
            }
            else
            {
                return -1;
            }
        }
		void write(uint8_t* data, int length)
        {
            for(int i=0; i<length; i++)
            {
                while(!Usart_FreeSpace()){}
                Usart_Putch(data[i]);
            }
        }
		unsigned long time(void){return millis();}//System_GetTime()
        
    protected:        
        long baud_;
};

#endif
