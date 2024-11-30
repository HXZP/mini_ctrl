/*基于有头链表，链头不计入数据*/

#include "hxzp_template.h"

static List* NameList;

void StartNameTask(void *argument)
{  
  for(;;)
  {

    osDelay(1);
  }
}



osThreadId_t NameTaskHandle;
const osThreadAttr_t NameTask_attributes = {
  .name = "NameTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

void hxzp_Name_init(Name *self)
{
  if(NameList == NULL)
  {
    NameList = List_Create();
  }
 
  List_Insert(NameList,self);  
   
  if(NameTaskHandle == NULL && NameList != NULL)
  {
    NameTaskHandle = osThreadNew(StartNameTask, NULL, &NameTask_attributes);
  }
}










