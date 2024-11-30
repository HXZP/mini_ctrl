# 已解决问题

## 烧录调试

芯片无法识别问题，无法烧录

原因：swd的22R电阻未焊接，boot0上拉电阻未连接导致悬空

## 按键调试

波轮按钮不知名原因cw方向和VCC导通导致电平无法变化，更换pcb后正常

普通按钮一直处于导通状态，原因是按钮四个引脚，有两个引脚是从前方金属外壳导出，选型问题

## LCD调试

屏幕按照手册协议通信后花屏

原因：协议理解问题，设置区域后要发送颜色，颜色才是实际数据，设置区域只是选择更新范围

##  cubemx生成错误

1、更换Middlewares\Third_Party\FreeRTOS\Source\portable\RVDS中的ARM_CM3为副本

 2、sd卡相关：Middlewares\Third_Party\FatFs\src\option中syscall.c更改

# 进度

烧录

freertos

led

按键

lcd刷屏

sd卡+fatfs

usb串口

# TODO

串口系统

lcd字符显示

sd卡数据文件系统设计

usb通信以及切换hid功能

tof

imu焊接
