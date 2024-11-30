#ifndef _HXZP_RINGBUFF_H
#define _HXZP_RINGBUFF_H


#include <stdio.h>
#include <stdint.h>
#include <string.h>


//typedef enum
//{
//  RINGBUFF_,
//  RINGBUFF_CUT,

//}putType_e;

typedef struct {

    uint32_t in;//数据类型决定最长长度
    uint32_t out;

    uint32_t esize;//数据类型决定最长数据类型
    uint32_t mask;

    void  *data;

//    uint8_t putType;
}ringbuff;


void ringbuff_init(ringbuff *buff, void *data, uint32_t esize, uint32_t len);
uint8_t ringbuff_getIsEmpty(ringbuff* buff);
uint32_t ringbuff_getRemainingQuantity(ringbuff* buff);
uint32_t ringbuff_getUsedQuantity(ringbuff* buff);
uint32_t ringbuff_put(ringbuff* buff, const void *data, uint32_t len);
uint32_t ringbuff_get(ringbuff* buff, void* data, uint32_t len);


#endif