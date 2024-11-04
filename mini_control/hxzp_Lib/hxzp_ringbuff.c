#include "hxzp_ringbuff.h"



void ringbuff_init(ringbuff *buff, void *data, uint32_t esize, uint32_t len)
{
    buff->data = data;
    buff->esize = esize;
    buff->mask = len - 1;

    buff->in = 0;
    buff->out = 0;

    memset(buff->data, 0, len * esize);
}

uint8_t ringbuff_getIsEmpty(ringbuff* buff)
{
    /*Пе*/
    if (buff->in == buff->out)
    {
        return 1;
    }
    /*Тњ*/
    else if (buff->in - buff->out >= buff->mask)
    {
        return 0;
    }
    else
    {
        return 0;    
    }

}


uint32_t ringbuff_getRemainingQuantity(ringbuff* buff)
{
    return buff->mask + 1 - (buff->in - buff->out);
}

uint32_t ringbuff_getUsedQuantity(ringbuff* buff)
{
    return buff->in - buff->out;
}

uint32_t ringbuff_put(ringbuff* buff, const void *data, uint32_t len)
{
    if (ringbuff_getRemainingQuantity(buff) < len)
    {
        return 0;
    }

    if ((buff->in & buff->mask) + len > buff->mask) 
    {
        memcpy((uint8_t*)buff->data + (buff->in & buff->mask) * buff->esize, data, (len - (buff->in + len)&buff->mask) * buff->esize);
        memcpy(buff->data,((uint8_t*)data + (len - (buff->in + len)&buff->mask) * buff->esize), ((buff->in + len)&buff->mask) * buff->esize);
    }
    else
    {
        memcpy((uint8_t*)buff->data + (buff->in & buff->mask) * buff->esize, data, len * buff->esize);
    }

    buff->in += len;

    return len;
}

uint32_t ringbuff_get(ringbuff* buff, void* data, uint32_t len)
{
    if (ringbuff_getUsedQuantity(buff) < len)
    {
        return 0;
    }

    if ((buff->out & buff->mask) + len > buff->mask)
    {
        memcpy(data, (uint8_t*)buff->data + (buff->out & buff->mask) * buff->esize, (len - (buff->out + len)&buff->mask) * buff->esize);
        memcpy((uint8_t*)data + (len - (buff->out + len)&buff->mask) * buff->esize, buff->data, ((buff->out + len)&buff->mask) * buff->esize);
    }
    else
    {
        memcpy(data, (uint8_t*)buff->data + (buff->out & buff->mask) * buff->esize, len * buff->esize);
    }

    buff->out += len;

    return len;
}

