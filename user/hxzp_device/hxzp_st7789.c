#include "hxzp_st7789.h"
#include <time.h>
#include "system.h"


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

void hxzp_st7789_SetPoint(uint16_t x, uint16_t y, uint16_t color)
{
    if(LCD.initFlag == 0)
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

void hxzp_st7789_SetWord(uint16_t x, uint16_t y, uint16_t color)
{
    if(LCD.initFlag == 0)
    {
        return;
    }

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
    hxzp_st7789_Commad(0x29);//Display On
    hxzp_st7789_DelayMs(150);

    LCD.initFlag = 2;
}

hxzp_st7789_rgb color = {

  .R = 0,
  .G = 0,      
  .B = 0,      
};

uint16_t xs,xe,ys,ye;
void StartLcdTask(void *argument)
{
    hxzp_st7789_Init();
    hxzp_st7789_SetBackground(*(uint16_t*)(&color));
    
    for(;;)
    {
        
//        color.R++;
//        color.G++;
//        color.B++;
//      
//        hxzp_st7789_SetBackground(*(uint16_t*)(&color));

//        hxzp_st7789_SetTran(xs++,xe+++1,ys++,ye+++1, RED);
//        
//        if(xs > LCD_Width)xs = 0;if(xe > LCD_Width)xe = 0;if(ys > LCD_HEIGHT)ys = 0;if(ye > LCD_HEIGHT)ye = 0;
      
      
        osDelay(10);
    }
}











