#ifndef _ROS_syscore_msgs_TeabotControl_h
#define _ROS_syscore_msgs_TeabotControl_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace syscore_msgs
{

  class TeabotControl : public ros::Msg
  {
    public:
      uint32_t RobotID;
      uint32_t CmdID;
      uint8_t items_length;
      uint32_t st_items;
      uint32_t * items;
      uint8_t data_length;
      uint8_t st_data;
      uint8_t * data;

    TeabotControl():
      RobotID(0),
      CmdID(0),
      items_length(0), items(NULL),
      data_length(0), data(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->RobotID >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->RobotID >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->RobotID >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->RobotID >> (8 * 3)) & 0xFF;
      offset += sizeof(this->RobotID);
      *(outbuffer + offset + 0) = (this->CmdID >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->CmdID >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->CmdID >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->CmdID >> (8 * 3)) & 0xFF;
      offset += sizeof(this->CmdID);
      *(outbuffer + offset++) = items_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < items_length; i++){
      *(outbuffer + offset + 0) = (this->items[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->items[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->items[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->items[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->items[i]);
      }
      *(outbuffer + offset++) = data_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < data_length; i++){
      *(outbuffer + offset + 0) = (this->data[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->RobotID =  ((uint32_t) (*(inbuffer + offset)));
      this->RobotID |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->RobotID |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->RobotID |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->RobotID);
      this->CmdID =  ((uint32_t) (*(inbuffer + offset)));
      this->CmdID |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->CmdID |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->CmdID |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->CmdID);
      uint8_t items_lengthT = *(inbuffer + offset++);
      if(items_lengthT > items_length)
        this->items = (uint32_t*)realloc(this->items, items_lengthT * sizeof(uint32_t));
      offset += 3;
      items_length = items_lengthT;
      for( uint8_t i = 0; i < items_length; i++){
      this->st_items =  ((uint32_t) (*(inbuffer + offset)));
      this->st_items |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->st_items |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->st_items |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->st_items);
        memcpy( &(this->items[i]), &(this->st_items), sizeof(uint32_t));
      }
      uint8_t data_lengthT = *(inbuffer + offset++);
      if(data_lengthT > data_length)
        this->data = (uint8_t*)realloc(this->data, data_lengthT * sizeof(uint8_t));
      offset += 3;
      data_length = data_lengthT;
      for( uint8_t i = 0; i < data_length; i++){
      this->st_data =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_data);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(uint8_t));
      }
     return offset;
    }

    const char * getType(){ return "syscore_msgs/TeabotControl"; };
    const char * getMD5(){ return "6a56412f7e7fe92c45fd14fb2b6809f1"; };

  };

}
#endif