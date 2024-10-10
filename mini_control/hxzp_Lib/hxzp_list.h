#ifndef HXZP_LIST
#define HXZP_LIST

#include "stdint.h"
#include "stdlib.h"

typedef enum{
    
    LIST_OK = 0,    
    LIST_ERR,
    LIST_WARNNING,

}List_Err_e;


/**
 * @brief       链表结构体
 * @details     一个通用数据类型的链表结构，可通过指针储存任意类型的数据。
 */
typedef struct List_s {
    void*  data;
    struct List_s* next;
} List;

List *List_Create(void);
List_Err_e List_Insert(List *head, void *data);
List_Err_e List_InsertWithPos(List *head, uint16_t offset, void *data);
List_Err_e List_Destroy(List *head);
inline uint8_t List_IsEmpty(List *head);
uint16_t List_GetLength(List *head);



#endif

