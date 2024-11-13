#ifndef SYS_TIME_H
#define SYS_TIME_H

#include "stdint.h"
#include "stdlib.h"
#include "stm32f1xx_hal.h"

void sys_delay_us(uint16_t us);
void sys_delay_ms(uint16_t ms);
uint32_t sys_getSys_us(void);
uint32_t sys_getSys_ms(void);
uint32_t sys_getSys_s(void);
#endif // DELAY_H