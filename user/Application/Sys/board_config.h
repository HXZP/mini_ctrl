//<<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_CONFIG_H
#define __BOARD_CONFIG_H

#define USING_PRINTF_NULL 0
#define USING_PRINTF_UART 1
#define USING_PRINTF_USB  2
#define USING_PRINTF_RTT  3
#define USING_PRINTF_LCD  4

//<s.20> 固件名字
#define HW_NAME "mini_control"
//<s.10> 硬件版本
#define HW_VERSION "1.0"
//<s.10> 软件版本
#define SW_VERSION "1.0"

//<h> 打印信息

// <o>打印方式
// <i>USB串口打印可以由上位机设置波特率
// <0=> 不打印
// <1=> 串口
// <2=> USB
// <3=> RTT
// <4=> LCD
#define SYSTEM_PRINTF_PORT 2


// <q> 打印任务信息
#define USING_PRINTF_TASK_INFO 0

// <q> 打印错误追踪
// <i> configUSE_IDLE_HOOK要置1
#define USING_PRINTF_CMBACKTRACE 1

//</h>

//<h> other
//<o> ADDL <1-255:10>
#define ADDL 1

// <q.1> NLL
// <q.2> NLL
// <q.3> NLL
#define NLL 1


//</h>

#if (USING_PRINTF_TASK_INFO == 1)
  #define INCLUDE_xTaskGetIdleTaskHandle 1
  #define configUSE_TRACE_FACILITY 1
  #define configUSE_STATS_FORMATTING_FUNCTIONS 1
  //#define configUSE_IDLE_HOOK 1 在freertosConfig.h定义
#endif
















#endif


//<<< end of configuration section >>>