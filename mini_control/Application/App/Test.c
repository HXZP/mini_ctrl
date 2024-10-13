#include "FreeRTOS.h"
#include "hxzp_list.h"
#include "cmsis_os.h"
#include "main.h"

#include "hxzp_led.h"
#include "hxzp_key.h"

#include "spi.h"
/*

led设计 通过外部传入亮度表以及读表速度 加入优先级 加入在忙状态

*/

void LCD_Cmd(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_A0_GPIO_Port,LCD_A0_Pin,0);  
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,0);
//  HAL_Delay(1);

	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,1);
}

void LCD_Dat(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_A0_GPIO_Port,LCD_A0_Pin,1);  
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,0);
//  HAL_Delay(1);

	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,1);
}






//uint8_t sdata[2700];

#define BUFF 2700
  uint8_t  msg[BUFF];
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    

//  hxzp_Led_piece("W0","A0",1,1,1,0);
  
  hxzp_Led_set("W0",2);
  hxzp_Led_set("W1",2);
  hxzp_Led_set("W2",2);
  
#if 1	
  HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,1);
  
  HAL_GPIO_WritePin(LCD_LED_GPIO_Port,LCD_LED_Pin,1);

//	HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,1);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,0);
//	HAL_Delay(5);	
//	HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,1);
  
	HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,1);
	HAL_Delay(5);
	HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,0);
	HAL_Delay(5);
	HAL_GPIO_WritePin(LCD_RES_GPIO_Port,LCD_RES_Pin,1);
	HAL_Delay(5);
  
  
	LCD_Cmd(0x01);//sleep in
	HAL_Delay(10);
  
	LCD_Cmd(0x11);//sleep out
	HAL_Delay(10);
  
  


	LCD_Cmd(0x36);
	LCD_Dat(0x60);//左到右 上到下

	LCD_Cmd(0x3A);
	LCD_Dat(0x55);
#if 1	  
	LCD_Cmd(0x20);//此命令用于从显示反转模式中恢复。

	LCD_Cmd(0xb2);
	LCD_Dat(0x0c);
	LCD_Dat(0x0c);
	LCD_Dat(0x00);
	LCD_Dat(0x33);
	LCD_Dat(0x33);
	
	LCD_Cmd(0xb7);
	LCD_Dat(0x35);	
	
	LCD_Cmd(0xbb);//VCOMS Setting
	LCD_Dat(0x35);
	
	LCD_Cmd(0xc0);//LCM Control 
	LCD_Dat(0x2c);	
	
	LCD_Cmd(0xc2);// VDV and VRH command write enable. 
	LCD_Dat(0x01);
	
	LCD_Cmd(0xc3);
	LCD_Dat(0x0b);
	
	LCD_Cmd(0xc4);
	LCD_Dat(0x20);

	LCD_Cmd(0x51);
	LCD_Dat(0x0F);//亮度00-FF
	
	LCD_Cmd(0xc6);
	LCD_Dat(0x00);//40Hz
	
	LCD_Cmd(0xd0);//Power Control
	LCD_Dat(0xa4);	
	LCD_Dat(0xa1);	
		
	LCD_Cmd(0xe0);//正电压 Gamma 控制
	LCD_Dat(0xd0);
	LCD_Dat(0x00);
	LCD_Dat(0x02);
	LCD_Dat(0x07);
	LCD_Dat(0x0b);
	LCD_Dat(0x1a);
	LCD_Dat(0x31);
	LCD_Dat(0x54);	
	LCD_Dat(0x40);
	LCD_Dat(0x29);
	LCD_Dat(0x12);
	LCD_Dat(0x12);
	LCD_Dat(0x17);
	
	LCD_Cmd(0xe1);//负电压 Gamma 控制
	LCD_Dat(0xd0);
	LCD_Dat(0x00);
	LCD_Dat(0x02);
	LCD_Dat(0x07);
	LCD_Dat(0x05);
	LCD_Dat(0x25);
	LCD_Dat(0x2d);
	LCD_Dat(0x44);	
	LCD_Dat(0x45);
	LCD_Dat(0x1c);
	LCD_Dat(0x18);
	LCD_Dat(0x16);
	LCD_Dat(0x1c);
#endif
  LCD_Cmd(0x21);
	LCD_Cmd(0x29);//Display On
  HAL_Delay(150);


//  uint8_t *sdata = malloc(240 * 135 * 2);
  
  
//	LCD_Cmd(0x2a);
//	LCD_Dat(0x00);
//	LCD_Dat(0x40);	

//	LCD_Cmd(0x2b);
//	LCD_Dat(0x00);
//	LCD_Dat(0x40);		
//  
//  LCD_Cmd(0x2c);
//	LCD_Dat(0x11);
//	LCD_Dat(0x01); 
#endif     
//  hxzp_Led_insert("W0",0);
//  hxzp_Led_insert("W1",0);
//  hxzp_Led_insert("W2",0);

  uint16_t data = 0x0000;

  
  int32_t time = HAL_GetTick();int32_t errtime;
  /* Infinite loop */
  
  
  
    
 
  
  
  for(;;)
  {
    /*hz = 1000/lenght*delay 人类25*/
    LCD_Cmd(0x2a);
    LCD_Dat(0x00);
    LCD_Dat(0x28);	
    LCD_Dat(0x01);
    LCD_Dat(0x17);//320 屏幕横
    
    LCD_Cmd(0x2b);
    LCD_Dat(0x00);
    LCD_Dat(0x35);		
    LCD_Dat(0x00);
    LCD_Dat(0xBC);//140 屏幕竖
    
    LCD_Cmd(0x2c);
    HAL_GPIO_WritePin(LCD_A0_GPIO_Port,LCD_A0_Pin,1);  
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,0);     
    

//  HAL_Delay(1);

//    for (int i = 0; i < 2700; i++) {
//      
//      if(!(i%2))sdata[i] = (uint8_t)(data&0xFF00>>8);
//      if(i%2)sdata[i+1] = (uint8_t)(data&0x00FF); 
//      
//    }
//    
//    for (int i = 0; i < 24; i++) {

//      HAL_SPI_Transmit_DMA(&hspi1, sdata, 2700);
//    }   

//    HAL_SPI_Transmit_DMA(&hspi1, sdata, 2 * 240 * 135);


    for (int i = 0; i < BUFF / 2; i++) {
      
      msg[i*2] = (uint8_t)((data&0xFF00)>>8);
      msg[i*2+1] = (uint8_t)(data&0x00FF); 
    }
    
    for (int i = 0; i < 64800 / BUFF; i++) {
//      for (int j = 0; j < 10; j++){}
        

        {
          HAL_SPI_Transmit_DMA(&hspi1, msg, BUFF);
          LCD_tcFlagReset();
        }
        while(!LCD_tcFlagGet());
        
//      HAL_SPI_Transmit(&hspi1, msg, BUFF, 1000);   
 //       continue;
    }
    
//        HAL_SPI_Transmit(&hspi1, msg, 648, 1000);    
    
//    errtime = time - HAL_GetTick();
//   uint8_t data[2 * 240 * 135];
//  for (int i = 0; i < 240 * 135 * 2; i++) {
//    
//      data[i] = 0xFF;
//  } 
//  HAL_SPI_Transmit(&hspi1, data, 240 * 135 * 2, 1000);
  
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,1);      

    data++;
    
    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}










