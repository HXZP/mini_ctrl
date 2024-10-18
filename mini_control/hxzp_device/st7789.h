/*
Data:
135*240
8pin

PinMap：
1.LEDA
2.GND
3.RESET
4.RS
5.SDA
6.SCL
7.VDD
8.CS

PC5 RES
PA5 SCK
PA7 SDA
PC4 A0(WRX)

Congfigue:
- Half-Duplex
- CPOL/CPHA:0/0 (The driver samples the SDA (input data) at rising edge of SCL, but shifts SDA (output data) at the falling edge of SCL.
- First Bit:High(The MSB is transmitted first. 

CS:
A falling edge on CSX enables the serial interface and indicates the start of data transmission.

WRX 
Data is regarded as a command when WRX is low 
Data is regarded as a parameter or data when WRX is high
0:command
1:data

Read Function
To achieve read function, the micro controller first has to send a command (read ID or register command) and 
then the following byte is transmitted in the opposite direction. 

Mode Enter
2-wire data lane serial interface use: CSX (chip enable), DCX (serial clock) and SDA (serial data 
input/output 1), and WRX (serial data input 2). To enter this interface, command E7h need set 10h.

Reset
RES低电平有效
上电拉电平复位操作，低电平至少要10us，然后进入复位模式，需要等待5ms完成初始化


该模块有三种颜色模式，用于将数据传输到显示 RAM。
这些是每像素 12 位颜色、每像素 16 位颜色和每像素 18 位颜色。
描述了每个接口的数据格式。可以通过 2 种方法将数据下载到帧内存中。











*/



















/*

// ST7789 初始化函数
void ST7789_Init(void) {
    // 复位显示器
    GPIO_ResetBits(GPIOA, SPI1_RES_PIN);
    Delay(100); // 延时100ms
    GPIO_SetBits(GPIOA, SPI1_RES_PIN);
    Delay(100); // 延时100ms

    // 发送初始化命令
    ST7789_WriteCommand(0x01); // 软件复位
    Delay(150); // 延时150ms
    ST7789_WriteCommand(0x11); // 退出睡眠模式
    Delay(255); // 延时255ms

    ST7789_WriteCommand(0x36); // 内存数据访问控制
    ST7789_WriteData(0x00);    // 设置显示方向为0度（横屏）

    ST7789_WriteCommand(0x3A); // 设置颜色格式
    ST7789_WriteData(0x05);    // 8位颜色格式

    ST7789_WriteCommand(0xB2); // 设置帧率控制
    ST7789_WriteData(0x0C);
    ST7789_WriteData(0x0C);
    ST7789_WriteData(0x00);
    ST7789_WriteData(0x33);
    ST7789_WriteData(0x33);

    ST7789_WriteCommand(0xB7); // 设置电源控制
    ST7789_WriteData(0x35);

    ST7789_WriteCommand(0xBB); // 电量控制
    ST7789_WriteData(0x1A);

    ST7789_WriteCommand(0xC0); // 电源控制
    ST7789_WriteData(0x2C);

    ST7789_WriteCommand(0xC2); // VDV 和 VRH 设置
    ST7789_WriteData(0x01);

    ST7789_WriteCommand(0xC3); // VRH 设置
    ST7789_WriteData(0x12);    // 设置VRH

    ST7789_WriteCommand(0xC4); // VDV 设置
    ST7789_WriteData(0x20);

    ST7789_WriteCommand(0xC6); // 帧率控制
    ST7789_WriteData(0x0F);

    ST7789_WriteCommand(0xD0); // 电源控制
    ST7789_WriteData(0xA4);
    ST7789_WriteData(0xA1);

    ST7789_WriteCommand(0xE0); // 正极伽玛校正
    ST7789_WriteData(0xD0);
    ST7789_WriteData(0x04);
    ST7789_WriteData(0x0D);
    ST7789_WriteData(0x11);
    ST7789_WriteData(0x13);
    ST7789_WriteData(0x2B);
    ST7789_WriteData(0x3F);
    ST7789_WriteData(0x54);
    ST7789_WriteData(0x4C);
    ST7789_WriteData(0x18);
    ST7789_WriteData(0x0D);
    ST7789_WriteData(0x0B);
    ST7789_WriteData(0x1F);
    ST7789_WriteData(0x23);

    ST7789_WriteCommand(0xE1); // 负极伽玛校正
    ST7789_WriteData(0xD0);
    ST7789_WriteData(0x04);
    ST7789_WriteData(0x0C);
    ST7789_WriteData(0x11);
    ST7789_WriteData(0x13);
    ST7789_WriteData(0x2C);
    ST7789_WriteData(0x3F);
    ST7789_WriteData(0x44);
    ST7789_WriteData(0x51);
    ST7789_WriteData(0x2F);
    ST7789_WriteData(0x1F);
    ST7789_WriteData(0x1F);
    ST7789_WriteData(0x20);
    ST7789_WriteData(0x23);

    ST7789_WriteCommand(0x21); // 打开反显

    ST7789_WriteCommand(0x29); // 打开显示
    Delay(100);

    // 设置列地址
    ST7789_WriteCommand(0x2A); // 列地址设置
    ST7789_WriteData(0x00); // 起始列地址高位
    ST7789_WriteData(0x00); // 起始列地址低位
    ST7789_WriteData(0x00); // 结束列地址高位
    ST7789_WriteData(0xEF); // 结束列地址低位（240 列）

    // 设置行地址
    ST7789_WriteCommand(0x2B); // 行地址设置
    ST7789_WriteData(0x00); // 起始行地址高位
    ST7789_WriteData(0x00); // 起始行地址低位
    ST7789_WriteData(0x00); // 结束行地址高位
    ST7789_WriteData(0xC5); // 结束行地址低位（198 行）

    ST7789_WriteCommand(0x2C); // 内存写入
}




*/