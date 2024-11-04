#ifndef _HXZP_RINGBUFF_H
#define _HXZP_RINGBUFF_H


#include <stdio.h>
#include <stdint.h>
#include <string.h>



typedef struct {

    uint8_t in;
    uint8_t out;

    uint32_t esize;
    uint8_t mask;

    void  *data;

}ringbuff;


void ringbuff_init(ringbuff *buff, void *data, uint32_t esize, uint32_t len);
uint8_t ringbuff_getIsEmpty(ringbuff* buff);
uint32_t ringbuff_getRemainingQuantity(ringbuff* buff);
uint32_t ringbuff_getUsedQuantity(ringbuff* buff);
uint32_t ringbuff_put(ringbuff* buff, const void *data, uint32_t len);
uint32_t ringbuff_get(ringbuff* buff, void* data, uint32_t len);


#endif