#include "FreeRTOS.h"
#include "hxzp_list.h"
#include "cmsis_os.h"
#include "main.h"

#include "hxzp_led.h"
#include "hxzp_key.h"

#include "spi.h"

#include "fatfs.h"
#include "sdio.h"

/*

led设计 通过外部传入亮度表以及读表速度 加入优先级 加入在忙状态

*/



void read_write_file(void) {
  
    FRESULT res;
    UINT bw, br;
    char write_data[] = "666";
    char read_data[20];

    // 打开文件以写入
    res = f_open(&SDFile, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK) {
        // 写入数据
        res = f_write(&SDFile, write_data, sizeof(write_data), &bw);
        res = f_close(&SDFile);
    }

    // 打开文件以读取
    res = f_open(&SDFile, "test.txt", FA_READ);
    if (res == FR_OK) {
        // 读取数据
        res = f_read(&SDFile, read_data, sizeof(read_data), &br);
        res = f_close(&SDFile);
    }
}


  uint8_t data[20];
  uint8_t dataR[20];
uint8_t res = 0;uint8_t res1 = 0;uint8_t res2 = 0;uint8_t res3 = 0;
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    

//  hxzp_Led_piece("W0","A0",1,1,1,0);
  
  hxzp_Led_set("W0",2);
  hxzp_Led_set("W1",2);
  hxzp_Led_set("W2",2);
 
  
//  if (f_mount(&SDFatFS, SDPath, 1) != FR_OK) {}

  res = f_mount(&SDFatFS, SDPath, 1);
  
  if(res)
  {
    while(1);
  }
  
  for(uint8_t i = 0;i<20;i++)
  {
    data[i] = i;
  }  
  

  for(;;)
  {
    res2++;
   if(!res1){
   
   read_write_file();//res1 = 1;
   } 
    
    
    
//      NVIC_SystemReset();
    


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
    osDelay(3000);
  }
  /* USER CODE END StartDefaultTask */
}










