#ifndef _ROS_syscore_msgs_UWB_h
#define _ROS_syscore_msgs_UWB_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class UWB : public ros::Msg
  {
    public:
      float Position_x;
      float Position_y;

    UWB():
      Position_x(0),
      Position_y(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Position_x;
      u_Position_x.real = this->Position_x;
      *(outbuffer + offset + 0) = (u_Position_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Position_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Position_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Position_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Position_x);
      union {
        float real;
        uint32_t base;
      } u_Position_y;
      u_Position_y.real = this->Position_y;
      *(outbuffer + offset + 0) = (u_Position_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Position_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Position_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Position_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Position_y);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Position_x;
      u_Position_x.base = 0;
      u_Position_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Position_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Position_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Position_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Position_x = u_Position_x.real;
      offset += sizeof(this->Position_x);
      union {
        float real;
        uint32_t base;
      } u_Position_y;
      u_Position_y.base = 0;
      u_Position_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Position_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Position_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Position_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Position_y = u_Position_y.real;
      offset += sizeof(this->Position_y);
     return offset;
    }

    const char * getType(){ return "syscore_msgs/UWB"; };
    const char * getMD5(){ return "b46a1e43458f4c11d0cb4534d0f49823"; };

  };

}
#endif