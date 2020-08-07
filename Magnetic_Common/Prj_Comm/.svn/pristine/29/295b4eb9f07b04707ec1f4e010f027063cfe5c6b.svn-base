#ifndef _ROS_syscore_msgs_Magnetic_h
#define _ROS_syscore_msgs_Magnetic_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class Magnetic : public ros::Msg
  {
    public:
      uint8_t position;
      uint8_t stripe;
      int8_t diffmm;
      uint8_t bitcnt;
      uint8_t width;
      uint16_t bits;

    Magnetic():
      position(0),
      stripe(0),
      diffmm(0),
      bitcnt(0),
      width(0),
      bits(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->position >> (8 * 0)) & 0xFF;
      offset += sizeof(this->position);
      *(outbuffer + offset + 0) = (this->stripe >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stripe);
      union {
        int8_t real;
        uint8_t base;
      } u_diffmm;
      u_diffmm.real = this->diffmm;
      *(outbuffer + offset + 0) = (u_diffmm.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->diffmm);
      *(outbuffer + offset + 0) = (this->bitcnt >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bitcnt);
      *(outbuffer + offset + 0) = (this->width >> (8 * 0)) & 0xFF;
      offset += sizeof(this->width);
      *(outbuffer + offset + 0) = (this->bits >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bits >> (8 * 1)) & 0xFF;
      offset += sizeof(this->bits);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->position =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->position);
      this->stripe =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->stripe);
      union {
        int8_t real;
        uint8_t base;
      } u_diffmm;
      u_diffmm.base = 0;
      u_diffmm.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->diffmm = u_diffmm.real;
      offset += sizeof(this->diffmm);
      this->bitcnt =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->bitcnt);
      this->width =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->width);
      this->bits =  ((uint16_t) (*(inbuffer + offset)));
      this->bits |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->bits);
     return offset;
    }

    const char * getType(){ return "syscore_msgs/Magnetic"; };
    const char * getMD5(){ return "cbd75d8aaa3d2c4c1e2a249fbc3a6960"; };

  };

}
#endif