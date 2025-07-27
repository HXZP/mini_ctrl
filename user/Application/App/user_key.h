#ifndef USER_KEY_H
#define USER_KEY_H

#include "drv_key.h"
#include "usbd_hid.h"

typedef struct {
  
  struct 
  {
    uint8_t left:1;
    uint8_t right:1;
    uint8_t middle:1;
    uint8_t reserve:5;
  }buttons;// 按钮状态 (bit0:左键, bit1:右键, bit2:中键)
  
  int8_t x;          // X轴移动 (-127到127)
  int8_t y;          // Y轴移动 (-127到127)
  int8_t wheel;      // 滚轮移动 (-127到127)
} HID_MOUSE_Report_t;

void User_Key_Init(void);





#endif

