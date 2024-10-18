#ifndef DELAY_H
#define DELAY_H

#include "stdint.h"
#include "stdlib.h"
#include "stm32f1xx_hal.h"

void delay_us(uint16_t us);
void delay_ms(uint16_t ms);

#endif // DELAY_H