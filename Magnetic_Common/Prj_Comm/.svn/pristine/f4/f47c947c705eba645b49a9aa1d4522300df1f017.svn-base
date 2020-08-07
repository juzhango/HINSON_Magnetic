#ifndef __TEABOT_UTILS_H
#define __TEABOT_UTILS_H
#include "common.h"

////////////////////////////////////////////////////////////////////////////////////	

/****************************************************************************
* 名    称: float convert_trans_rot_vel_to_steering_angle(double v, double omega, double wheelbase)
* 功    能：转换平移和旋转速度到汽车轮carlike的转向角度
* 入口参数：base_v 机器人平移速度
* 入口参数：omega 转向角速度
* 入口参数：wheelbase 轴距
* 返回参数：舵轮转向角度
* 说    明：
****************************************************************************/
float convert_trans_rot_vel_to_steering_angle(float base_v, float omega, float wheelbase);	

/****************************************************************************
* 名    称: float convert_trans_rot_steering_angle_to_robot_vel(float steering_angle, float omega, float wheelbase)
* 功    能：转换旋转速度和舵轮角度到机器人的平移速度
* 入口参数：steering_angel 舵轮角度
* 入口参数：omega 转向角速度
* 入口参数：wheelbase 轴距
* 入口参数：wheel_v 舵轮转速
* 返回参数：机器人 平移速度
* 说    明：
****************************************************************************/
float convert_trans_rot_steering_angle_to_robot_vel(float steering_angle, float omega, float wheelbase, float wheel_v);



/****************************************************************************
* 名    称: double convert_trans_vel_to_robot_rot(double v, double th, double wheelbase)
* 功    能：转换汽车轮carlike平移和舵轮的转向角度到机器人的转向角速度
* 入口参数：wheel_v 舵轮转速
* 入口参数：th 舵轮转向角度
* 入口参数：wheelbase 轴距
* 入口参数：wheelbase_diffAxisRatio 舵轮安装位置与中轴的偏移的比例系数
* 返回参数：机器人转向角速度
* 说    明：来源teb_local_planner_tutorials-indigo-devel cmd_vel_to_ackermann_drive.py
****************************************************************************/
float convert_trans_vel_to_robot_rot(float wheel_v, float th, float wheelbase, float wheelbase_diffAxisRatio);

//eMBRTUReceive函数完成了CRC校验、帧数据地址、长度的赋值，便于给上层进行处理！
bool checkRTUReceiveData( u8 addressId, u8* ucRTUBuf, u8 length, u8** pucFrame, u8* pusLength);
//组合数据，并计算填充crc值
bool combineRTUSendData( u8 ucSlaveAddress, u8 * pucFrame, u8 pusLength);

#endif