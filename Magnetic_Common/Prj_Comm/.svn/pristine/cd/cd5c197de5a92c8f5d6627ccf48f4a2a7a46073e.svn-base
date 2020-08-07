#ifndef _MOTIONMODELDSTEERS_H_
#define _MOTIONMODELDSTEERS_H_

/////////////////////////////////////////////////////////
//
//  中轴线前后位双舵轮运动模型解算函数
//
////////////////////////////////////////////////////////

//机器人整体速度信息
struct TeabotRobotVelInfo
{
	float vx;	//x方向线速度
	float vy; //y方向线速度（舵向值）
	float vth; //角速度
	
	TeabotRobotVelInfo()
	{
		vx = 0;
		vy = 0;
		vth = 0;
	}
};


//双舵轮速度信息
struct DoubleSteersVelInfo
{
	float v1;  //轮1速度
	float v2;  //轮2速度
	float theta1; //轮1角弧度
	float theta2; //轮2角弧度
	
	DoubleSteersVelInfo()
	{
		v1 = 0;
		v2 = 0;
		theta1 = 0;
		theta2 = 0;
	}
};


namespace teabot_dsteers
{
	
/*******************************************************************************
** Function name:    convert_robot_vel_to_steers_vel(const TeabotRobotVelInfo robotInfo, const float wheel_dAxisLength, DoubleSteersVelInfo& steersVelInfo)
** robotInfo： 机器人速度信息
** wheel_dAxisLength:  轮距：两舵轮旋转中心点之间的距离D
** steersVelInfo:  舵轮速度信息
********************************************************************************/
	void convert_robot_vel_to_steers_vel(const TeabotRobotVelInfo robotInfo, const float wheel_dAxisLength, DoubleSteersVelInfo& steersVelInfo,bool b_SteerPositiveRecog);

/*******************************************************************************
** Function name:    convert_steers_vel_to_robot_vel(const DoubleSteersVelInfo steersVelInfo, const float wheel_dAxisLength, TeabotRobotVelInfo& robotInfo)
** steersVelInfo:  舵轮速度信息
** wheel_dAxisLength:  轮距：两舵轮旋转中心点之间的距离D
** robotInfo： 机器人速度信息
********************************************************************************/
	void convert_steers_vel_to_robot_vel(const DoubleSteersVelInfo steersVelInfo, const float wheel_dAxisLength, TeabotRobotVelInfo& robotInfo,bool b_SteerPositiveRecog);
}
#endif
