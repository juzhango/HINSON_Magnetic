#ifndef _ROS_syscore_msgs_SafeSensor_h
#define _ROS_syscore_msgs_SafeSensor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class SafeSensor : public ros::Msg
  {
    public:
      uint8_t kind;
      uint16_t position;
      uint8_t status;
      int16_t data;

    SafeSensor():
      kind(0),
      position(0),
      status(0),
      data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->kind >> (8 * 0)) & 0xFF;
      offset += sizeof(this->kind);
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
      this->kind =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->kind);
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

    const char * getType(){ return "syscore_msgs/SafeSensor"; };
    const char * getMD5(){ return "c26eee8fac6b42b004fa9f58ec37f7d0"; };

  };

}
#endif