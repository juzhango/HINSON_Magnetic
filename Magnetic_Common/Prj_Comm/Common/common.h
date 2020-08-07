#ifndef __COMMON_H
#define __COMMON_H
#include "stm32f4xx.h"

//////////////////////////////////////////////////////////////////////////////////
//0,不支持ucos
//1,支持ucos
//#define SYSTEM_SUPPORT_UCOS		1	//定义系统文件夹是否支持UCOS

typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;

typedef struct
{
    u16 data0: 1;
    u16 data1: 1;
    u16 data2: 1;
    u16 data3: 1;
    u16 data4: 1;
    u16 data5: 1;
    u16 data6: 1;
    u16 data7: 1;
    u16 data8: 1;
    u16 data9: 1;
    u16 data10: 1;
    u16 data11: 1;
    u16 data12: 1;
    u16 data13: 1;
    u16 data14: 1;
    u16 data15: 1;
} _gpio_group;


//0,不支持os
//1,支持os
#define SYSTEM_SUPPORT_OS		1		//定义系统文件夹是否支持uCOS


//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入

#define SYSCLK 168    //系统时钟

///////////////////设备通用定义/////////////////
#define MANU          0  //手动
#define AUTO          1  //自动
#define OFF           0  //关
#define ON            1  //开

struct _RobotParameters //机器人参数--结构体
{
    bool InitAll;//初始化所有参数
	bool InitMotors; //是否初始化电机控制器
    bool OpenObstacles;//开启壁障
    bool OpenBatteryCtrl;//开启电池保护控制权限，0：下位机 1：上位机
    bool OpenCentrifuge;//开启离心力纠正
    bool OpenMotorBrake;//开启电机制动
    bool OpenGrindDisc;//开启研磨盘
	bool OpenWaterPump;//开启水泵开关,默认关闭
	bool OpenSolenoidValve;//开启电磁阀开关，默认关闭
	bool OpenLED;//开启LED探照灯；//默认关闭
	bool WaterLevelSafe;
	bool OpenCharging;//开启充电功能
    bool OpenDebugLog;//开启日志监听
    u8 Agv_Sound_Alarm_Grade; //开启声音报警，0：不开启，1/2/3三种报警方式
    float WheelDiameterL;//机器人左轮直径
    float WheelDiameterR;//机器人右轮直径
    float WheelAxisLong;//机器人左右轮距
    float WheelAxisWide;//机器人前后轮距
    float BattryVoltage;//电池电压
    float BattryVoltagePercentage;//电池电量
    float BatteryCurrent;//电池电流
    float BatteryTemperature;//电池温度
    float MotorCurrentL;//左电机电流
    float MotorCurrentR;//右电机电流
};


struct _SafetySensorMsg//安全传感器消息--结构体
{
	u8 recently;//最高状态传感器的位置
	u8 breakdown_num;//故障个数
	u8* kind;//传感器类型
	u16* position;//各自位置
	u8* status;//各自状态
	u16* distance;//各自距离
	u8 number;	//传感器个数
	bool isStopped; //是否处于静止状态
};

struct _SonarMsg//声呐消息--结构体
{
	u8 recently;//最高状态传感器的位置
	u8 breakdown_num;//故障个数
	u16* position;//各自位置
	u8* status;//各自状态
	u16* distance;//各自距离
	u8 number;	//传感器个数
	bool isStopped; //是否处于静止状态
};



struct _MagneticsMsg//磁传感器消息--结构体
{
	u8 number;	//传感器个数
	u8* position;//方位
	u8* stripe;//是否检测到磁条
	int8_t* diffmm;//偏移距离
	u8* bitcnt;//识别位数
	u8* width;	//磁条宽度
	u16* bits; //识别位数
	bool isStopped; //是否处于静止状态
};


struct _Robot_status//(0b1111 1111)//8个状态
{
	bool SVCMD_BaseControl_StateType_Standby; //待命状态（下位机启动完毕状态直接进入这个状态）
  bool SVCMD_BaseControl_StateType_Working;  //工作状态（电池电量存在多种情形）--------判断速度
  bool SVCMD_BaseControl_StateType_Error;  //故障状态（电池电量存在多种情形）
  bool SVCMD_BaseControl_StateType_Charging_Lowly; //低电量报警状态（此时机器人不在充电桩位置）
  bool SVCMD_BaseControl_StateType_Finding_Charging_Station;  //搜寻充电桩状态  是否在自动寻找充电桩函数	
  //以下三个一定在充电桩接触位
	bool SVCMD_BaseControl_StateType_Charging_Begin; //开始充电（此时机器人刚刚到达充电桩的位置，且处于充电中）充电点位置
  bool SVCMD_BaseControl_StateType_Charging_Middle; //电量冲到50%（此时机器人在充电桩的位置，并且已经充电到50%，可以作为应急使用）
  bool SVCMD_BaseControl_StateType_Charging_End; //充电结束（此时机器人在充电桩的位置，并且充满电）
};
struct _IMU_Msg
{
    uint8_t ID;
    int16_t AccRaw[3];//加速度
    int16_t GyoRaw[3];//角速度
    int16_t MagRaw[3];//地磁
    float Eular[3];
    float Quaternion[4];
};

enum _SONAR_POSITION//声呐位置
{
    Bottom_Before_left2 = 208,
    Bottom_Before_left1 = 209,
    Bottom_Before_middle = 210,
    Bottom_Before_right1 = 211,
    Bottom_Before_right2 = 212,
	
    Bottom_After_left2 = 218,
    Bottom_After_left1 = 219,
    Bottom_After_middle = 220,
    Bottom_After_right1 = 221,
    Bottom_After_right2 = 222,
	
    Bottom_Left_left2 = 228,
    Bottom_Left_left1 = 229,
    Bottom_Left_middle = 230,
    Bottom_Left_right1 = 231,
    Bottom_Left_right2 = 232,
	
    Bottom_Right_left2 = 238,
    Bottom_Right_left1 = 239,
    Bottom_Right_middle = 240,
    Bottom_Right_right1 = 241,
    Bottom_Right_right2 = 242,
};

//声呐状态
enum _SONAR_STATUS
{
    SAFETY = 0, //安全
    WARN = 1, //警告
    DANGEROUS = 2, //危险
    BREAKDOWN = 3, //故障
};
//控制协议
enum Interaction_protocol
{

};
//以下为汇编函数
void WFI_SET(void);		   //执行WFI指令
void INTX_DISABLE(void); //关闭所有中断
void INTX_ENABLE(void);	 //开启所有中断
void MSR_MSP(u32 addr);	 //设置堆栈地址


void GPIO_group_OUT(_gpio_group *group, u16 outdata);
void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size, u16 outdata);

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

void NVIC_Configuration(void);
void System_Init(void);

char * float2str(float val, int precision, char buf[]);
//无符号64位整形转字符串 多线程下不可用
char * uint64tostr(uint64_t val, char buf[]);
//无符号32位整形转字符串 多线程下不可用
char * uint32tostr(uint32_t val, char buf[]);
//无符号32位整形转字符串 多线程下不可用
char * int32tostr(int32_t val, char buf[]);
char *F2S(double d, int precision, char* str);
char *fun(char *s1, char *s2);
char* my_itoa(int value, char *str, int radix);
char *my_ftoa(double number, int ndigit, char *buf);
u16 CRC_CHECK(u8 *Buf, u8 len); //crc校验
void Float_To_Char(float f, uint8_t *s);
void Double_To_Char(double f, uint8_t *s);
float Uchar_To_Float(uint8_t *Byte);
double Uchar_To_Double(uint8_t *Byte);

/*

* 函数名：Get_ChipIDData
 * 描述  ：获取芯片ID
 * 输入  ：无
 * 输出  ：无
 * 说明  ：96位的ID是stm32唯一身份标识，可以以8bit、16bit、32bit读取
           提供了大端和小端两种表示方法
*/
u8* Get_ChipID_Data();

#endif





























