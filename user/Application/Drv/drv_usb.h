#ifndef DRV_USB_H
#define DRV_USB_H

#include "hxzp_lib.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"


#define DRV_USB_PACKET_LEN 64

void Drv_Usb_Init(void);
void Drv_Usb_RxCpltCallback(uint8_t* buff, uint32_t len);
#endif // DRV_LED_H