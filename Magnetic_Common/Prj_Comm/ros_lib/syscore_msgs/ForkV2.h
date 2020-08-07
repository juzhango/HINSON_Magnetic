#ifndef _ROS_syscore_msgs_ForkV2_h
#define _ROS_syscore_msgs_ForkV2_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class ForkV2 : public ros::Msg
  {
    public:
      bool isStopped;
      uint8_t CtrlKind;
      float CtrlSpeed;
      float CtrlValue;
      uint8_t LoadLevel;
      bool RequireTilt;

    ForkV2():
      isStopped(0),
      CtrlKind(0),
      CtrlSpeed(0),
      CtrlValue(0),
      LoadLevel(0),
      RequireTilt(0)
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
      *(outbuffer + offset + 0) = (this->CtrlKind >> (8 * 0)) & 0xFF;
      offset += sizeof(this->CtrlKind);
      union {
        float real;
        uint32_t base;
      } u_CtrlSpeed;
      u_CtrlSpeed.real = this->CtrlSpeed;
      *(outbuffer + offset + 0) = (u_CtrlSpeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_CtrlSpeed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_CtrlSpeed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_CtrlSpeed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->CtrlSpeed);
      union {
        float real;
        uint32_t base;
      } u_CtrlValue;
      u_CtrlValue.real = this->CtrlValue;
      *(outbuffer + offset + 0) = (u_CtrlValue.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_CtrlValue.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_CtrlValue.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_CtrlValue.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->CtrlValue);
      *(outbuffer + offset + 0) = (this->LoadLevel >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LoadLevel);
      union {
        bool real;
        uint8_t base;
      } u_RequireTilt;
      u_RequireTilt.real = this->RequireTilt;
      *(outbuffer + offset + 0) = (u_RequireTilt.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->RequireTilt);
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
      this->CtrlKind =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->CtrlKind);
      union {
        float real;
        uint32_t base;
      } u_CtrlSpeed;
      u_CtrlSpeed.base = 0;
      u_CtrlSpeed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_CtrlSpeed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_CtrlSpeed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_CtrlSpeed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->CtrlSpeed = u_CtrlSpeed.real;
      offset += sizeof(this->CtrlSpeed);
      union {
        float real;
        uint32_t base;
      } u_CtrlValue;
      u_CtrlValue.base = 0;
      u_CtrlValue.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_CtrlValue.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_CtrlValue.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_CtrlValue.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->CtrlValue = u_CtrlValue.real;
      offset += sizeof(this->CtrlValue);
      this->LoadLevel =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LoadLevel);
      union {
        bool real;
        uint8_t base;
      } u_RequireTilt;
      u_RequireTilt.base = 0;
      u_RequireTilt.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->RequireTilt = u_RequireTilt.real;
      offset += sizeof(this->RequireTilt);
     return offset;
    }

    const char * getType(){ return "syscore_msgs/ForkV2"; };
    const char * getMD5(){ return "f657e9435c3419cef70efdabd9f86f15"; };

  };

}
#endif