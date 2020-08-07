#ifndef __SUPERCOREIMU_H__
#define __SUPERCOREIMU_H__

#include <stdint.h>
#include <stdbool.h>
#include "common.h"
#define MAX_PACKET_LEN          (128)
extern _IMU_Msg IMU;
typedef enum 
{
    kItemID =                   0x90,   /* user programed ID    size: 1 */
    kItemIPAdress =             0x92,   /* ip address           size: 4 */
    kItemAccRaw =               0xA0,   /* raw acc              size: 3x2 */
    kItemAccRawFiltered =       0xA1,   
    kItemAccDynamic =           0xA2,   
    kItemGyoRaw =               0xB0,   /* raw gyro             size: 3x2 */
    kItemGyoRawFiltered =       0xB1,   
    kItemMagRaw =               0xC0,   /* raw mag              size: 3x2 */
    kItemMagRawFiltered =       0xC1,   
    kItemAtdE =                 0xD0,   /* eular angle          size:3x2 */
    kItemAtdQ =                 0xD1,   /* att q,               size:4x4 */
    kItemTemp =                 0xE0,   
    kItemPressure =             0xF0,   /* pressure             size:1x4 */
    kItemEnd =                  0xFF,   
}ItemID_t;
void SuperCoreIMU_Init(uint32_t bound);
uint32_t Packet_Decode(uint8_t c);
bool parserIMU_9axisData(const uint8_t* bufff_data);
bool parserIMU_6axisData(const uint8_t* bufff_data);
bool parserIMUBuffer(const uint8_t* bufff_data, const uint16_t content_size);
bool SuperCoreIMUDataInit(bool _ImuInit);
void CorrectImuData();
#endif
