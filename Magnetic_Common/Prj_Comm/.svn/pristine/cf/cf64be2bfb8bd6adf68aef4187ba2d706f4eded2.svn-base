#ifndef _ROS_syscore_msgs_Sonar_h
#define _ROS_syscore_msgs_Sonar_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class Sonar : public ros::Msg
  {
    public:
      uint16_t position;
      uint8_t status;
      int16_t data;

    Sonar():
      position(0),
      status(0),
      data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->position >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->position >> (8 * 1)) & 0xFF;
      offset += sizeof(this->position);
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      union {
        int16_t real;
        uint16_t base;
      } u_data;
      u_data.real = this->data;
      *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_data.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->position =  ((uint16_t) (*(inbuffer + offset)));
      this->position |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->position);
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
      union {
        int16_t real;
        uint16_t base;
      } u_data;
      u_data.base = 0;
      u_data.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_data.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->data = u_data.real;
      offset += sizeof(this->data);
     return offset;
    }

    const char * getType(){ return "syscore_msgs/Sonar"; };
    const char * getMD5(){ return "f0aec4180081043ebfecd2b1d2bc9359"; };

  };

}
#endif