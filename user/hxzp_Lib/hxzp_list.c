#include "hxzp_list.h"


/**
 * @brief       创建一个新的链表
 * @retval      返回创建成功的链表首地址
 * @retval      NULL   创建失败
 */
List *List_Create(void) 
{
    List *head = (List *)malloc(sizeof(List));
    
    if (head == NULL) 
    {
        return NULL;
    }

    head->next = NULL;

    return head;
}


/**
 * @brief  插入新数据到链表的最后,链表头不能为空
 * @param[in]  head 链表头指针
 * @param[in]  data 插入数据
 */
List_Err_e List_Insert(List *head, void *data) 
{
    /*用于储存头已经下一节点切换*/
    List *node = head, *newnode;  
    if (head == NULL) 
    {
        return LIST_ERR;
    }

    /*用于储存插入节点数据*/
    newnode = (List *)malloc(sizeof(List));
    if (newnode == NULL) 
    {
        return LIST_ERR;
    }
    
    while (node->next != NULL) 
    {
        node = node->next;
    }
    
    newnode->data = data;
    newnode->next = NULL;
    node->next = newnode;
    
    return LIST_OK;
}

/**
 * @brief  链表的位置插入
 * @param[in]  head 链表头指针
 * @param[in]  offset 插入位置
 * @param[in]  data 插入数据的指针
 */
List_Err_e List_InsertWithPos(List *head, uint16_t offset, void *data) 
{
    List *node = head, *newnode;

    /*node指针一个个向后找,直到找到了某一个节点*/
    while (node != NULL) 
    {
        node = node->next;

        if((offset--) == 0)
        {
            break;
        }
    }

    /*位置非法不可以插入*/
    if (node == NULL)
    {
        return LIST_ERR;
    }
    /*位置合法*/
    else
    {
        newnode = (List *)malloc(sizeof(List));

        if (newnode == NULL) 
        {
            return LIST_ERR;
        }

        newnode->data = data;  

        /*该位置取缔原本的链接*/
        newnode->next = node->next;
        
        node->next = newnode;

        return LIST_OK;
    }
}

/**
 * @brief  删除链表全部数据，包括自己
 * @param[in]  head 链表头指针
 * @retval RST_EOK 表示删除成功
 * @retval RST_ERROR 表示链表头为空 删除失败
 */
List_Err_e List_Destroy(List *head)
{
    if (head == NULL) 
    {
        return LIST_ERR;
    }
  
    List *node, *next;
  
    /* node 指向 head的后继节点,逐个释放node */
    for (node = head->next; node != NULL; node = next) 
    {
        next = node->next;
        free(node);
    }    
    free(head);
    
    return LIST_OK;
}

/**
 * @brief  检查链表是否为空
 * @param[in]  head 链表头指针
 */
inline uint8_t List_IsEmpty(List *head) 
{
    return head == NULL ? 1 : 0;
}

uint16_t List_GetLength(List *head)
{
    uint16_t Length = 0;
    List *node;
    
    for(node = head->next; node != NULL; node = node->next)
    {
        Length++;
    }
    
    return Length;
}


