/*
使用屏幕为新智景135*240，spi，插接版
屏幕大小 135*240
引脚8pin

PinMap：
1.LEDA
2.GND
3.RESET
4.RS
5.SDA
6.SCL
7.VDD
8.CS

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

ram 240*320
F0
240           0 
+-------------+0
|             |
|             |
|             |
|             |
|             |
|             |
|             |
|             |
|             |
+-------------+320 140

注意地址起始

BC<--35H
135  1
+----+1   28H      
|    |     |
|    |     |
|    |     | 
|    |     | 
|    |     v
+----+240 117H 

数据长度
屏幕像素点数量3240
屏幕数据长度64800 

使用RGB色彩 [ RRRRR | GGGGGG | BBBBB ]
红色：5位，范围是 0 - 31
绿色：6位，范围是 0 - 63
蓝色：5位，范围是 0 - 31

5次发送1000us一次

https://blog.csdn.net/weixin_51915497/article/details/136156233?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-136156233-blog-142192908.235%5Ev43%5Epc_blog_bottom_relevance_base7&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-136156233-blog-142192908.235%5Ev43%5Epc_blog_bottom_relevance_base7&utm_relevant_index=1



*/
#ifndef HXZP_ST7789_H
#define HXZP_ST7789_H

#include "stdlib.h"
#include "stdint.h"

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"

#define LCD_Width      240
#define LCD_HEIGHT     135
#define LCD_AREA       LCD_Width*LCD_HEIGHT //32400

#define LCD_DATA_TX_TIMES     4                            //传输次数
#define LCD_DATA_LEN          LCD_AREA*2                     //数据长度 64800  0.0144  69.44hz
#define LCD_DATA_BUFF_LEN     LCD_DATA_LEN/LCD_DATA_TX_TIMES //一次传输数量 648  



/*起始地址和结束地址*/
#define LCD_ADRR_WSTART 0x28
#define LCD_ADRR_WEND   0x117
#define LCD_ADRR_HSTART 0x35
#define LCD_ADRR_HEND   0xBB
//#define LCD_ADRR_WSTART 0
//#define LCD_ADRR_WEND   0
//#define LCD_ADRR_HSTART 0
//#define LCD_ADRR_HEND   0


#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


typedef enum
{
    ST7798_GPIOL = 0,    
    ST7798_GPIOH,
    /* data */
}st7789_gpio_sta;

typedef struct hxzp_st7789_rgb_t
{
    uint16_t R:5;//31
    uint16_t G:6;//63
    uint16_t B:5;//31
} hxzp_st7789_rgb;


/*
static uint8_t cursorx = 0;
static uint8_t cursory = 0;
static uint8_t wide = 8;
static uint8_t high = 16;
static uint16_t color = 0xFFFF;
static uint16_t colorb = 0x0000;
*/
typedef struct  hxzp_string_t
{
  uint8_t cursorx;
  uint8_t cursory;
  
  uint8_t wide;
  uint8_t high;

  uint16_t color;
  uint16_t colorb;

  uint16_t buffIndex;
  
}hxzp_string;




typedef struct hxzp_st7789_t
{
    uint8_t buff[LCD_DATA_BUFF_LEN];

    struct
    {
        uint8_t initFlag       : 2;
        uint8_t inTransmission : 1;
        uint8_t reserve        : 5;
        /* data */
    };
    
    hxzp_string string;
    
    void (*setCS)(uint8_t state);
    void (*setA0)(uint8_t state);
    void (*setLED)(uint8_t state);
    void (*setRES)(uint8_t state);

    void (*write)(uint8_t *data, uint16_t len);

    uint8_t (*getTc)(void);
    
}hxzp_st7789;

typedef uint8_t (*getTcFlag)(void);
typedef void (*gpioReg)(uint8_t state);
typedef void (*writeReg)(uint8_t *data, uint16_t len);

void hxzp_st7789_InitReg(gpioReg CS,gpioReg A0,gpioReg LED,gpioReg RES,writeReg write);

void hxzp_st7789_GetTcReg(getTcFlag getflag);

uint8_t hxzp_st7789_TxLockGet(void);

void hxzp_st7789_TxLockRelease(void);

void hxzp_st7789_SetBackground(uint16_t color);

void hxzp_st7789_SetWindow(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend);

void hxzp_st7789_SetPoint(uint16_t x, uint16_t y, uint16_t color);

void hxzp_st7789_SetWord(const uint8_t *data, uint8_t wid, uint8_t len, uint16_t xoffset, uint16_t yoffset, uint16_t color, uint16_t colorb);

void hxzp_Lcd_PrintLF(void);//10
void hxzp_Lcd_PrintCR(void);//13
void hxzp_Lcd_Print(const uint8_t *data);
#endif // HXZP_ST7789_H









