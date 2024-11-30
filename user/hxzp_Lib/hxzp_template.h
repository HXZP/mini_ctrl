#ifndef HXZP_TEMPLATE_H
#define HXZP_TEMPLATE_H

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "string.h"
#include "hxzp_list.h"
#include "main.h"


typedef struct hxzp_Name_Config_s{

  uint8_t reserve;

}Name_Config;



typedef struct hxzp_Name_s{

  char *name;
    
  Name_Config *Config;
  uint8_t ConfigNum;
    
  void (*Write)(void);
  void (*Read)(void);
  void (*Extern)(void);

}Name;










#endif
