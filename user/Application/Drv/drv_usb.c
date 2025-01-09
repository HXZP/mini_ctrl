#include "drv_usb.h"

uint8_t u8usbMode = DRV_USB_CDC;
ringbuff usb_rx_ringbuff;
uint8_t usb_rx_data[1024];

void Drv_Usb_Init(void)
{
  ringbuff_init(&usb_rx_ringbuff, usb_rx_data, sizeof(uint8_t), sizeof(usb_rx_data));
    
  MX_USB_DEVICE_Init();
  
  if(u8usbMode == DRV_USB_CDC)
  USBD_CDC.Init(&hUsbDeviceFS,0);
  
  if(u8usbMode == DRV_USB_MSC)
  USBD_MSC.Init(&hUsbDeviceFS,0);
}

void Drv_Usb_RxCpltCallback(uint8_t* buff, uint32_t len)
{ 
  ringbuff_put(&usb_rx_ringbuff, buff, len);
}



void Drv_Set_UsbMode(drv_usbMode_e mode)
{
  u8usbMode = mode;
  
  Drv_Usb_Init();
}

uint8_t Drv_Get_UsbMode(void)
{
  return u8usbMode;
}



