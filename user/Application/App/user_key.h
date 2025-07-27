#ifndef USER_KEY_H
#define USER_KEY_H

#include "drv_key.h"



typedef struct {
  
  struct 
  {
    uint8_t left:1;
    uint8_t right:1;
    uint8_t middle:1;
    uint8_t reserve:5;
  }buttons;// ????? (bit0:???, bit1:???, bit2:?§Þ?)
  
  int8_t x;          // X????? (-127??127)
  int8_t y;          // Y????? (-127??127)
  int8_t wheel;      // ??????? (-127??127)
} HID_MOUSE_Report_t;


void User_Key_Init(void);





#endif

