#ifndef HXZP_LED_H
#define HXZP_LED_H

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "string.h"
#include "hxzp_list.h"
#include "main.h"


typedef struct hxzp_Led_Config_s{

  /*亮度变化表range:0-A*/
  const char *table; 
    
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
    uint8_t insertNum : 5;
    uint8_t insertUse : 1;
    uint8_t reserve   : 2;
  };
  
  struct
  {
    /*tableMax:31 scanNum:31 busy:1true openflag:1true*/
    uint16_t tableNum : 5;
    uint16_t scanNum : 5;
    uint16_t busy : 1;
    uint16_t openflag : 1;    
    uint16_t light : 4;
  };
  
  void (*Write)(uint8_t State);
  void (*Extern)(char *data);

}Led;

void hxzp_led_init(Led *self);
void hxzp_led_set(const char *name,uint8_t num);
#endif

