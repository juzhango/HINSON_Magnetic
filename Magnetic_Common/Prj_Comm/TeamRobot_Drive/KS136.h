#ifndef _KS136_H_
#define _KS136_H_
#include "I2C.h"
//�ر�����̽�� 75ms+ 0x75����
//����ȼ� ����ģʽ   0x70���, 0x71 usb, 0x72�ϳ�usb
//0x73�����Դ, 0x74������Ŀ����Դ, 0x75��������Դ �������μ�С
#define reduce_noise  0x75  
#define reg 0x02
#define turn_off_led  0xc1//̽�����ʾ 0xc0��   0xc1��
//̽��<5m���� 0xb0/0xb4(�²�)  <11m������0xb8 /0xbc
//25��C �����£�����Ϊ�߾����¶Ȳ����µĲ��� ����1mm)
//�������ö̾������ָ��
#define read_distance 0xb4 
#define read_brightness 0xa0 //����
#define read_temperature 0xc9 //�¶�
u8 KS136_ReadOneByte(u8 address,u8 reg_);
void KS136_WriteOneByte(u8 address,u8 reg_,u8 command); //address+register+command
void KS136_Init();
void KS136_ReduceNoise(u8 addr_old, u8 flag); 
u16 KS136_ReadDistacne(u16 address,u16 command);
void KS136_Change_Address(u8 addr_old, u8 addr_new);
/****************************************************************************
* ��    ��: KS136_Change_Address(u8 addr_old, u8 addr_new)
* ��    �ܣ������Ӳ����ƹ��ܣ���Դ����ָ�ֵԽС���������µף�Խ������
* ��ڲ������ɵ�ַ     
* ��ڲ�����flag will be 0x70,0x71,0x72,0x73,0x74,0x75,0x7a,0x7b,0x7c,0x7d,0x7e
* ���ز�������	   
* ˵    ����       
****************************************************************************/
void KS136_Config_0x70_0x7d(unsigned char addr_old, unsigned char flag);
#endif
