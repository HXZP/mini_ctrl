#include "hxzp_st7789.h"
#include <time.h>
#include "system.h"
#include "string.h"

hxzp_st7789 LCD;

void StartLcdTask(void *argument);



static void hxzp_st7789_DelayMs(uint16_t ms)
{
    HAL_Delay(ms);
}

static void hxzp_st7789_TxLockHold(void)
{
    LCD.inTransmission = 1;
}

uint8_t hxzp_st7789_TxLockGet(void)
{
    return LCD.inTransmission;
}

void hxzp_st7789_TxLockRelease(void)
{
    if(LCD.getTc == NULL)
    {
        return;
    }
    
    if(LCD.getTc())
    {
        LCD.inTransmission = 0;
    }
}

static void hxzp_st7789_Write(uint8_t *data, uint16_t len)
{
    if(LCD.initFlag == 0)
    {
        return;
    }
    
    while(hxzp_st7789_TxLockGet());

    hxzp_st7789_TxLockHold();

    LCD.write(data,len);
}

static void hxzp_st7789_Commad(uint8_t data)
{
    if(LCD.initFlag == 0)
    {
        return;
    }

    LCD.setCS(ST7798_GPIOL);
    LCD.setA0(ST7798_GPIOL);
    hxzp_st7789_Write(&data,1);
    LCD.setCS(ST7798_GPIOH);
}

static void hxzp_st7789_Data(uint8_t data)
{
    if(LCD.initFlag == 0)
    {
        return;
    }

    LCD.setCS(ST7798_GPIOL);
    LCD.setA0(ST7798_GPIOH);
    hxzp_st7789_Write(&data,1);
    LCD.setCS(ST7798_GPIOH);
}

static void hxzp_st7789_WriteWord(uint16_t *data, uint16_t len)
{
    if(LCD.initFlag == 0)
    {
        return;
    }
    
    uint16_t temp;
    LCD.setCS(ST7798_GPIOL);
    LCD.setA0(ST7798_GPIOL);

    while(len > LCD_DATA_BUFF_LEN)
    {
        for (uint16_t i = 0; i < LCD_DATA_BUFF_LEN/2; i++)
        {
            temp = *data;
            data++;

            LCD.buff[i * 2]      = (uint8_t)(temp>>8);
            LCD.buff[i * 2 + 1]  = (uint8_t)(temp&0xFF); 
        }          

        hxzp_st7789_Write(LCD.buff, LCD_DATA_BUFF_LEN);
        len = len - LCD_DATA_BUFF_LEN;
    }

    if(len > 0)
    {
        hxzp_st7789_Write(LCD.buff, len);
    }

    LCD.setCS(ST7798_GPIOH);
}

void hxzp_st7789_SetWindow(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend)
{
    if(LCD.initFlag == 0)
    {
        return;
    }
    
    uint16_t temp,res[2];

    /*设置横坐标*/
    hxzp_st7789_Commad(0x2a);

    temp = LCD_ADRR_WSTART + xstart;
    res[0] = temp >> 8;
    res[1] = temp & 0xFF;
    hxzp_st7789_Data(res[0]);
    hxzp_st7789_Data(res[1]);
    temp = LCD_ADRR_WSTART + xend;
    res[0] = temp >> 8;
    res[1] = temp & 0xFF;    	
    hxzp_st7789_Data(res[0]);
    hxzp_st7789_Data(res[1]);
    
    /*设置纵坐标*/
    hxzp_st7789_Commad(0x2b);

    temp = LCD_ADRR_HSTART + ystart;
    res[0] = temp >> 8;
    res[1] = temp & 0xFF;
    hxzp_st7789_Data(res[0]);
    hxzp_st7789_Data(res[1]);
    temp = LCD_ADRR_HSTART + yend;
    res[0] = temp >> 8;
    res[1] = temp & 0xFF;    	
    hxzp_st7789_Data(res[0]);
    hxzp_st7789_Data(res[1]);

    /*准备写入数据*/
    hxzp_st7789_Commad(0x2c);
}


void hxzp_st7789_SetBackground(uint16_t color)
{
    if(LCD.initFlag == 0)
    {
        return;
    }
    
    hxzp_st7789_SetWindow(0,0,LCD_Width-1,LCD_HEIGHT-1);

    LCD.setCS(ST7798_GPIOL);
    LCD.setA0(ST7798_GPIOH);

    for (uint16_t i = 0; i < LCD_DATA_BUFF_LEN/2; i++)
    {
        LCD.buff[i * 2]      = (uint8_t)(color>>8);
        LCD.buff[i * 2 + 1]  = (uint8_t)(color&0xFF); 
    }

    for (uint16_t i = 0; i < LCD_DATA_TX_TIMES; i++)
    {
        hxzp_st7789_Write(LCD.buff, LCD_DATA_BUFF_LEN);
    }    

    LCD.setCS(ST7798_GPIOH);
}

void hxzp_st7789_SetTran(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend, uint16_t color)
{
    if(LCD.initFlag == 0)
    {
        return;
    }
    
    hxzp_st7789_SetWindow(xstart,ystart,xend,yend);

    LCD.setCS(ST7798_GPIOL);
    LCD.setA0(ST7798_GPIOH);


    for (uint16_t i = 0; i < LCD_DATA_BUFF_LEN/2; i++)
    {
        LCD.buff[i * 2]      = (uint8_t)(color>>8);
        LCD.buff[i * 2 + 1]  = (uint8_t)(color&0xFF); 
    }

    for (uint16_t i = 0; i < LCD_DATA_TX_TIMES; i++)
    {
        hxzp_st7789_Write(LCD.buff, LCD_DATA_BUFF_LEN);
    }    

    LCD.setCS(ST7798_GPIOH);
}

void hxzp_st7789_SetSpace(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend)
{
    if(LCD.initFlag == 0)
    {
        return;
    }
    
    hxzp_st7789_SetWindow(xstart,ystart,xend,yend);

    LCD.setCS(ST7798_GPIOL);
    LCD.setA0(ST7798_GPIOH);

    hxzp_st7789_Write(LCD.buff, (xend - xstart + 1)*(yend - ystart + 1)*2);
    
    LCD.setCS(ST7798_GPIOH);
}


void hxzp_st7789_SetPoint(uint16_t x, uint16_t y, uint16_t color)
{
    if(LCD.initFlag != 2)
    {
        return;
    }

    hxzp_st7789_SetWindow(x,y,x,y);
    
    LCD.setCS(ST7798_GPIOL);
    LCD.setA0(ST7798_GPIOH);    

    LCD.buff[0]  = (uint8_t)(color>>8);
    LCD.buff[1]  = (uint8_t)(color&0xFF);

    hxzp_st7789_Write(LCD.buff, 2);
    
    LCD.setCS(ST7798_GPIOH);
    
}

void hxzp_st7789_SetWord(const uint8_t *data, uint8_t wid, uint8_t len, uint16_t xoffset, uint16_t yoffset, uint16_t color, uint16_t colorb)
{ 
    uint32_t x = 0;
    uint32_t y = 0;

    uint8_t dataNum = wid*len/8;
     
    for(uint16_t wordIdex = 0;wordIdex < dataNum;wordIdex++)
    {
      for(uint16_t wordBit = 0;wordBit < 8;wordBit++)
      {
         x = xoffset + (wordIdex % (wid/8)) * 8 + wordBit; 
         y = yoffset + wordIdex / (wid/8);
        
         if(data[wordIdex] & (0x80 >> wordBit))
         {
            hxzp_st7789_SetPoint(x,y,color); 
         }
         else
         {
            hxzp_st7789_SetPoint(x,y,colorb); 
         }
      }        
    }      
}

/* 
0x00 0x00
bitotal = x + (y*30)
idex = bit/8
bitx = bit%8

   240
135

x = colu * 8 + bit
y = line

逐行 高位在前 阴码
*/
#if 1
//uint8_t scanBuff[135][30] = {0};

void hxzp_Lcd_PrintScan(uint16_t color, uint16_t colorb)
{
  uint16_t x;
  uint16_t y;
  uint16_t offset = 0;
  uint16_t cnt = 0;
  
  hxzp_st7789_SetWindow(0,0,LCD_Width-1,LCD_HEIGHT-1);
//  LCD.setCS(ST7798_GPIOL);
//  LCD.setA0(ST7798_GPIOH);   
#if 1  
  for(uint8_t line = 0;line < 135; line++)
  {
    for(uint8_t column = 0;column < 30; column++)
    {
      for(uint8_t bit = 0;bit < 8; bit++)
      {    
         x = column * 8 + bit;
         y = line;
         if(scanBuff[line][column] & (0x80 >> bit))
         {
            hxzp_st7789_SetPoint(x,y,color); 
//           LCD.buff[(line*30*8 + column*8 + bit - offset)*2] = (uint8_t)(color>>8);
//           LCD.buff[(line*30*8 + column*8 + bit - offset)*2 + 1] = (uint8_t)(color&0xFF);
         }
         else
         {
            hxzp_st7789_SetPoint(x,y,colorb); 
//           LCD.buff[(line*30*8 + column*8 + bit - offset)*2] = (uint8_t)(colorb>>8);
//           LCD.buff[(line*30*8 + column*8 + bit - offset)*2 + 1] = (uint8_t)(colorb&0xFF);
         }
         
//         cnt++;
//         
//         if(cnt == LCD_DATA_BUFF_LEN)
//         {
//            hxzp_st7789_Write(LCD.buff, LCD_DATA_BUFF_LEN);
//            offset+=LCD_DATA_BUFF_LEN - 1;
//            cnt = 0;
//         }
         
//        if((!((line*30*8 + column*8 + 7)%(LCD_DATA_BUFF_LEN - 1))) && (line*30*8 + column*8 + 7))
//        {
//        //            offset = (LCD_DATA_BUFF_LEN - 1)*((line*30 + column)/(LCD_DATA_BUFF_LEN - 1));
//         
//          hxzp_st7789_Write(LCD.buff, LCD_DATA_BUFF_LEN);
//          offset+=LCD_DATA_BUFF_LEN - 1;
//        }            
         
      }
      
   
    }
  }
#endif
 
//    for (uint16_t i = 0; i < LCD_DATA_BUFF_LEN/2; i++)
//    {
//        LCD.buff[i * 2]      = (uint8_t)(colorb>>8);
//        LCD.buff[i * 2 + 1]  = (uint8_t)(colorb&0xFF); 
//    }

//    for (uint16_t i = 0; i < LCD_DATA_TX_TIMES; i++)
//    {
//        hxzp_st7789_Write(LCD.buff, LCD_DATA_BUFF_LEN);
//    } 
    
//  LCD.setCS(ST7798_GPIOH);
}
#endif


//static uint8_t cursorx = 0;
//static uint8_t cursory = 0;
//static uint8_t wide = 8;
//static uint8_t high = 16;
//static uint16_t color = 0xFFFF;
//static uint16_t colorb = 0x0000;
//归位
uint8_t wordBuff[256];
void hxzp_Lcd_PrintCR(void)
{
  LCD.string.cursorx = 0;
  hxzp_st7789_SetTran(0,LCD.string.cursory,LCD_Width-1,LCD.string.cursory + 15, LCD.string.colorb);
}
//换行
void hxzp_Lcd_PrintLF(void)
{
  uint8_t y = LCD.string.cursory;  
  uint16_t Temp;

  if(y + 2*LCD.string.high - 1 > LCD_HEIGHT - 1)
  {
    y = 0;
    
#if 0    
    //超范围，滚动屏幕,刷新
    Temp = y + 2*high - 1 - LCD_HEIGHT; //(LCD_HEIGHT - 2*high + 1) - y;//后移的长度
    memcpy(scanBuff,scanBuff[Temp],(135 - Temp)*30);
    
    y = LCD_HEIGHT - high;
    memset(scanBuff[y],0,high*30);
    
    hxzp_Lcd_PrintScan(color,colorb); 
#endif    
  }
  else   
  {
    y += LCD.string.high;
  }
  LCD.string.cursory = y;
}

void hxzp_Lcd_Print(const uint8_t *data)
{
  uint8_t x = LCD.string.cursorx;
  uint8_t y = LCD.string.cursory;

  uint8_t xTemp;
  uint8_t yTemp;
  
  uint16_t Temp;

  if(x + LCD.string.wide > LCD_Width - 1)
  {
    x = 0;
 
    if(y + 2*LCD.string.high - 1 > LCD_HEIGHT - 1)
    {
      y = 0;
      
#if 0     
      //超范围，滚动屏幕,刷新
      Temp = y + 2*high - LCD_HEIGHT; //(LCD_HEIGHT - 2*high + 1) - y;//后移的长度
      memcpy(scanBuff,scanBuff[Temp],(135 - Temp)*30);
      
      y = LCD_HEIGHT - high;
      memset(scanBuff[y],0,high*30);
      
      hxzp_Lcd_PrintScan(color,colorb); 
#endif    
    }
    else   
    {
      y += LCD.string.high;
    }
    
    hxzp_st7789_SetTran(0,y,LCD_Width-1,y + 15, LCD.string.colorb);
  }

  uint8_t dataNum = LCD.string.wide * LCD.string.high/8;
   
  for(uint16_t wordIdex = 0;wordIdex < dataNum;wordIdex++)
  {
    for(uint16_t wordBit = 0;wordBit < 8;wordBit++)
    {
       xTemp = x + (wordIdex % (LCD.string.wide/8)) * 8 + wordBit; 
       yTemp = y + wordIdex / (LCD.string.wide/8);
      
       if(data[wordIdex] & (0x80 >> wordBit))
       {
//          hxzp_st7789_SetPoint(xTemp,yTemp,color); 
//          scanBuff[yTemp][xTemp/8] |= 0x80 >> wordBit;    
         
          LCD.buff[(wordIdex*8 + wordBit)*2] = (uint8_t)(LCD.string.color>>8);
          LCD.buff[(wordIdex*8 + wordBit)*2 + 1] = (uint8_t)(LCD.string.color&0xFF);         

       }
       else
       {
          LCD.buff[(wordIdex*8 + wordBit)*2] = (uint8_t)(LCD.string.colorb>>8);
          LCD.buff[(wordIdex*8 + wordBit)*2 + 1] = (uint8_t)(LCD.string.colorb&0xFF);            
         
//          hxzp_st7789_SetPoint(xTemp,yTemp,colorb); 
//          scanBuff[yTemp][xTemp/8] &= ~(0x80 >> wordBit);
       }
    }        
  }     
  hxzp_st7789_SetSpace(x,y,x+LCD.string.wide-1,y+LCD.string.high-1);

  x += LCD.string.wide;

  LCD.string.cursorx = x;
  LCD.string.cursory = y;
}

void hxzp_st7789_GetTcReg(getTcFlag getflag)
{
    if(getflag == NULL)
    {
        return;
    }
  
    LCD.getTc = getflag;
}


osThreadId_t LcdTaskHandle;
const osThreadAttr_t LcdTask_attributes = {
  .name = "LcdTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

void hxzp_st7789_InitReg(gpioReg CS,gpioReg A0,gpioReg LED,gpioReg RES,writeReg write)
{
    if(CS == NULL || A0 == NULL || LED == NULL || RES == NULL || write == NULL)
    {
        return ;
    }
  
    LCD.setCS  = CS;
    LCD.setA0  = A0;
    LCD.setLED = LED;
    LCD.setRES = RES;
    LCD.write  = write;
  
    LCD.initFlag = 1;
    
    if(LcdTaskHandle == NULL)
    {
        LcdTaskHandle = osThreadNew(StartLcdTask, NULL, &LcdTask_attributes);
    }    
}

static void hxzp_st7789_Init(void)
{
    if(LCD.initFlag == 0)
    {
        return;
    }

    LCD.setLED(ST7798_GPIOH);

    LCD.setRES(ST7798_GPIOH);
    hxzp_st7789_DelayMs(5);
    LCD.setRES(ST7798_GPIOL);
    hxzp_st7789_DelayMs(5);
    LCD.setRES(ST7798_GPIOH);
    hxzp_st7789_DelayMs(5);

    hxzp_st7789_Commad(0x01);//sleep in
    hxzp_st7789_DelayMs(10);

    hxzp_st7789_Commad(0x11);//sleep out
    hxzp_st7789_DelayMs(10);

    hxzp_st7789_Commad(0x36); // 设置显示方向
    hxzp_st7789_Data(0x60);

    hxzp_st7789_Commad(0x3A);
    hxzp_st7789_Data(0x55);

    hxzp_st7789_Commad(0x20);//此命令用于从显示反转模式中恢复。

    hxzp_st7789_Commad(0xb2);// 设置帧率控制
    hxzp_st7789_Data(0x01);
    hxzp_st7789_Data(0x01);
    hxzp_st7789_Data(0x00);
    hxzp_st7789_Data(0x01);
    hxzp_st7789_Data(0x01);
    
    hxzp_st7789_Commad(0xb7);// 设置电源控制
    hxzp_st7789_Data(0x35);	
    
    hxzp_st7789_Commad(0xbb);//VCOMS Setting
    hxzp_st7789_Data(0x35);
    
    hxzp_st7789_Commad(0xc0);//LCM Control 
    hxzp_st7789_Data(0x2c);	
    
    hxzp_st7789_Commad(0xc2);// VDV and VRH command write enable. 
    hxzp_st7789_Data(0x01);
    
    hxzp_st7789_Commad(0xc3);// VRH 设置
    hxzp_st7789_Data(0x0b);
    
    hxzp_st7789_Commad(0xc4);// VDV 设置
    hxzp_st7789_Data(0x20);

    hxzp_st7789_Commad(0x51);//亮度00-FF
    hxzp_st7789_Data(0x0F);
    
    hxzp_st7789_Commad(0xc6);// 帧率控制
    hxzp_st7789_Data(0x00);//119Hz
    
    hxzp_st7789_Commad(0xd0);//Power Control
    hxzp_st7789_Data(0xa4);	
    hxzp_st7789_Data(0xa1);	
      
    hxzp_st7789_Commad(0xe0);//正电压 Gamma 控制
    hxzp_st7789_Data(0xd0);
    hxzp_st7789_Data(0x00);
    hxzp_st7789_Data(0x02);
    hxzp_st7789_Data(0x07);
    hxzp_st7789_Data(0x0b);
    hxzp_st7789_Data(0x1a);
    hxzp_st7789_Data(0x31);
    hxzp_st7789_Data(0x54);	
    hxzp_st7789_Data(0x40);
    hxzp_st7789_Data(0x29);
    hxzp_st7789_Data(0x12);
    hxzp_st7789_Data(0x12);
    hxzp_st7789_Data(0x17);
    
    hxzp_st7789_Commad(0xe1);//负电压 Gamma 控制
    hxzp_st7789_Data(0xd0);
    hxzp_st7789_Data(0x00);
    hxzp_st7789_Data(0x02);
    hxzp_st7789_Data(0x07);
    hxzp_st7789_Data(0x05);
    hxzp_st7789_Data(0x25);
    hxzp_st7789_Data(0x2d);
    hxzp_st7789_Data(0x44);	
    hxzp_st7789_Data(0x45);
    hxzp_st7789_Data(0x1c);
    hxzp_st7789_Data(0x18);
    hxzp_st7789_Data(0x16);
    hxzp_st7789_Data(0x1c);
    
    hxzp_st7789_Commad(0x21);// 打开反显
    hxzp_st7789_Commad(0x28);//Display On

    hxzp_st7789_SetBackground(0);
    
    hxzp_st7789_Commad(0x29);//Display On
    hxzp_st7789_DelayMs(150);    
    
    LCD.initFlag = 2;
    
    LCD.string.color = 0xFFFF;
    LCD.string.colorb = 0x0000;
}

hxzp_st7789_rgb colorbackground = {

  .R = 0,
  .G = 0,      
  .B = 0,      
};

uint16_t xs,xe,ys,ye;
void StartLcdTask(void *argument)
{
    hxzp_st7789_Init();
    
    
    for(;;)
    {
        
//        color.R++;
//        color.G++;
//        color.B++;
//      
//        hxzp_st7789_SetBackground(*(uint16_t*)(&colorbackground));

//        hxzp_st7789_SetTran(xs++,xe+++1,ys++,ye+++1, RED);
//        
//        if(xs > LCD_Width)xs = 0;if(xe > LCD_Width)xe = 0;if(ys > LCD_HEIGHT)ys = 0;if(ye > LCD_HEIGHT)ye = 0;
      
      
        osDelay(10);
    }
}











