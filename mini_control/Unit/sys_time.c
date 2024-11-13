#include "sys_time.h"


void sys_delay_us(uint16_t us)
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

void sys_delay_ms(uint16_t ms)
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

uint32_t sys_getSys_us(void)
{
  volatile uint32_t tick = HAL_GetTick();
  volatile uint32_t val  = SysTick->VAL;
  
  return tick * 1000 + (SysTick->LOAD+1 - val)*1000/HAL_RCC_GetSysClockFreq();
}

uint32_t sys_getSys_ms(void)
{
  return sys_getSys_us()/1000;
}

uint32_t sys_getSys_s(void)
{
  return sys_getSys_ms()/1000;
}