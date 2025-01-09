#ifndef DRV_USB_H
#define DRV_USB_H

#include "hxzp_lib.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usbd_msc.h"

#define DRV_USB_PACKET_LEN 64


typedef enum
{
  DRV_USB_CDC = 0,
  DRV_USB_MSC,


}drv_usbMode_e;




void Drv_Usb_Init(void);
void Drv_Usb_RxCpltCallback(uint8_t* buff, uint32_t len);

void Drv_Set_UsbMode(drv_usbMode_e mode);
uint8_t Drv_Get_UsbMode(void);


#endif // DRV_LED_H