#include "drv_key.h"


Key_Config key_config_default = 
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

uint8_t Key_Read_ccw(void)
{
  return HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5);
}

uint8_t Key_Read_push(void)
{
  return HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6);
}

uint8_t Key_Read_key1(void)
{
  return HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
}

uint8_t Key_Read_key2(void)
{
  return HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin);
}

Key key_cw = 
{
  .name = "CW",
  
  .Config = &key_config_default,
  .ConfigNum = sizeof(key_config_default)/sizeof(Key_Config),
    
  .Read = Key_Read_cw,
};



Key key_ccw = 
{
  .name = "CCW",
  
  .Config = &key_config_default,
  .ConfigNum = sizeof(key_config_default)/sizeof(Key_Config),
    
  .Read = Key_Read_ccw,
};



Key key_push = 
{
  .name = "PUSH",
  
  .Config = &key_config_default,
  .ConfigNum = sizeof(key_config_default)/sizeof(Key_Config),
    
  .Read = Key_Read_push,
};

Key key_key1 = 
{
  .name = "KEY1",
  
  .Config = &key_config_default,
  .ConfigNum = sizeof(key_config_default)/sizeof(Key_Config),
    
  .Read = Key_Read_key1,
};

Key key_key2 = 
{
  .name = "KEY2",
  
  .Config = &key_config_default,
  .ConfigNum = sizeof(key_config_default)/sizeof(Key_Config),
    
  .Read = Key_Read_key2,
};


void Drv_Key_Init(void)
{
  hxzp_Key_init(&key_cw);
  hxzp_Key_init(&key_ccw);
  hxzp_Key_init(&key_push);
  hxzp_Key_init(&key_key1);
  hxzp_Key_init(&key_key2);  
}












