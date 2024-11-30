#include "drv_lcd.h"

void Drv_Lcd_CS(uint8_t state)
{
    while(hxzp_st7789_TxLockGet());
  
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,state);  
}

void Drv_Lcd_A0(uint8_t state)
{
    HAL_GPIO_WritePin(LCD_A0_GPIO_Port,LCD_A0_Pin,state); 
}

void Drv_Lcd_LED(uint8_t state)
{
    HAL_GPIO_WritePin(LCD_LED_GPIO_Port,LCD_LED_Pin,state);
}

void Drv_Lcd_RES(uint8_t state)
{
    HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,state);
}

void Drv_Lcd_Write(uint8_t *data, uint16_t len)
{
    HAL_SPI_Transmit_DMA(&hspi1, data, len);
}


void Drv_Lcd_Init(void)
{
    hxzp_st7789_InitReg(Drv_Lcd_CS,Drv_Lcd_A0,Drv_Lcd_LED,Drv_Lcd_RES,Drv_Lcd_Write);
    
    hxzp_st7789_GetTcReg(USER_SPI_GetDmaTCFlag);
}





