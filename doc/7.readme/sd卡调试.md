# SD卡调试

sd卡无法通信，更改上拉电阻47K到10K后依旧无法通信，表现为无法正常挂载，debug发现无法通信

高速率下要使用dma

测试其实也可以不用dma，发送和接收记得while

修改了堆栈后可以勉强使用fafts

## cmbacktrace使用

为了适配freertos要修改task .c文件，见doc文件夹

注意

```c
601    /*该检查会导致无法使用cmbacktrace，因为修改了TCB_T*/
602 //			configASSERT( xSize == sizeof( TCB_t ) )
```

## 11.30调试sd卡，与任务堆栈相关

测试发现使用fafts读写sd会死机，现象为成功读写sd几次后死机，使用cmbacktrace检查得到最后出现异常是在任务启动中

![Snipaste_2024-11-30_11-18-49](D:\Aproject\foc\mini_ctrl\doc\7.readme\pictrue\Snipaste_2024-11-30_11-18-49.png)

使用的堆栈大小

```S

Stack_Size		EQU     0x1000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp
                                                  
; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size      EQU     0x1000
```

修改任务的堆栈大小，程序正常运行不再死机

```C
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 8,
  .priority = (osPriority_t) osPriorityNormal,
};
```

尝试使用void vTaskList( signed char *pcWriteBuffer );获取任务堆栈情况，先打开相关函数

```
INCLUDE_xTaskGetIdleTaskHandle 1
configUSE_TRACE_FACILITY 1
configUSE_STATS_FORMATTING_FUNCTIONS 1
configUSE_IDLE_HOOK 1

#include "task.h"
void vApplicationIdleHook(void)
{
	/*
		1.执行低优先级，或后台需要不停处理的功能代码
		2.测试系统处理裕量（内核执行空闲任务时间越长表示内核越空闲）
		3.将处理器配置到低功耗模式（Tickless模式）
	*/
  char *buffer = (char*)malloc(512);
  vTaskList(buffer);
  
  printf("%s",buffer);
  
  free(buffer);
  
}

```

第一列          第二列                  第三列              第四列

 task name    task 当前状态      task 优先级       最小剩余 task 栈空间，字节为单位

https://www.cnblogs.com/seelylin/p/16617423.html

第一列: task name
即 xTaskCreate 创建该 task 时第二个参数。
如果名称过长，会根据 configMAX_TASK_NAME_LEN 截断。

第二列: task 当前状态

X: running
B: blocked
R: ready
D: deleted
S: suspended

第三列: task 优先级
即 xTaskCreate 创建该 task 时第四个参数。
数字越大，优先级越高，建议客户设置 task 优先级在 1-9 之间，慎行！

第四列: 最小剩余 task 栈空间，字节为单位
在 xTaskCreate 创建 task 时，给定的第三个参数值代表该 task 调度和运行过程中，最大可用 task 栈空间，以字节为单位(读者可以修改 portSTACK_TYPE 宏来决定是否以字节还是4字节为单位);
Task 如果 API 调用比较深，则使用的栈空间越大，也就意味着最小剩余 task 栈空间越小。

高能预警，做好笔记，熟读三遍：
A: 当某个 task 最小剩余 task 栈空间比较大时，适当减小 xTaskCreate 创建该 task 时给定的第三个参数值，可节约 DRAM，以优化系统内存。

B: 当某个 task 最小剩余 task 栈空间比较小时，适当增大 xTaskCreate 创建该 task 时给定的第三个参数值，可降低 task 栈溢出风险。

C: 如果对 SDK 没有深入了解，不要修改 系统 task 优先级和分配的最大可用栈空间。

D: 不要在系统 task 的 callback 函数里，添加过多代码，不要添加阻塞操作。

第五列: task 创建顺序

///////////////////////
IDLE           	  X	0	37	4
KeyTask        	B	24	96	2
LcdTask        	B	24	70	3
LedTask        	B	24	86	1
Tmr Svc        	B	2	221	5
///////////////////////

发现少了defaulttask 调节它的任务堆栈大小，发现调到128*4后能够正常出现，后来发现总configTOTAL_HEAP_SIZE 设置为3072，过小虽然heap和statck应该是两个东西，但是调大后能够创建了

```C
#define configTOTAL_HEAP_SIZE                    ((size_t)5120)
```

///////////////////////
IDLE           	X	0	36	5
KeyTask        	B	24	86	2
LcdTask        	B	24	70	3
defaultTask    	B	24	228	4
LedTask        	B	24	96	1
Tmr Svc        	B	2	221	6

因此前面设置为256 * 8导致任务未创建而不死机

可以看到再次异常信息，因此是任务堆栈不够导致

///////////////////////
IDLE           	X	0	36	5
KeyTask        	B	24	96	2
              	B	24	0	0
defaultTask    	B	24	0	4
LedTask        	B	24	96	1
Tmr Svc        	B	2	221	6

///////////////////////
IDLE           	X	0	36	5
KeyTask        	B	24	96	2
7ギ腊        	B	24	0	2779096485
defaultTask    	B	24	0	4
LedTask        	B	24	96	1
Tmr Svc        	B	2	221	6

固件名称：mini_control，硬件版本号：1.0，软件版本号：1.0
在线程(IDLE)中发生错误异常
========================= 寄存器信息 =========================
R0 : 02aea53a  R1 : 20005350  R2 : 00000001  R3 : 00000002

R12: 000003e8  LR : 080110af  PC : 0800fea4  PSR: 41000000

发生总线错误，原因：精确的数据总线错误
发生总线错误的地址：02aea53a
查看更多函数调用栈信息，请运行：addr2line -e mini_control.axf -afpiC 0800fea4 080110ae 0800fa98 080109c8 08011120 08010ad6 0800f676 0800fec8 

设定为128 * 16后，空间就绰绰有余

///////////////////////
IDLE           	X	0	36	5
KeyTask        	B	24	96	2
LcdTask        	B	24	70	3
defaultTask    	B	24	247	4
LedTask        	B	24	96	1
Tmr Svc        	B	2	221	6
///////////////////////
IDLE           	X	0	36	5
KeyTask        	B	24	96	2
LcdTask        	B	24	70	3
defaultTask    	B	24	251	4
LedTask        	B	24	96	1
Tmr Svc        	B	2	221	6

## 四线调试问题

尝试使用4线模式，但是一直无法成功，卡在初始化4线模式处

四线模式初始化的过程为

在一线模式下，发送命令开启四线模式，据说速度不能大于400Khz

尝试过降低速度后无效果

在设置四线模式的函数中SD_WideBus_Enable的SD_FindSCR获取不到回复

```C
  while(!__HAL_SD_GET_FLAG(hsd, SDIO_FLAG_RXOVERR | SDIO_FLAG_DCRCFAIL | SDIO_FLAG_DTIMEOUT))
  {
    if(__HAL_SD_GET_FLAG(hsd, SDIO_FLAG_RXDAVL))
    {
      *(tempscr + index) = SDIO_ReadFIFO(hsd->Instance);
      index++;
    }
    else if(!__HAL_SD_GET_FLAG(hsd, SDIO_FLAG_RXACT))
    {
      break;
    }

    if((HAL_GetTick() - tickstart) >=  SDMMC_DATATIMEOUT)
    {
      return HAL_SD_ERROR_TIMEOUT;
    }
  }
```

注释中描述是无法使用四线模式

```C
  /* If requested card supports wide bus operation */
return HAL_SD_ERROR_REQUEST_NOT_APPLICABLE;
```

姑且认为是这个原因，暂时也没换其他sd试试，目前这个sd卡也比较便宜，使用1线是可以正常用的

## 速度

hsd.Init.ClockDiv = 6;好像只有某些值能用
