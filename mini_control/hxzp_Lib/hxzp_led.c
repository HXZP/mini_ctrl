#include "hxzp_led.h"


static List* LedList;


void StartLedTask(void *argument)
{
  static uint8_t u8count = 0;
  uint8_t u8tableNum = 0;
  Led *self;
  
  for(;;)
  {
    for(List *node = LedList->next; node != NULL; node = node->next)
    {
      self = (Led*)(node->data);
      
      /*未开启*/
      if(self->openflag == 0)
      {
        continue;
      }

      if(self->insertUse == 0)
      {
        u8tableNum = self->tableNum;
      }   
      else
      {
        u8tableNum = self->insertNum;
      }
      
      /*计算下一动作时间*/
      if(self->preTime == 0)
      {
        self->busy = 1;
        self->preTime = HAL_GetTick();
      }
      else if(HAL_GetTick() - self->preTime > self->Config[u8tableNum].scanTime*100)
      {
          if(self->Config[u8tableNum].table[self->scanNum + 1] == '\0')
          {
            if(self->Config[u8tableNum].loop == 1)
            {
              self->scanNum = 0;
              self->busy = 1;
            }
            else
            {
              if(self->insertUse == 1)
              {
                self->insertUse = 0;
              }
              
              self->busy = 0;            
            }
          }
          else if(self->Config[u8tableNum].table[self->scanNum + 1] != '\0')
          {
            self->scanNum++; 
            self->busy = 1;
          }
          
          self->preTime = HAL_GetTick();
      }  
      
      /*解析数据*/
      switch(self->Config[u8tableNum].table[self->scanNum])
      {
        case '0':
          self->light = 0;
          break;

        case '1':
          self->light = 1;
          break;
        
        case '2':
          self->light = 2;
          break;

        case '3':
          self->light = 3;
          break;
        
        case '4':
          self->light = 4;
          break;

        case '5':
          self->light = 5;
          break;

        case '6':
          self->light = 6;
          break;

        case '7':
          self->light = 7;
          break;        

        case '8':
          self->light = 8;
          break;

        case '9':
          self->light = 9;
          break;

        case 'A':
          self->light = 10;
          break;    
         
        default:
          self->light = 0xF;
          self->Extern((char *)(&self->Config[u8tableNum].table[self->scanNum]));
          break;
      }
      
      /*执行*/
      if(self->light <= u8count && self->light <= 10 && self->Write != NULL)
      {
        self->Write(1);
      }
      else
      {
        self->Write(0);
      }
      
      u8count = (u8count == 10) ? 0 : (u8count + 1);
    }       

    osDelay(1);
  }
}


osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

void hxzp_led_init(Led *self)
{
  if(LedList == NULL)
  {
    LedList = List_Create();
  }
 
  List_Insert(LedList,self);  
   
  if(ledTaskHandle == NULL && LedList != NULL)
  {
    ledTaskHandle = osThreadNew(StartLedTask, NULL, &ledTask_attributes);
  }
}

void hxzp_led_set(const char *name,uint8_t num)
{
  Led *self;
  
  for(List *node = LedList->next; node != NULL; node = node->next)
  {
    self = (Led*)(node->data);
    
    if(strcmp(self->name, name) == 0)
    {
      if(self->ConfigNum > num)
      {
        if(self->Config[self->tableNum].priority <= self->Config[num].priority)
        {
          self->openflag = 1;
          self->tableNum = num;
          self->scanNum = 0;
          self->preTime = 0;
        }
      }
      break;
    }
  }
}

void hxzp_led_insert(const char *name,uint8_t num)
{
  Led *self;
  
  for(List *node = LedList->next; node != NULL; node = node->next)
  {
    self = (Led*)(node->data);
    
    if(strcmp(self->name, name) == 0)
    {
      if(self->ConfigNum > num)
      {  
        if(self->Config[self->tableNum].priority <= self->Config[num].priority)
        {        
          if(self->Config[num].loop == 0)
          {
            self->openflag = 1;
            self->insertUse = 1;
            self->insertNum = num;
            self->scanNum = 0; 
            self->preTime = 0;
          }
        }          
      }
      break;
    }
  }  
}  







