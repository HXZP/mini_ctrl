#include "FreeRTOS.h"
#include "hxzp_list.h"
#include "cmsis_os.h"
#include "main.h"

#include "hxzp_led.h"
#include "hxzp_key.h"
/*

led设计 通过外部传入亮度表以及读表速度 加入优先级 加入在忙状态

*/


Led_Config led1_Conf[5] = 
{
  {"0",1,0,0},
  {"AA0",2,0,1},
  {"123456789A98765432",1,0,1},  
  {"123456789A",2,0,1},
  
  {"0",0,0,0},
};

Led_Config led2_Conf[5] = 
{
  {"0",1,0,0},
  {"0AA",2,0,1},
  {"56789A987654321234",1,0,1},  
  {"123456789A",2,0,1},
  
  {"0",0,0,0},
};

Led_Config led3_Conf[5] = 
{
  {"0",1,0,0},  
  {"A0A",2,0,1},
  {"89A987654321234567",1,0,1},  
  {"123456789A",2,0,1},
  
  {"0",0,0,0},  
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


Key_Config key_config_cw = 
{
  .debouncing_Time = 5,
  
  .down_Time = 1,
  .downlong_Time = 30,
  .downhold_Time = 50,
  .double_Time = 10, 

};

uint8_t Key_Read_cw(void)
{
  return HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7);
}

Key key_cw = 
{
  .name = "CW",
  
  .Config = &key_config_cw,
  .ConfigNum = sizeof(key_config_cw)/sizeof(Key_Config),
    
  .Read = Key_Read_cw,
};


Key_Config key_config_ccw = 
{
  .debouncing_Time = 5,
  
  .down_Time = 1,
  .downlong_Time = 30,
  .downhold_Time = 50,
  .double_Time = 10, 

};

uint8_t Key_Read_ccw(void)
{
  return HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5);
}

Key key_ccw = 
{
  .name = "CCW",
  
  .Config = &key_config_ccw,
  .ConfigNum = sizeof(key_config_ccw)/sizeof(Key_Config),
    
  .Read = Key_Read_ccw,
};


Key_Config key_config_push = 
{
  .debouncing_Time = 5,
  
  .down_Time = 1,
  .downlong_Time = 30,
  .downhold_Time = 50,
  .double_Time = 10, 

};

uint8_t Key_Read_push(void)
{
  return HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6);
}

Key key_push = 
{
  .name = "PUSH",
  
  .Config = &key_config_push,
  .ConfigNum = sizeof(key_config_push)/sizeof(Key_Config),
    
  .Read = Key_Read_push,
};

void Key_Event_CW(uint8_t state)
{
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W0","0123456789A9876543210",1,1,0,1);
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
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W2","0123456789A9876543210",1,1,0,1);
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
  switch(state)
  {
    case KEY_IDLE:
      break;

    case KEY_PRESS:
      hxzp_Led_piece("W1","0123456789A9876543210",1,1,0,1);
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


void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    
  hxzp_Led_init(&led1);
  hxzp_Led_init(&led2);
  hxzp_Led_init(&led3);
  
  hxzp_Key_init(&key_cw);
  hxzp_Key_init(&key_ccw);
  hxzp_Key_init(&key_push);
//  hxzp_Led_piece("W0","A0",1,1,1,0);
  
  hxzp_Led_set("W0",1);
  hxzp_Led_set("W1",1);
  hxzp_Led_set("W2",1);
  
  hxzp_Key_eventReg("CW",Key_Event_CW);
  hxzp_Key_eventReg("CCW",Key_Event_CCW);
  hxzp_Key_eventReg("PUSH",Key_Event_PUSH);
    
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










