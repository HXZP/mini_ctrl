#include "delay.h"


void delay_us(uint16_t us)
{
  uint32_t tick = HAL_RCC_GetSysClockFreq() / 1000000  * us ;
  
  uint32_t tick_pre = SysTick->VAL;
  
  uint32_t tick_record;
  
  while(1)
  {
      
    
      if(SysTick->VAL > tick_pre)
      {
          tick_record += 0xFFFFFF + tick_pre - SysTick->VAL;
      }
      else
      {
          tick_record += tick_pre - SysTick->VAL;
      }
      
      tick_pre = SysTick->VAL;
      
      if(tick_record > tick)
      {
          break;
      }
  }
}

void delay_ms(uint16_t ms)
{
  uint32_t tick = HAL_RCC_GetSysClockFreq() / 1000  * ms ;
  
  uint32_t tick_pre = SysTick->VAL;
  
  uint32_t tick_record;
  
  while(1)
  {

      if(SysTick->VAL > tick_pre)
      {
          tick_record += 0xFFFFFF + tick_pre - SysTick->VAL;
      }
      else
      {
          tick_record += tick_pre - SysTick->VAL;
      }
      
      tick_pre = SysTick->VAL;
      
      if(tick_record > tick)
      {
          break;
      }
  }
}


