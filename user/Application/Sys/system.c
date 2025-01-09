#include "system.h"

#include "usart.h"

#include "usbd_cdc_if.h"

#include <stdarg.h>

#include "FreeRTOS.h"
#include "task.h"


#include "fatfs.h"
#include "sdio.h"
#include "hxzp_st7789.h"


#if 1//(SYSTEM_PRINTF_PORT == USING_PRINTF_LCD)  
static uint8_t sysLcdData;
static uint8_t sysLcdDataBuff[32] = {0};
static void sys_read_word_fileEn(uint8_t *data, uint16_t idex)
{
  FRESULT res;
  UINT br;
  // 打开文件以读取
  res = f_open(&SDFile, "en16x16.FON", FA_READ);
  if (res == FR_OK) {
      // 读取数据
      res = f_lseek(&SDFile,idex*16);
      res = f_read(&SDFile, data, 16, &br);
      res = f_close(&SDFile);
  }
}
void sys_lcd_printf(uint8_t ch)
{
  sys_read_word_fileEn(sysLcdDataBuff,(uint16_t)ch);

  if(ch == 96)
  {
    hxzp_Lcd_PrintLF();
    hxzp_Lcd_PrintCR();
  }
  else
  {
    hxzp_Lcd_Print(sysLcdDataBuff);
  }
  
  

//  hxzp_st7789_SetWord(sysLcdData,8,16,0,0,0xffff,0x0000);
}    
#endif




/*
  printf打印重定向
  串口
  debugprintf
  rtt
  lcd屏幕
*/
int fputc(int ch, FILE *f)//串口重定向
{
  
#if (SYSTEM_PRINTF_PORT == USING_PRINTF_UART)  
    HAL_UART_Transmit(&huart3,(uint8_t*)&ch,1,1000);
#endif
    
#if (SYSTEM_PRINTF_PORT == USING_PRINTF_LCD)  
    sys_lcd_printf((uint8_t)ch);
#endif
    return ch;
}

#if (SYSTEM_PRINTF_PORT == USING_PRINTF_USB)  

static uint8_t buff[1024];
void sys_usb_printf(const char *format, ...)
{
  va_list args;
  uint32_t length;

  va_start(args, format);
  length = vsnprintf((char *)buff, APP_TX_DATA_SIZE, (char *)format, args);
  va_end(args);
  CDC_Transmit_FS(buff, length);
}
#endif  


/*
  延时函数
  stm32系统时钟是24位倒计时的tick时钟
  记录上一次的时间，当本次时间大于上一次则发生了溢出，累计时间加0xFFFFFF


  获取系统运行时间
  通过ms的时间转换到tick数再加上当前运行的tick数，除去频率得到系统微秒运行时间
*/
void sys_delay_us(uint16_t us)
{
  uint32_t tick = SYSTEM_TIMER_FREQ_HZ / 1000000  * us ;
  
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
  uint32_t tick = SYSTEM_TIMER_FREQ_HZ / 1000  * ms ;
  
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
//  volatile uint32_t tick = SYSTEM_GET_TIME_MS;
//  volatile uint32_t val  = SysTick->VAL;
  
  return SYSTEM_GET_TIME_MS * 1000 + (SysTick->LOAD + 1 - SysTick->VAL) * 1000/SYSTEM_TIMER_FREQ_HZ;
}

uint32_t sys_getSys_ms(void)
{
  return sys_getSys_us()/1000;
}

uint32_t sys_getSys_s(void)
{
  return sys_getSys_ms()/1000;
}

#if 0
/*
  1.执行低优先级，或后台需要不停处理的功能代码
  2.测试系统处理裕量（内核执行空闲任务时间越长表示内核越空闲）
  3.将处理器配置到低功耗模式（Tickless模式）
*/
#if (USING_PRINTF_TASK_INFO == 1)

#define IDLEHOOK_TIME_MS 100
void vApplicationIdleHook(void)
{
  static uint32_t getMs = 0;
  
  if(sys_getSys_ms() - getMs > IDLEHOOK_TIME_MS)
  {
  
    char *buffer = (char*)malloc(256);
    vTaskList(buffer);
    
    printf("///////////////////////\r\n");
    printf("%s",buffer);
    
    
    free(buffer);
    
    getMs = sys_getSys_ms();
  }
}
#endif

#endif

