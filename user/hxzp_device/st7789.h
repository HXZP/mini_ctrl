/*
Data:
135*240
8pin

PinMap��
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
RES�͵�ƽ��Ч
�ϵ�����ƽ��λ�������͵�ƽ����Ҫ10us��Ȼ����븴λģʽ����Ҫ�ȴ�5ms��ɳ�ʼ��


��ģ����������ɫģʽ�����ڽ����ݴ��䵽��ʾ RAM��
��Щ��ÿ���� 12 λ��ɫ��ÿ���� 16 λ��ɫ��ÿ���� 18 λ��ɫ��
������ÿ���ӿڵ����ݸ�ʽ������ͨ�� 2 �ַ������������ص�֡�ڴ��С�











*/



















/*

// ST7789 ��ʼ������
void ST7789_Init(void) {
    // ��λ��ʾ��
    GPIO_ResetBits(GPIOA, SPI1_RES_PIN);
    Delay(100); // ��ʱ100ms
    GPIO_SetBits(GPIOA, SPI1_RES_PIN);
    Delay(100); // ��ʱ100ms

    // ���ͳ�ʼ������
    ST7789_WriteCommand(0x01); // �����λ
    Delay(150); // ��ʱ150ms
    ST7789_WriteCommand(0x11); // �˳�˯��ģʽ
    Delay(255); // ��ʱ255ms

    ST7789_WriteCommand(0x36); // �ڴ����ݷ��ʿ���
    ST7789_WriteData(0x00);    // ������ʾ����Ϊ0�ȣ�������

    ST7789_WriteCommand(0x3A); // ������ɫ��ʽ
    ST7789_WriteData(0x05);    // 8λ��ɫ��ʽ

    ST7789_WriteCommand(0xB2); // ����֡�ʿ���
    ST7789_WriteData(0x0C);
    ST7789_WriteData(0x0C);
    ST7789_WriteData(0x00);
    ST7789_WriteData(0x33);
    ST7789_WriteData(0x33);

    ST7789_WriteCommand(0xB7); // ���õ�Դ����
    ST7789_WriteData(0x35);

    ST7789_WriteCommand(0xBB); // ��������
    ST7789_WriteData(0x1A);

    ST7789_WriteCommand(0xC0); // ��Դ����
    ST7789_WriteData(0x2C);

    ST7789_WriteCommand(0xC2); // VDV �� VRH ����
    ST7789_WriteData(0x01);

    ST7789_WriteCommand(0xC3); // VRH ����
    ST7789_WriteData(0x12);    // ����VRH

    ST7789_WriteCommand(0xC4); // VDV ����
    ST7789_WriteData(0x20);

    ST7789_WriteCommand(0xC6); // ֡�ʿ���
    ST7789_WriteData(0x0F);

    ST7789_WriteCommand(0xD0); // ��Դ����
    ST7789_WriteData(0xA4);
    ST7789_WriteData(0xA1);

    ST7789_WriteCommand(0xE0); // ����٤��У��
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

    ST7789_WriteCommand(0xE1); // ����٤��У��
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

    ST7789_WriteCommand(0x21); // �򿪷���

    ST7789_WriteCommand(0x29); // ����ʾ
    Delay(100);

    // �����е�ַ
    ST7789_WriteCommand(0x2A); // �е�ַ����
    ST7789_WriteData(0x00); // ��ʼ�е�ַ��λ
    ST7789_WriteData(0x00); // ��ʼ�е�ַ��λ
    ST7789_WriteData(0x00); // �����е�ַ��λ
    ST7789_WriteData(0xEF); // �����е�ַ��λ��240 �У�

    // �����е�ַ
    ST7789_WriteCommand(0x2B); // �е�ַ����
    ST7789_WriteData(0x00); // ��ʼ�е�ַ��λ
    ST7789_WriteData(0x00); // ��ʼ�е�ַ��λ
    ST7789_WriteData(0x00); // �����е�ַ��λ
    ST7789_WriteData(0xC5); // �����е�ַ��λ��198 �У�

    ST7789_WriteCommand(0x2C); // �ڴ�д��
}




*/