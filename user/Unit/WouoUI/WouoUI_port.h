#ifndef __OLED_PORT_H__
#define __OLED_PORT_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

#define OLED_LOG (void)

//对应要实现的接口函数
void WouoUI_port_Init(void); //初始化驱动
void WouoUI_port_SendBuff(uint8_t buff[135][240]); //将8*128字节的buff一次性全部发送的函数

void drawBigPixel(int x, int y, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif

