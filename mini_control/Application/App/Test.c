#include "FreeRTOS.h"
#include "hxzp_list.h"
#include "cmsis_os.h"
#include "main.h"

#include "hxzp_led.h"
#include "hxzp_key.h"
/*

led设计 通过外部传入亮度表以及读表速度 加入优先级 加入在忙状态

*/


void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    

//  hxzp_Led_piece("W0","A0",1,1,1,0);
  
  hxzp_Led_set("W0",2);
  hxzp_Led_set("W1",2);
  hxzp_Led_set("W2",2);
  

    
//  hxzp_Led_insert("W0",0);
//  hxzp_Led_insert("W1",0);
//  hxzp_Led_insert("W2",0);
  /* Infinite loop */
  for(;;)
  {
    /*hz = 1000/lenght*delay 人类25*/

    
    
    

    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}










