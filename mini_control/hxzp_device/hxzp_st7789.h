/*
使用屏幕为新
Data:
135*240
8pin

PinMap：
1.LEDA
2.GND
3.RESET
4.RS
5.SDA
6.SCL
7.VDD
8.CS

PC5 RES
PA5 SCK
PA7 SDA
PC4 A0(WRX)

Congfigue:
- Half-Duplex
- CPOL/CPHA:0/0 (The driver samples the SDA (input data) at rising edge of SCL, but shifts SDA (output data) at the falling edge of SCL.
- First Bit:High(The MSB is transmitted first. 

CS:
A falling edge on CSX enables the serial interface and indicates the start of data transmission.

WRX 
Data is regarded as a command when WRX is low 
Data is regarded as a parameter or data when WRX is high
0:command
1:data

Read Function
To achieve read function, the micro controller first has to send a command (read ID or register command) and 
then the following byte is transmitted in the opposite direction. 

Mode Enter
2-wire data lane serial interface use: CSX (chip enable), DCX (serial clock) and SDA (serial data 
input/output 1), and WRX (serial data input 2). To enter this interface, command E7h need set 10h.

Reset
RES低电平有效
上电拉电平复位操作，低电平至少要10us，然后进入复位模式，需要等待5ms完成初始化

该模块有三种颜色模式，用于将数据传输到显示 RAM。
这些是每像素 12 位颜色、每像素 16 位颜色和每像素 18 位颜色。
描述了每个接口的数据格式。可以通过 2 种方法将数据下载到帧内存中。

*/
#ifndef HXZP_ST7789_H
#define HXZP_ST7789_H

#include "stdlib.h"


#endif // HXZP_ST7789_H