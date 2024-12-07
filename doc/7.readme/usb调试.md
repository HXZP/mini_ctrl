# USB硬件

必须要有外部时钟

要加两个电阻，负责电脑无法识别

# USB识别号

USB_DESC_TYPE_DEVICE

3为固定COM口

0为根据在电脑上的接口而变化COM口，多设备同一个接口为同一个COM口

```C
__ALIGN_BEGIN uint8_t USBD_FS_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END =
{
  0x12,                       /*bLength */
  USB_DESC_TYPE_DEVICE,       /*bDescriptorType*/
  0x00,                       /*bcdUSB */
      
```

## 修改名字

usbd_desc文件

```C
#define USBD_VID     1155
#define USBD_LANGID_STRING     1033
#define USBD_MANUFACTURER_STRING     "STMicroelectronics"
#define USBD_PID_FS     22336
#define USBD_PRODUCT_STRING_FS     "STM32 Virtual ComPort"
#define USBD_CONFIGURATION_STRING_FS     "CDC Config"
#define USBD_INTERFACE_STRING_FS     "CDC Interface"


```

VID:

http://www.linux-usb.org/usb.ids



```C
设备描述符:

长度(bLength): 18 字节
描述符类型(bDescriptorType): 0x01
设备版本(bcdDevice)
供应商 ID(idVendor)
产品 ID(idProduct)
设备类别(bDeviceClass)
设备子类别(bDeviceSubClass)
设备协议(bDeviceProtocol)
最大数据包大小(bMaxPacketSize0)
厂商字符串描述符索引(iManufacturer)
产品字符串描述符索引(iProduct)
序列号字符串描述符索引(iSerialNumber)
配置数量(bNumConfigurations)
配置描述符:

长度(bLength): 9 字节
描述符类型(bDescriptorType): 0x02
总长度(wTotalLength)
接口数量(bNumInterfaces)
配置值(bConfigurationValue)
配置字符串描述符索引(iConfiguration)
特性(bmAttributes)
最大电流(bMaxPower)
接口描述符:

长度(bLength): 9 字节
描述符类型(bDescriptorType): 0x04
接口编号(bInterfaceNumber)
备用设置(bAlternateSetting)
端点数量(bNumEndpoints)
接口类别(bInterfaceClass)
接口子类别(bInterfaceSubClass)
接口协议(bInterfaceProtocol)
接口字符串描述符索引(iInterface)
端点描述符:

长度(bLength): 7 字节
描述符类型(bDescriptorType): 0x05
端点地址(bEndpointAddress)
端点特性(bmAttributes)
最大数据包大小(wMaxPacketSize)
端点间隔(bInterval)
字符串描述符:

长度(bLength)
描述符类型(bDescriptorType): 0x03
字符串数据(bString)
————————————————

                            版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
                        
原文链接：https://blog.csdn.net/qq_39258454/article/details/140241535
```

# 初始化问题

还要初始化 USBD_CDC.Init(&hUsbDeviceFS,0);

```C
  MX_USB_DEVICE_Init();
  
  USBD_CDC.Init(&hUsbDeviceFS,0);
```

