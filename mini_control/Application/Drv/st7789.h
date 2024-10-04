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