#include "drv_init.h"



void Drv_Init(void)
{
  Drv_Led_Init();  
  Drv_Key_Init();
  Drv_Lcd_Init();
  
  Drv_Usart_Init();
  
  cm_backtrace_init("mini_control","1.0","1.0");
}

