#include "FreeRTOS.h"
#include "hxzp_list.h"
#include "cmsis_os.h"
#include "main.h"

#include "hxzp_led.h"

/*

led设计 通过外部传入亮度表以及读表速度 加入优先级 加入在忙状态

*/


Led_Config led1_Conf[3] = 
{
  {"A0",5,0,1},
  {"123456789A98765432",1,0,1},  
  {"123456789A",2,0,1},
};

Led_Config led2_Conf[3] = 
{
  {"A0",5,0,1},
  {"56789A987654321234",1,0,1},  
  {"123456789A",2,0,1},
};

Led_Config led3_Conf[3] = 
{
  {"A0",5,0,1},
  {"89A987654321234567",1,0,1},  
  {"123456789A",2,0,1},
};

void Led1_Write(uint8_t state)
{
  HAL_GPIO_WritePin(W0_GPIO_Port,W0_Pin,state);
}

void Led2_Write(uint8_t state)
{
  HAL_GPIO_WritePin(W1_GPIO_Port,W1_Pin,state);
}

void Led3_Write(uint8_t state)
{
  HAL_GPIO_WritePin(W2_GPIO_Port,W2_Pin,state);
}

Led led1 = 
{
  .name = "W0",
  .Config = led1_Conf,
  .ConfigNum = sizeof(led1_Conf)/sizeof(Led_Config),
  .Write  = Led1_Write,
};

Led led2 = 
{
  .name = "W1",
  .Config = led2_Conf,
  .ConfigNum = sizeof(led1_Conf)/sizeof(Led_Config),
  .Write  = Led2_Write,
};

Led led3 = 
{
  .name = "W2",
  .Config = led3_Conf,
  .ConfigNum = sizeof(led1_Conf)/sizeof(Led_Config),
  .Write  = Led3_Write,
};

void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    
  hxzp_led_init(&led1);
  hxzp_led_init(&led2);
  hxzp_led_init(&led3);
  
  hxzp_led_set("W0",1);
  hxzp_led_set("W1",1);
  hxzp_led_set("W2",1);

  /* Infinite loop */
  for(;;)
  {
    /*hz = 1000/lenght*delay 人类25*/


    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}










