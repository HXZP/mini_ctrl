#include "drv_led.h"


Led_Config led1_Conf[5] = 
{
  {"0",1,0,0},
  {"A0A",2,0,1},
  {"123456789A98765432100000000000000000000000000",10,0,1},  
  {"123456789A",2,0,1},
  
  {"0",0,0,0},
};

Led_Config led2_Conf[5] = 
{
  {"0",1,0,0},
  {"AA0",2,0,1},
  {"00000000000123456789A987654321000000000000000",10,0,1},  
  {"123456789A",2,0,1},
  
  {"0",0,0,0},
};

Led_Config led3_Conf[5] = 
{
  {"0",1,0,0},  
  {"0AA",2,0,1},
  {"0000000000000000000000123456789A9876543210000",10,0,1},  
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

void Drv_Led_Init(void)
{
  hxzp_Led_init(&led1);
  hxzp_Led_init(&led2);
  hxzp_Led_init(&led3);
}
