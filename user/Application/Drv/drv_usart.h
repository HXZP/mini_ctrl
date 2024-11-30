#ifndef DRV_USART_H
#define DRV_USART_H

#include "hxzp_lib.h"
#include "usart.h"

void Drv_Usart_Init(void);
void Drv_Usart_RxCpltCallback(const char *name);
#endif // DRV_LED_H