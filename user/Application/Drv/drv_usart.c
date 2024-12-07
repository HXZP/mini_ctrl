#include "drv_usart.h"


ringbuff usart3_rx_ringbuff;
uint8_t usart3_rx_data[1024];
uint8_t usart3_rx_buff[1024];

void Drv_Usart_Init(void)
{
  ringbuff_init(&usart3_rx_ringbuff, usart3_rx_data, sizeof(uint8_t), sizeof(usart3_rx_data));
  
  HAL_UARTEx_ReceiveToIdle_IT(&huart3, usart3_rx_buff, sizeof(usart3_rx_buff));
}

uint32_t Drv_Usart_Put(const char *name, const uint8_t *buff, uint32_t len)
{
  uint32_t reslen = 0;
  
  if(strcmp(name, "usart3") == 0)
  {  
    reslen = ringbuff_put(&usart3_rx_ringbuff, buff, len);
  }

  return reslen;
}

uint32_t Drv_Usart_Get(const char *name, uint8_t *buff, uint32_t len)
{
  uint32_t reslen = 0;
  
  if(strcmp(name, "usart3") == 0)
  {  
    reslen = ringbuff_get(&usart3_rx_ringbuff, buff, len);
  }

  return reslen;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if(huart->Instance == USART3)
  {
    Drv_Usart_Put("usart3", usart3_rx_buff, Size);
  
    HAL_UARTEx_ReceiveToIdle_IT(&huart3, usart3_rx_buff, sizeof(usart3_rx_buff));
    
    memset(usart3_rx_buff, 0, sizeof(usart3_rx_buff));
  }

}
