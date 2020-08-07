#ifndef _KGL_H_
#define _KGL_H_

#include "common.h" 

//开关量IO输入
#define KGL0  PGin(0)  //手动or自动
#define KGL1  PGin(1)  //研磨盘正转
#define KGL2  PGin(2)  //研磨盘反转
#define KGL3  PGin(3)  //LED探照灯
#define KGL4  PGin(4) 
#define KGL5  PGin(5) 
#define KGL6  PDin(6)
#define KGL7  PDin(7)

void KGL_IO_Init(void);
#endif
