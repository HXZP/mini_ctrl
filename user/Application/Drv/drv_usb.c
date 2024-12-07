#include "drv_usb.h"


ringbuff usb_rx_ringbuff;
uint8_t usb_rx_data[1024];

void Drv_Usb_Init(void)
{
  ringbuff_init(&usb_rx_ringbuff, usb_rx_data, sizeof(uint8_t), sizeof(usb_rx_data));
    
  MX_USB_DEVICE_Init();
  
  USBD_CDC.Init(&hUsbDeviceFS,0);
}

void Drv_Usb_RxCpltCallback(uint8_t* buff, uint32_t len)
{ 
  ringbuff_put(&usb_rx_ringbuff, buff, len);
}