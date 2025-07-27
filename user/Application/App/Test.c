

#include "FreeRTOS.h"
#include "hxzp_list.h"
#include "cmsis_os.h"
#include "main.h"

#include "hxzp_led.h"
#include "hxzp_key.h"

#include "spi.h"
#include "usart.h"

#include "fatfs.h"
#include "sdio.h"

#include "usb_device.h"
//#include "usbd_cdc_if.h"

#include "system.h"

#include "task.h"

#include <stdlib.h>

#include <stdio.h>

#include "hxzp_st7789.h"
//#include "WouoUI_user.h"
//#include "WouoUI.h"

#include "usbd_hid.h"
/*

led设计 通过外部传入亮度表以及读表速度 加入优先级 加入在忙状态

*/
extern USBD_HandleTypeDef hUsbDeviceFS;
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    
  for(;;)
  {
    osDelay(1000);
    
    // 按下A键
//    uint8_t key_report[8] = {0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00};
//    USBD_HID_SendReport(&hUsbDeviceFS, key_report, 8, 0);

//    // 保持按下状态一段时间（可选）
//    HAL_Delay(50);  // 50ms按键持续时间

//    // 释放所有按键
//    memset(key_report, 0, sizeof(key_report));
//    USBD_HID_SendReport(&hUsbDeviceFS, key_report, 8, 0);
    
    uint8_t mouse_report[4] = {0x00, 20, 15, 0};
    USBD_HID_SendReport(&hUsbDeviceFS, mouse_report, 4, 1);    
    
  }
  /* USER CODE END StartDefaultTask */
}










