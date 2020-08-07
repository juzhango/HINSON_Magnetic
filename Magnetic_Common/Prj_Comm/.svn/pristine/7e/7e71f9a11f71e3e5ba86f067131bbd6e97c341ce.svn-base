#ifndef _ROS_SERVICE_HandshakeUpAndDown_h
#define _ROS_SERVICE_HandshakeUpAndDown_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

static const char HANDSHAKEUPANDDOWN[] = "syscore_msgs/HandshakeUpAndDown";

  class HandshakeUpAndDownRequest : public ros::Msg
  {
    public:
      int32_t RobotID;

    HandshakeUpAndDownRequest():
      RobotID(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_RobotID;
      u_RobotID.real = this->RobotID;
      *(outbuffer + offset + 0) = (u_RobotID.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_RobotID.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_RobotID.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_RobotID.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->RobotID);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_RobotID;
      u_RobotID.base = 0;
      u_RobotID.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_RobotID.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_RobotID.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_RobotID.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->RobotID = u_RobotID.real;
      offset += sizeof(this->RobotID);
     return offset;
    }

    const char * getType(){ return HANDSHAKEUPANDDOWN; };
    const char * getMD5(){ return "4a9402b8eacf92cd53fc32f6c11be65c"; };

  };

  class HandshakeUpAndDownResponse : public ros::Msg
  {
    public:
      int32_t RobotID;

    HandshakeUpAndDownResponse():
      RobotID(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_RobotID;
      u_RobotID.real = this->RobotID;
      *(outbuffer + offset + 0) = (u_RobotID.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_RobotID.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_RobotID.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_RobotID.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->RobotID);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_RobotID;
      u_RobotID.base = 0;
      u_RobotID.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_RobotID.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_RobotID.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_RobotID.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->RobotID = u_RobotID.real;
      offset += sizeof(this->RobotID);
     return offset;
    }

    const char * getType(){ return HANDSHAKEUPANDDOWN; };
    const char * getMD5(){ return "4a9402b8eacf92cd53fc32f6c11be65c"; };

  };

  class HandshakeUpAndDown {
    public:
    typedef HandshakeUpAndDownRequest Request;
    typedef HandshakeUpAndDownResponse Response;
  };

}
#endif
