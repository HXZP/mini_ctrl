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
    FIL file;
    FRESULT res;
    UINT bw, br;
    char write_data[] = "Hello, SD Card!";
    char read_data[20];

    // 打开文件以写入
    res = f_open(&file, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK) {
        // 写入数据
        res = f_write(&file, write_data, sizeof(write_data), &bw);
        f_close(&file);
    }

    // 打开文件以读取
    res = f_open(&file, "test.txt", FA_READ);
    if (res == FR_OK) {
        // 读取数据
        res = f_read(&file, read_data, sizeof(read_data), &br);
        f_close(&file);
    }
}


void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    

//  hxzp_Led_piece("W0","A0",1,1,1,0);
  
  hxzp_Led_set("W0",2);
  hxzp_Led_set("W1",2);
  hxzp_Led_set("W2",2);
 
  
    if (f_mount(&SDFatFS, SDPath, 1) != FR_OK) {
        // 挂载失败，处理错误
//        Error_Handler();
    }
    
  for(;;)
  {
    read_write_file();

    hxzp_Led_piece("W2","A0",50,1,0,1);
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}










