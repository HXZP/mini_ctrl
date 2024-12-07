

#include "FreeRTOS.h"
#include "hxzp_list.h"
#include "cmsis_os.h"
#include "main.h"

#include "hxzp_led.h"
#include "hxzp_key.h"

#include "spi.h"
#include "usart.h"
#include "fatfs.h"
#include "sdio.h"

#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "system.h"

#include "task.h"

#include <stdlib.h>

#include <stdio.h>

#include "hxzp_st7789.h"
//#include "WouoUI_user.h"
//#include "WouoUI.h"
/*

led设计 通过外部传入亮度表以及读表速度 加入优先级 加入在忙状态

*/
//https://blog.csdn.net/fhb1922702569/article/details/91368360/
char name[] = "test";
char num[4];
char docId[] = ".dat";
char doc[20];
uint16_t index = 0;
void read_write_file(void) {
  
    FRESULT res;
    UINT bw, br;
//    char write_data[] = "123";
//    char read_data[20];
  
    uint8_t write_data = index;

    index++;  
  
    sprintf(num, "%d", index);

    memset(doc,0,20);
  
    strcat(doc,name);
    strcat(doc,num);
    strcat(doc,docId);
  
    // 打开文件以写入
    res = f_open(&SDFile, doc, FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK) {
        // 写入数据
        res = f_write(&SDFile, &write_data, sizeof(write_data), &bw);
        res = f_close(&SDFile);
    }

    // 打开文件以读取
//    res = f_open(&SDFile, doc, FA_READ);
//    if (res == FR_OK) {
//        // 读取数据
//        res = f_read(&SDFile, read_data, sizeof(read_data), &br);
//        res = f_close(&SDFile);
//    }
}


 



//#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
//#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
//#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

//#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
//#define TRCENA          0x01000000
//struct __FILE { int handle; /* Add whatever is needed */ };
//FILE __stdout;
//FILE __stdin;

//int fputc( int ch, FILE *f ) {
//    if (DEMCR & TRCENA) 
//    {
//        while (ITM_Port32(0) == 0);
//        ITM_Port8(0) = ch;
//    }
//    return(ch);
//}
const uint8_t font16_16[4][32] = 
{
  {0x08,0x80,0x08,0x80,0x08,0x84,0x10,0x88,0x10,0x90,0x30,0xA0,0x30,0xC0,0x50,0x80,0x91,0x80,0x12,0x80,0x14,0x80,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x7E,0x10,0x00},/*"化",0*/
  {0x22,0x08,0x11,0x08,0x11,0x10,0x00,0x20,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xE0,0x00,0x40,0x01,0x80,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},/*"学",1*/
  {0x04,0x04,0x24,0x04,0x24,0x04,0x3F,0xA4,0x44,0x24,0x04,0x24,0xFF,0xE4,0x04,0x24,0x04,0x24,0x3F,0xA4,0x24,0xA4,0x24,0xA4,0x26,0x84,0x25,0x04,0x04,0x14,0x04,0x08},/*"制",2*/
  {0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x00,0x00,0x00,0x00,0x7C,0x7C,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x7C,0x7C,0x44,0x44},/*"品",3*/
};
//00001000 10000000
char str[] = "nb sb\r";
uint8_t data[20];
uint8_t dataR[20];
uint8_t res = 0;
uint8_t res1 = 0;
uint32_t res2 = 0;
uint32_t res3 = 0;
uint32_t res4 = 0;

uint32_t x = 0;
uint32_t y = 0;
uint8_t word = 0;
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    

//  hxzp_Led_piece("W0","A0",1,1,1,0);
  
//  hxzp_Led_set("W0",2);
//  hxzp_Led_set("W1",2);
//  hxzp_Led_set("W2",2);
 
  
  
  
//  TestUI_Init();
  
//  if (f_mount(&SDFatFS, SDPath, 1) != FR_OK) {}

//  res = f_mount(&SDFatFS, SDPath, 1);
  
//  if(res)
//  {
//    while(1);
//  }
//  
//  for(uint8_t i = 0;i<20;i++)
//  {
//    data[i] = i;
//  }  
  

  for(;;)
  {
//    res2++;
//   if(!res1){
//   
    
    
//   read_write_file();//res1 = 1;
    
    
    

    
    for(uint16_t wordNum = 0;wordNum < 4;wordNum++)
    {
      for(uint16_t wordIdex = 0;wordIdex < 32;wordIdex++)
      {
        word = font16_16[wordNum][wordIdex];
        for(uint16_t wordBit = 0;wordBit < 8;wordBit++)
        {
           x = wordNum * 16 + (wordIdex % 2) * 8 + wordBit; 
           y = wordIdex / 2;
          
           if(font16_16[wordNum][wordIdex] & (0x80 >> wordBit))
           {
              hxzp_st7789_SetPoint(x,y,0xFF); 
           }
        }        
      }    
    }    
    
//    x++;
//    y++;
//    hxzp_st7789_SetPoint(x,y,RED); 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
//   } 
//     vTaskList( signed char *pcWriteBuffer );
//    TestUI_Proc();
    
//    CDC_Transmit_FS((uint8_t*)"hello\r",6);
    
//      NVIC_SystemReset();
    
//    res2 = sys_getSys_us();
//    res3 = sys_getSys_ms();
//    res4 = sys_getSys_s();
//    read_write_file();
    
    
    printf("??");
    
//    HAL_UART_Transmit(&huart3,(uint8_t*)"abdasdk\r",strlen("abdasdk\r"),1000);
    
//    hxzp_Led_piece("W2","A0",50,1,0,1);
    
//    f_mount(&SDFatFS, SDPath, 1);

//   res3 =  HAL_SD_GetCardState(&hsd);
   
    
    
//    while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER);
//    res1 = HAL_SD_WriteBlocks(&hsd,data,1,1,100000000);

//    for(uint8_t i = 0;i<20;i++)
//    {
//      dataR[i] = 0;
//    }
//    
//    while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER);
//    res2 = HAL_SD_ReadBlocks(&hsd,dataR,1,1,100000000);    
//    

    
//    while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER);
// 
//    res1 = HAL_SD_WriteBlocks_DMA(&hsd,data,1,1);

////    if(HAL_SD_WriteBlocks_DMA(&hsd,data,1,1))while(1);

//    for(uint8_t i = 0;i<20;i++)
//    {
//      dataR[i] = 0;
//    }
//    
//    while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER);
//    
//    res2 = HAL_SD_ReadBlocks_DMA(&hsd,dataR,1,1);
    
//    if(HAL_SD_ReadBlocks_DMA(&hsd,dataR,1,1))while(1);
//    osThreadExit();
    osDelay(2000);
  }
  /* USER CODE END StartDefaultTask */
}










