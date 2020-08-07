#ifndef _ROS_syscore_msgs_RFID_h
#define _ROS_syscore_msgs_RFID_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class RFID : public ros::Msg
  {
    public:
      bool isStopped;
      uint8_t position;
      uint64_t rfid;

    RFID():
      isStopped(0),
      position(0),
      rfid(0)
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
      *(outbuffer + offset + 0) = (this->position >> (8 * 0)) & 0xFF;
      offset += sizeof(this->position);
      union {
        uint64_t real;
        uint32_t base;
      } u_rfid;
      u_rfid.real = this->rfid;
      *(outbuffer + offset + 0) = (u_rfid.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rfid.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rfid.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rfid.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rfid);
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
      this->position =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->position);
      union {
        uint64_t real;
        uint32_t base;
      } u_rfid;
      u_rfid.base = 0;
      u_rfid.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rfid.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rfid.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rfid.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rfid = u_rfid.real;
      offset += sizeof(this->rfid);
     return offset;
    }

    const char * getType(){ return "syscore_msgs/RFID"; };
    const char * getMD5(){ return "4075151c131d3b0f55511a63f52cc097"; };

  };

}
#endif