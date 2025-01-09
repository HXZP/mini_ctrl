#ifndef SYSTEM_H
#define SYSTEM_H

#include "stdint.h"
#include "stdlib.h"
#include <stdio.h>
#include "stm32f1xx_hal.h"

#include "board_config.h"

void sys_usb_printf(const char *format, ...);
#define USB_PRINTF(format, ...)               sys_usb_printf(format, ##__VA_ARGS__);


#ifndef SYSTEM_PRINTF_PORT
  #define SYSTEM_PRINTF_PORT 0
#endif


#if (SYSTEM_PRINTF_PORT == USING_PRINTF_UART || SYSTEM_PRINTF_PORT == USING_PRINTF_LCD)
#define LOG(format, ...)               printf(format, ##__VA_ARGS__);

#elif (SYSTEM_PRINTF_PORT == USING_PRINTF_USB)
#define LOG(format, ...)               USB_PRINTF(format, ##__VA_ARGS__);

#endif



#define SYSTEM_TIMER_FREQ_HZ HAL_RCC_GetSysClockFreq()
#define SYSTEM_GET_TIME_MS   HAL_GetTick()


void sys_delay_us(uint16_t us);
void sys_delay_ms(uint16_t ms);
uint32_t sys_getSys_us(void);
uint32_t sys_getSys_ms(void);
uint32_t sys_getSys_s(void);

void sys_lcd_printf(uint8_t ch);
#endif 