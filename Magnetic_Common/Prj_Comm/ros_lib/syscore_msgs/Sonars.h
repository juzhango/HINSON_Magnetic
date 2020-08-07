#ifndef _ROS_syscore_msgs_Sonars_h
#define _ROS_syscore_msgs_Sonars_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "syscore_msgs/Sonar.h"

namespace syscore_msgs
{

  class Sonars : public ros::Msg
  {
    public:
      uint16_t recently;
      uint8_t breakdown_num;
      bool isStopped;
      uint8_t layout_length;
      syscore_msgs::Sonar st_layout;
      syscore_msgs::Sonar * layout;

    Sonars():
      recently(0),
      breakdown_num(0),
      isStopped(0),
      layout_length(0), layout(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->recently >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->recently >> (8 * 1)) & 0xFF;
      offset += sizeof(this->recently);
      *(outbuffer + offset + 0) = (this->breakdown_num >> (8 * 0)) & 0xFF;
      offset += sizeof(this->breakdown_num);
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
      this->recently =  ((uint16_t) (*(inbuffer + offset)));
      this->recently |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->recently);
      this->breakdown_num =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->breakdown_num);
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
        this->layout = (syscore_msgs::Sonar*)realloc(this->layout, layout_lengthT * sizeof(syscore_msgs::Sonar));
      offset += 3;
      layout_length = layout_lengthT;
      for( uint8_t i = 0; i < layout_length; i++){
      offset += this->st_layout.deserialize(inbuffer + offset);
        memcpy( &(this->layout[i]), &(this->st_layout), sizeof(syscore_msgs::Sonar));
      }
     return offset;
    }

    const char * getType(){ return "syscore_msgs/Sonars"; };
    const char * getMD5(){ return "9be4acd7cfa45f390586cc088fa0965f"; };

  };

}
#endif