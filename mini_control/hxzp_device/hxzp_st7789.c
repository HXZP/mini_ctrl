#include "hxzp_st7789.h"

#include "FreeRTOS.h"
#include "cmsis_os.h"

hxzp_st7789 LCD;

static void hxzp_st7789_DelayMs(uint16_t ms)
{
    hxzp_st7789_DelayMs(ms);
}

void hxzp_st7789_Commad(uint8_t data)
{
    if(LCD.setA0 == NULL || LCD.setCS == NULL || LCD.writeByte == NULL)
    {
        return;
    }

    LCD.setCS(ST7798_GPIOL);
    LCD.setA0(ST7798_GPIOL);
    LCD.writeByte(data);
    LCD.setCS(ST7798_GPIOH);
}

void hxzp_st7789_Data(uint8_t data)
{
    if(LCD.setA0 == NULL || LCD.setCS == NULL || LCD.writeByte == NULL)
    {
        return;
    }

    LCD.setCS(ST7798_GPIOH);
    LCD.setA0(ST7798_GPIOL);
    LCD.writeByte(data);
    LCD.setCS(ST7798_GPIOH);
}

static void hxzp_st7789_WriteWord(uint16_t *data, uint16_t len)
{
    if(LCD.setA0 == NULL || LCD.setCS == NULL || LCD.writeByte == NULL)
    {
        return;
    }
    
    uint8_t  msg[10];
    uint16_t temp;
    LCD.setCS(ST7798_GPIOH);
    LCD.setA0(ST7798_GPIOL);

    while(len > 10)
    {
        for (int i = 0; i < 10; i++)
        {
            temp = &data;
            data++;

            if(!(i%2))msg[i] = (uint8_t)(temp>>8);
            if(i%2)msg[i+1]  = (uint8_t)(temp&0xFF); 
        }          

        LCD.write(data, 10);
        len = len - 10;
    }      

    if(len > 0)
    {
        LCD.write(data, len);
    }

    LCD.setCS(ST7798_GPIOH);
}

void hxzp_st7789_SetWindow(uint16_t xstart, uint16_t ystart, uint16_t xend, uint16_t yend)
{
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
    LCD_Cmd(0x2c);
}


void hxzp_st7789_SetBackground(uint16_t color)
{


}









void hxzp_st7789_Init(void)
{
    if(LCD.setLED == NULL || LCD.setRES == NULL)
    {
        return;
    }

    LCD.setLED(ST7798_GPIOH);

    LCD.setRES(ST7798_GPIOH);
    hxzp_st7789_DelayMs(5);
    LCD.setRES(ST7798_GPIOH);
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
	hxzp_st7789_Data(0x0c);
	hxzp_st7789_Data(0x0c);
	hxzp_st7789_Data(0x00);
	hxzp_st7789_Data(0x33);
	hxzp_st7789_Data(0x33);
	
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
	hxzp_st7789_Data(0x00);//40Hz
	
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

}



















