#ifndef _ROS_syscore_msgs_LSB110_h
#define _ROS_syscore_msgs_LSB110_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace syscore_msgs
{

  class LSB110 : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float Vertical_Deviation;
      float Pitch_Angle;
      float Roll_Angle;

    LSB110():
      header(),
      Vertical_Deviation(0),
      Pitch_Angle(0),
      Roll_Angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_Vertical_Deviation;
      u_Vertical_Deviation.real = this->Vertical_Deviation;
      *(outbuffer + offset + 0) = (u_Vertical_Deviation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Vertical_Deviation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Vertical_Deviation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Vertical_Deviation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Vertical_Deviation);
      union {
        float real;
        uint32_t base;
      } u_Pitch_Angle;
      u_Pitch_Angle.real = this->Pitch_Angle;
      *(outbuffer + offset + 0) = (u_Pitch_Angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Pitch_Angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Pitch_Angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Pitch_Angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Pitch_Angle);
      union {
        float real;
        uint32_t base;
      } u_Roll_Angle;
      u_Roll_Angle.real = this->Roll_Angle;
      *(outbuffer + offset + 0) = (u_Roll_Angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Roll_Angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Roll_Angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Roll_Angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Roll_Angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_Vertical_Deviation;
      u_Vertical_Deviation.base = 0;
      u_Vertical_Deviation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Vertical_Deviation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Vertical_Deviation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Vertical_Deviation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Vertical_Deviation = u_Vertical_Deviation.real;
      offset += sizeof(this->Vertical_Deviation);
      union {
        float real;
        uint32_t base;
      } u_Pitch_Angle;
      u_Pitch_Angle.base = 0;
      u_Pitch_Angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Pitch_Angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Pitch_Angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Pitch_Angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Pitch_Angle = u_Pitch_Angle.real;
      offset += sizeof(this->Pitch_Angle);
      union {
        float real;
        uint32_t base;
      } u_Roll_Angle;
      u_Roll_Angle.base = 0;
      u_Roll_Angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Roll_Angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Roll_Angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Roll_Angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Roll_Angle = u_Roll_Angle.real;
      offset += sizeof(this->Roll_Angle);
     return offset;
    }

    const char * getType(){ return "syscore_msgs/LSB110"; };
    const char * getMD5(){ return "74c0c137274144d33b2abe1b42934a6f"; };

  };

}
#endif