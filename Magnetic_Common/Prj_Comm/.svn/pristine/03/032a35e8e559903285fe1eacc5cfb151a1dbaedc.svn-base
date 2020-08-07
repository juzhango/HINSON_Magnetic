#ifndef _ROS_syscore_msgs_Magnetics_h
#define _ROS_syscore_msgs_Magnetics_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "syscore_msgs/Magnetic.h"

namespace syscore_msgs
{

  class Magnetics : public ros::Msg
  {
    public:
      bool isStopped;
      uint8_t layout_length;
      syscore_msgs::Magnetic st_layout;
      syscore_msgs::Magnetic * layout;

    Magnetics():
      isStopped(0),
      layout_length(0), layout(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_isStopped;
      u_isStopped.real = this->isStopped;
      *(outbuffer + offset + 0) = (u_isStopped.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->isStopped);
      *(outbuffer + offset++) = layout_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < layout_length; i++){
      offset += this->layout[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_isStopped;
      u_isStopped.base = 0;
      u_isStopped.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->isStopped = u_isStopped.real;
      offset += sizeof(this->isStopped);
      uint8_t layout_lengthT = *(inbuffer + offset++);
      if(layout_lengthT > layout_length)
        this->layout = (syscore_msgs::Magnetic*)realloc(this->layout, layout_lengthT * sizeof(syscore_msgs::Magnetic));
      offset += 3;
      layout_length = layout_lengthT;
      for( uint8_t i = 0; i < layout_length; i++){
      offset += this->st_layout.deserialize(inbuffer + offset);
        memcpy( &(this->layout[i]), &(this->st_layout), sizeof(syscore_msgs::Magnetic));
      }
     return offset;
    }

    const char * getType(){ return "syscore_msgs/Magnetics"; };
    const char * getMD5(){ return "6644dacd5231b378a000fe4f702d717c"; };

  };

}
#endif