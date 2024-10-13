/*
ʹ����ĻΪ���Ǿ�135*240��spi����Ӱ�
��Ļ��С 135*240
����8pin

PinMap��
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
RES�͵�ƽ��Ч
�ϵ�����ƽ��λ�������͵�ƽ����Ҫ10us��Ȼ����븴λģʽ����Ҫ�ȴ�5ms��ɳ�ʼ��

��ģ����������ɫģʽ�����ڽ����ݴ��䵽��ʾ RAM��
��Щ��ÿ���� 12 λ��ɫ��ÿ���� 16 λ��ɫ��ÿ���� 18 λ��ɫ��
������ÿ���ӿڵ����ݸ�ʽ������ͨ�� 2 �ַ������������ص�֡�ڴ��С�

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

ע���ַ��ʼ

BC<--35H
135  1
+----+1   28H      
|    |     |
|    |     |
|    |     | 
|    |     | 
|    |     v
+----+240 117H 

3240
64800 
*/
#ifndef HXZP_ST7789_H
#define HXZP_ST7789_H

#include "stdlib.h"
#include "stdint.h"

#define LCD_Width  240
#define LCD_HEIGHT 135
#define LCD_AREA   3240
#define LCD_DATA_LEN   64800



/*��ʼ��ַ�ͽ�����ַ*/
#define LCD_ADRR_WSTART 0x28
#define LCD_ADRR_WEND   0x117
#define LCD_ADRR_HSTART 0x35
#define LCD_ADRR_HEND   0xBC

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


typedef enum
{
    ST7798_GPIOL = 0,    
    ST7798_GPIOH,
    /* data */
}st7789_gpio_sta;



typedef struct hxzp_st7789_t
{

    void (*setCS)(uint8_t state);
    void (*setA0)(uint8_t state);
    void (*setLED)(uint8_t state);
    void (*setRES)(uint8_t state);

    void (*write)(uint8_t *data, uint16_t len);
    void (*writeByte)(uint8_t data);

}hxzp_st7789;












#endif // HXZP_ST7789_H