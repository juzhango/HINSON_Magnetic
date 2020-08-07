#include "stm32f4xx.h"  //叉车运动学模型 

#ifndef __FORKLIFT_KINEMATICS_MODEL_H__
#define __FORKLIFT_KINEMATICS_MODEL_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct
{
	float f32_Liner_Vel;   //线速度
	float f32_Angular_Vel; //角速度
}ST_TWIST_VEL;  //转向速度：线速度、角速度      TWIST(弯曲)

typedef struct
{
	float f32_Steer_Vel;   //舵轮速度
	float f32_Steer_Angle; //舵轮角度
}ST_STEER_SPD_ANGLE;       //舵轮速度角度结构体

typedef struct
{
	float f32_Correct_Angle;  //补偿角
	float f32_Wheelbase;      //轴距
	float f32_Center_Offset;  //中心偏移量   中轴线到舵轮的距离
	float f32_Center_Dis;     //轮距
}ST_STEER_CORRECT_FACTOR;//控制  修正  因素 //////////////////////////////////////////////////////////////////////////////////////////////


float Kinematics_Model_Positive(ST_TWIST_VEL *p1,ST_STEER_SPD_ANGLE *p2,const ST_STEER_CORRECT_FACTOR *p3); ////////////////////////////
float Kinematics_Model_Negative(ST_TWIST_VEL *p1,ST_STEER_SPD_ANGLE *p2,const ST_STEER_CORRECT_FACTOR *p3);//////////////////////////////


#endif
