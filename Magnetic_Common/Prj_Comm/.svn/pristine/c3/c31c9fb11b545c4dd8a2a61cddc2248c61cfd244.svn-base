#ifndef _ROS_syscore_msgs_SwitchIO_h
#define _ROS_syscore_msgs_SwitchIO_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class SwitchIO : public ros::Msg
  {
    public:
      uint32_t Switch;
      uint32_t IO;
      uint32_t Ex;

    SwitchIO():
      Switch(0),
      IO(0),
      Ex(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->Switch >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Switch >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Switch >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Switch >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Switch);
      *(outbuffer + offset + 0) = (this->IO >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->IO >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->IO >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->IO >> (8 * 3)) & 0xFF;
      offset += sizeof(this->IO);
      *(outbuffer + offset + 0) = (this->Ex >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Ex >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Ex >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Ex >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Ex);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->Switch =  ((uint32_t) (*(inbuffer + offset)));
      this->Switch |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->Switch |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->Switch |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->Switch);
      this->IO =  ((uint32_t) (*(inbuffer + offset)));
      this->IO |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->IO |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->IO |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->IO);
      this->Ex =  ((uint32_t) (*(inbuffer + offset)));
      this->Ex |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->Ex |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->Ex |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->Ex);
     return offset;
    }

    const char * getType(){ return "syscore_msgs/SwitchIO"; };
    const char * getMD5(){ return "6174c30839c27cf1971c1de98f8b651f"; };

  };

}
#endif