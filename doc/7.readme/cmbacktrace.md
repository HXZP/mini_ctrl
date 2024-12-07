# cmbacktrace使用

为了适配freertos要修改task .c文件，见doc文件夹

有五处改动

```C
/*< Support For CmBacktrace >*/
uint32_t * vTaskStackAddr()
{
    return pxCurrentTCB->pxStack;
}

uint32_t vTaskStackSize()
{
    #if ( portSTACK_GROWTH > 0 )
    
    return (pxNewTCB->pxEndOfStack - pxNewTCB->pxStack + 1);
    
    #else /* ( portSTACK_GROWTH > 0 )*/
    
    return pxCurrentTCB->uxSizeOfStack;
    
    #endif /* ( portSTACK_GROWTH > 0 )*/
}

char * vTaskName()
{
    return pxCurrentTCB->pcTaskName;
}
/*-----------------------------------------------------------*/

```

```C
typedef struct tskTaskControlBlock中添加

#if( portSTACK_GROWTH <= 0)
UBaseType_t     uxSizeOfStack;      /*< Support For CmBacktrace >*/
#endif
```

```C
static void prvInitialiseNewTask中添加

pxNewTCB->uxSizeOfStack = ulStackDepth;   /*< Support For CmBacktrace >*/
```

```C
typedef struct xSTATIC_TCB中添加

#if(portSTACK_GROWTH <= 0)
        UBaseType_t     uxSizeOfStack;      /*< Support For CmBacktrace >*/
#endif /* ( portSTACK_GROWTH > 0 )*/
```

```c
601    /*该检查会导致无法使用cmbacktrace，因为修改了TCB_T*/
602 //			configASSERT( xSize == sizeof( TCB_t ) )
```

将串口打印的内容复制到MDK_ARM下中编译生成的mini_control内打开cmd，在这里才能找到axf文件，就能看到更加具体的原因

```C
固件名称：mini_control，硬件版本号：1.0，软件版本号：1.0
在线程(IDLE)中发生错误异常
========================= 寄存器信息 =========================
R0 : 02aea53a  R1 : 20005350  R2 : 00000001  R3 : 00000002

R12: 000003e8  LR : 080110af  PC : 0800fea4  PSR: 41000000

发生总线错误，原因：精确的数据总线错误
发生总线错误的地址：02aea53a
查看更多函数调用栈信息，请运行：addr2line -e mini_control.axf -afpiC 0800fea4 080110ae 0800fa98 080109c8 08011120 08010ad6 0800f676 0800fec8 
```

![Snipaste_2024-11-30_11-18-49](D:\Aproject\foc\mini_ctrl\doc\7.readme\pictrue\Snipaste_2024-11-30_11-18-49.png)



通过include进行复制

![image-20241203003111661](D:\Aproject\foc\mini_ctrl\doc\7.readme\pictrue\image-20241203003111661.png)

![image-20241203003135646](D:\Aproject\foc\mini_ctrl\doc\7.readme\pictrue\image-20241203003135646.png)
