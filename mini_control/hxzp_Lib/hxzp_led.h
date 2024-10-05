#ifndef HXZP_LED_H
#define HXZP_LED_H

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "string.h"
#include "hxzp_list.h"
#include "main.h"


typedef struct hxzp_Led_Config_s{

  /*亮度变化表range:0-A*/
  char table[32]; 
    
  struct
  {
    /*100ms Pscan range:0-3100ms */
    uint8_t scanTime : 5;
    
    /*range:0-3*/
    uint8_t priority : 2;
    
    uint8_t loop : 1;
  };

}Led_Config;


typedef struct hxzp_Led_s{

  char *name;
    
  Led_Config *Config;
  uint8_t ConfigNum;
  
  /*用于记录时间*/
  uint32_t preTime;
  
  struct
  {
    uint32_t bufferNum : 5;
    uint32_t insertUse : 1;

    /*tableMax:31 scanNum:31 busy:1true openflag:1true*/
    uint32_t tableNum : 5;
    uint32_t scanNum : 5;
    uint32_t busy : 1;    
    uint32_t light : 4;
    uint32_t reserve : 11;    
  };
  
  void (*Write)(uint8_t state);
  
  /*外部算法函数*/
  void (*Extern)(char *data);

}Led;

void hxzp_Led_init(Led *self);
void hxzp_Led_set(const char *name,uint8_t num);
void hxzp_Led_insert(const char *name,uint8_t num);
void hxzp_Led_piece(const char *name,const char *light,uint8_t sacnTime,uint8_t priority,uint8_t loop,uint8_t insert);

#endif

