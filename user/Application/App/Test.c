

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

#include "sys_time.h"

#include "task.h"

#include <stdlib.h>

#include <stdio.h>
//#include "WouoUI_user.h"
//#include "WouoUI.h"
/*

led��� ͨ���ⲿ�������ȱ��Լ������ٶ� �������ȼ� ������æ״̬

*/

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
  
    // ���ļ���д��
    res = f_open(&SDFile, doc, FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK) {
        // д������
        res = f_write(&SDFile, &write_data, sizeof(write_data), &bw);
        res = f_close(&SDFile);
    }

    // ���ļ��Զ�ȡ
//    res = f_open(&SDFile, doc, FA_READ);
//    if (res == FR_OK) {
//        // ��ȡ����
//        res = f_read(&SDFile, read_data, sizeof(read_data), &br);
//        res = f_close(&SDFile);
//    }
}


 
int fputc(int ch, FILE *f)//�����ض���
{
    HAL_UART_Transmit(&huart3,(uint8_t*)&ch,1,1000);
    return ch;
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

uint32_t getTick = 0;
void vApplicationIdleHook(void)
{
	/*
		1.ִ�е����ȼ������̨��Ҫ��ͣ����Ĺ��ܴ���
		2.����ϵͳ����ԣ�����ں�ִ�п�������ʱ��Խ����ʾ�ں�Խ���У�
		3.�����������õ��͹���ģʽ��Ticklessģʽ��
	*/
  if(HAL_GetTick() - getTick > 100)
  {
  
  char *buffer = (char*)malloc(256);
  vTaskList(buffer);
  
  printf("///////////////////////\r\n");
  printf("%s",buffer);
  
  
  free(buffer);
  
  getTick = HAL_GetTick();
  }
}




char str[] = "nb sb\r";
uint8_t data[20];
uint8_t dataR[20];
uint8_t res = 0;uint8_t res1 = 0;uint32_t res2 = 0;uint32_t res3 = 0;uint32_t res4 = 0;
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */    

//  hxzp_Led_piece("W0","A0",1,1,1,0);
  
//  hxzp_Led_set("W0",2);
//  hxzp_Led_set("W1",2);
//  hxzp_Led_set("W2",2);
 
//  MX_USB_DEVICE_Init();
  
  
//  TestUI_Init();
  
//  if (f_mount(&SDFatFS, SDPath, 1) != FR_OK) {}

  res = f_mount(&SDFatFS, SDPath, 1);
  
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
    
    
   read_write_file();//res1 = 1;
    
    
//   } 
//     vTaskList( signed char *pcWriteBuffer );
//    TestUI_Proc();
    
//    CDC_Transmit_FS((uint8_t*)"hello\r",6);
    
//      NVIC_SystemReset();
    
//    res2 = sys_getSys_us();
//    res3 = sys_getSys_ms();
//    res4 = sys_getSys_s();
//    read_write_file();
    
    
//    printf("??");
    
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
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}










