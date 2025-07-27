#include "user_key.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
HID_MOUSE_Report_t report;

/**
  * @brief  发送鼠标报告
  * @param  pdev: USB设备句柄
  * @param  buttons: 按钮状态
  * @param  x: X轴移动
  * @param  y: Y轴移动
  * @param  wheel: 滚轮移动
  * @retval USBD状态
  */
uint8_t USBD_HID_SendMouseReport(HID_MOUSE_Report_t *report)
{
  return USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)report, sizeof(report), 1);
}










extern uint8_t refresh;

void Key_Event_CW(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      report.x = 0;
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","157AAAAAAAA9876543210",2,1,0,0);
      break;
    
    case KEY_DOWN:
      report.x = 64;
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

void Key_Event_CCW(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      report.x = 0;
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W2","157AAAAAAAA9876543210",2,1,0,0);
      break;
    
    case KEY_DOWN:
      report.x = -64;
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

void Key_Event_PUSH(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","00000000000123456789A987654321000000000000000",2,1,0,0);
      hxzp_Led_piece("W1","123456789A98765432100000000000000000000000000",2,1,0,0);
      hxzp_Led_piece("W2","00000000000123456789A987654321000000000000000",2,1,0,0);
      break;
    
    case KEY_DOWN:
      report.buttons.left = 1;
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      report.buttons.right = 1;
      break;    
  
  }
}

void Key_Event_KEY1(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","0000000000000000000000123456789A9876543210000",2,1,0,0);
      hxzp_Led_piece("W1","00000000000123456789A987654321000000000000000",2,1,0,0);
      hxzp_Led_piece("W2","123456789A98765432100000000000000000000000000",2,1,0,0);
      break;
    
    case KEY_DOWN:
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

void Key_Event_KEY2(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","123456789A98765432100000000000000000000000000",2,1,0,0);
      hxzp_Led_piece("W1","00000000000123456789A987654321000000000000000",2,1,0,0);
      hxzp_Led_piece("W2","0000000000000000000000123456789A9876543210000",2,1,0,0);    
      break;
    
    case KEY_DOWN:
      break;

    case KEY_DOWN_LONG:
      break;

    case KEY_DOWN_HOLD:
      break;

    case KEY_UP:
      break;

    case KEY_DOUBLE:
      break;    
  
  }
}

osThreadId_t keyboradTaskHandle;
const osThreadAttr_t keyboradTask_attributes = {
  .name = "keyboradTask",
  .stack_size = 128 * 1,
  .priority = (osPriority_t) osPriorityNormal,
};

void StartkeyboradTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    
  for(;;)
  {
    USBD_HID_SendMouseReport(&report);
    report.buttons.left = 0;
    report.buttons.right = 0;
    report.buttons.middle = 0;
    
    osDelay(50);
  }
  /* USER CODE END StartDefaultTask */
}

void User_Key_Init(void)
{
  hxzp_Key_eventReg("CW",Key_Event_CW);
  hxzp_Key_eventReg("CCW",Key_Event_CCW);
  hxzp_Key_eventReg("PUSH",Key_Event_PUSH);
  hxzp_Key_eventReg("KEY1",Key_Event_KEY1);
  hxzp_Key_eventReg("KEY2",Key_Event_KEY2);  
  
//  keyboradTaskHandle = osThreadNew(StartkeyboradTask, NULL, &keyboradTask_attributes);
}












