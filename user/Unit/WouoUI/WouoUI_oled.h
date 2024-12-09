#ifndef __OLED_G_H__
#define __OLED_G_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "WouoUI_port.h"
#include "WouoUI_font.h"
#include "math.h"
#include "string.h"

#define OLED_WIDTH 240
#define OLED_HEIGHT 135

#define OLED_MIDDLE_H 64
#define OLED_MIDDLE_V 32

#define OLED_LINE_SPACE 1

typedef struct
{
    int16_t start_x;
    int16_t start_y;
    int16_t w;
    int16_t h;
} window;

typedef enum {
    BLUR_1_4 = 0x00,
    BLUR_2_4,
    BLUR_3_4,
    BLUR_4_4,
} BLUR_DEGREE;

typedef enum {
    RD_LEFT_UP = 0x00, // 射线从左上角出发
    RD_LEFT_DOWN,      // 射线从左下角出发
    RD_RIGHT_UP,       // 射线从右上角出发
    RD_RIGHT_DOWN,     // 射线从右下角出发
    RD_RIGHT,          // 射线从水平向�?
    RD_LEFT,           // 射线从水平向�?
} RaderDirection;

typedef enum {
    COLOR_NORMAL = 0,
    COLOR_XOR
} OLED_COLOR_MODE;

typedef enum {
    OLED_BLACK = 0,
    OLED_WHITE
} OLED_COLOR;

void OLED_ClearBuff(void);
void OLED_SetPointColor(uint8_t color);
void OLED_RefreshBuff(void);

int16_t OLED_WinDrawASCII(window *win, int16_t x, int16_t y, sFONT font, char c);
void OLED_WinDrawStr(window *win, int16_t x, int16_t y, sFONT font, uint8_t *str);
uint16_t OLED_GetStrWidth(const char *str, sFONT font);
void OLED_WinDrawVLine(window *win, int16_t x, int16_t y_start, int16_t y_end);
void OLED_WinDrawHLine(window *win, int16_t x_start, int16_t x_end, int16_t y);
void OLED_WinDrawRBox(window *win, int16_t x_start, int16_t y_start, int16_t width, int16_t height, uint8_t r);
void OLED_WinDrawRBoxEmpty(window *win, int16_t x_start, int16_t y_start, int16_t width, int16_t height, uint8_t r);
void OLED_WinDrawBoxRightAngle(window *win, int16_t x_start, int16_t y_start, int16_t width, int16_t height, uint8_t r);
void OLED_WinDrawBMP(window *win, int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t *BMP, uint8_t color);
void OLED_WinDrawPoint(window *win, int16_t x, int16_t y);
void OLED_WinDrawLine(window *win, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void OLED_AllBlur(BLUR_DEGREE blur);
uint8_t OLED_WinDrawRaderPic(window *win, const uint8_t *pic, int16_t start_x, uint16_t start_y, uint8_t width, uint8_t height, uint16_t *p_end_point,
                             RaderDirection direct, uint8_t enable_all_point_scan, uint8_t scan_rate);

#ifdef __cplusplus
}
#endif

#endif
