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
  // ���ļ��Զ�ȡ
  res = f_open(&SDFile, "en16x16.FON", FA_READ);
  if (res == FR_OK) {
      // ��ȡ����
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
  printf��ӡ�ض���
  ����
  debugprintf
  rtt
  lcd��Ļ
*/
int fputc(int ch, FILE *f)//�����ض���
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
  ��ʱ����
  stm32ϵͳʱ����24λ����ʱ��tickʱ��
  ��¼��һ�ε�ʱ�䣬������ʱ�������һ��������������ۼ�ʱ���0xFFFFFF


  ��ȡϵͳ����ʱ��
  ͨ��ms��ʱ��ת����tick���ټ��ϵ�ǰ���е�tick������ȥƵ�ʵõ�ϵͳ΢������ʱ��
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
  1.ִ�е����ȼ������̨��Ҫ��ͣ����Ĺ��ܴ���
  2.����ϵͳ����ԣ�����ں�ִ�п�������ʱ��Խ����ʾ�ں�Խ���У�
  3.�����������õ��͹���ģʽ��Ticklessģʽ��
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

