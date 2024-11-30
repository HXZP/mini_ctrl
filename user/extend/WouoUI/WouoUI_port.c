#include "WouoUI_port.h"
#include "hxzp_st7789.h"

void WouoUI_port_SendBuff(uint8_t buff[135][240]) {
    
  for(uint8_t i = 0;i<135;i++)
  {
    for(uint8_t j = 0;j<240;j++)
    {
      if(buff[j][i])
        hxzp_st7789_SetPoint(j,i,0x255);
      else
        hxzp_st7789_SetPoint(j,i,0);
    }      
  
  }
  
}
