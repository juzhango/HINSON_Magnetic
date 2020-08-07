#ifndef _ROS_syscore_msgs_Fork_h
#define _ROS_syscore_msgs_Fork_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class Fork : public ros::Msg
  {
    public:
      bool isStopped;
      uint8_t LiftKind;
      float LiftSpeed;
      float LiftHeight;
      uint8_t MoveKind;
      float MoveSpeed;
      float MoveDist;

    Fork():
      isStopped(0),
      LiftKind(0),
      LiftSpeed(0),
      LiftHeight(0),
      MoveKind(0),
      MoveSpeed(0),
      MoveDist(0)
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
      *(outbuffer + offset + 0) = (this->LiftKind >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LiftKind);
      union {
        float real;
        uint32_t base;
      } u_LiftSpeed;
      u_LiftSpeed.real = this->LiftSpeed;
      *(outbuffer + offset + 0) = (u_LiftSpeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_LiftSpeed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_LiftSpeed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_LiftSpeed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->LiftSpeed);
      union {
        float real;
        uint32_t base;
      } u_LiftHeight;
      u_LiftHeight.real = this->LiftHeight;
      *(outbuffer + offset + 0) = (u_LiftHeight.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_LiftHeight.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_LiftHeight.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_LiftHeight.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->LiftHeight);
      *(outbuffer + offset + 0) = (this->MoveKind >> (8 * 0)) & 0xFF;
      offset += sizeof(this->MoveKind);
      union {
        float real;
        uint32_t base;
      } u_MoveSpeed;
      u_MoveSpeed.real = this->MoveSpeed;
      *(outbuffer + offset + 0) = (u_MoveSpeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_MoveSpeed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_MoveSpeed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_MoveSpeed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->MoveSpeed);
      union {
        float real;
        uint32_t base;
      } u_MoveDist;
      u_MoveDist.real = this->MoveDist;
      *(outbuffer + offset + 0) = (u_MoveDist.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_MoveDist.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_MoveDist.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_MoveDist.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->MoveDist);
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
      this->LiftKind =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->LiftKind);
      union {
        float real;
        uint32_t base;
      } u_LiftSpeed;
      u_LiftSpeed.base = 0;
      u_LiftSpeed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_LiftSpeed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_LiftSpeed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_LiftSpeed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->LiftSpeed = u_LiftSpeed.real;
      offset += sizeof(this->LiftSpeed);
      union {
        float real;
        uint32_t base;
      } u_LiftHeight;
      u_LiftHeight.base = 0;
      u_LiftHeight.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_LiftHeight.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_LiftHeight.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_LiftHeight.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->LiftHeight = u_LiftHeight.real;
      offset += sizeof(this->LiftHeight);
      this->MoveKind =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->MoveKind);
      union {
        float real;
        uint32_t base;
      } u_MoveSpeed;
      u_MoveSpeed.base = 0;
      u_MoveSpeed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_MoveSpeed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_MoveSpeed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_MoveSpeed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->MoveSpeed = u_MoveSpeed.real;
      offset += sizeof(this->MoveSpeed);
      union {
        float real;
        uint32_t base;
      } u_MoveDist;
      u_MoveDist.base = 0;
      u_MoveDist.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_MoveDist.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_MoveDist.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_MoveDist.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->MoveDist = u_MoveDist.real;
      offset += sizeof(this->MoveDist);
     return offset;
    }

    const char * getType(){ return "syscore_msgs/Fork"; };
    const char * getMD5(){ return "35b54f8df546ebd3ef2b2dcb829f1d59"; };

  };

}
#endif