#include "user_key.h"
#include "usbd_hid.h"

extern uint8_t refresh;
HID_MOUSE_Report_t report;

extern USBD_HandleTypeDef hUsbDeviceFS;

/**
  * @brief  ?????????
  * @param  pdev: USB?υτ???
  * @param  buttons: ?????
  * @param  x: X?????
  * @param  y: Y?????
  * @param  wheel: ???????
  * @retval USBD??
  */
uint8_t USBD_HID_SendMouseReport(HID_MOUSE_Report_t *report)
{
  return USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)report, sizeof(report), 1);
}


void Key_Event_CW(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
		report.x = 0;
      break;

    case KEY_PRESS:
		report.x = 1;
      hxzp_Led_piece("W0","157AAAAAAAA9876543210",2,1,0,0);
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

void Key_Event_CCW(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
		report.x = 0;
      break;

    case KEY_PRESS:
		report.x = -1;
      hxzp_Led_piece("W2","157AAAAAAAA9876543210",2,1,0,0);
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

void Key_Event_PUSH(uint8_t state)
{
	uint8_t key_report[8] = {0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00};
  switch(state)
  {
    case KEY_IDLE:
    memset(key_report, 0, sizeof(key_report));
    USBD_HID_SendReport(&hUsbDeviceFS, key_report, 8, 0);		
      break;

    case KEY_PRESS:
		
		USBD_HID_SendReport(&hUsbDeviceFS, key_report, 8, 0);		
		hxzp_Led_piece("W0","00000000000123456789A987654321000000000000000",2,1,0,0);
		hxzp_Led_piece("W1","123456789A98765432100000000000000000000000000",2,1,0,0);
		hxzp_Led_piece("W2","00000000000123456789A987654321000000000000000",2,1,0,0);
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

void Key_Event_KEY1(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
		report.buttons.left = 0;
      break;

    case KEY_PRESS:
		report.buttons.left = 1;
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
		report.buttons.right = 0;
      break;

    case KEY_PRESS:
		report.buttons.right = 1;
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
  
  keyboradTaskHandle = osThreadNew(StartkeyboradTask, NULL, &keyboradTask_attributes);
}












