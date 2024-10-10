#include "hxzp_list.h"


/**
 * @brief       ����һ���µ�����
 * @retval      ���ش����ɹ��������׵�ַ
 * @retval      NULL   ����ʧ��
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
 * @brief  ���������ݵ���������,����ͷ����Ϊ��
 * @param[in]  head ����ͷָ��
 * @param[in]  data ��������
 */
List_Err_e List_Insert(List *head, void *data) 
{
    /*���ڴ���ͷ�Ѿ���һ�ڵ��л�*/
    List *node = head, *newnode;  
    if (head == NULL) 
    {
        return LIST_ERR;
    }

    /*���ڴ������ڵ�����*/
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
 * @brief  �����λ�ò���
 * @param[in]  head ����ͷָ��
 * @param[in]  offset ����λ��
 * @param[in]  data �������ݵ�ָ��
 */
List_Err_e List_InsertWithPos(List *head, uint16_t offset, void *data) 
{
    List *node = head, *newnode;

    /*nodeָ��һ���������,ֱ���ҵ���ĳһ���ڵ�*/
    while (node != NULL) 
    {
        node = node->next;

        if((offset--) == 0)
        {
            break;
        }
    }

    /*λ�÷Ƿ������Բ���*/
    if (node == NULL)
    {
        return LIST_ERR;
    }
    /*λ�úϷ�*/
    else
    {
        newnode = (List *)malloc(sizeof(List));

        if (newnode == NULL) 
        {
            return LIST_ERR;
        }

        newnode->data = data;  

        /*��λ��ȡ��ԭ��������*/
        newnode->next = node->next;
        
        node->next = newnode;

        return LIST_OK;
    }
}

/**
 * @brief  ɾ������ȫ�����ݣ������Լ�
 * @param[in]  head ����ͷָ��
 * @retval RST_EOK ��ʾɾ���ɹ�
 * @retval RST_ERROR ��ʾ����ͷΪ�� ɾ��ʧ��
 */
List_Err_e List_Destroy(List *head)
{
    if (head == NULL) 
    {
        return LIST_ERR;
    }
  
    List *node, *next;
  
    /* node ָ�� head�ĺ�̽ڵ�,����ͷ�node */
    for (node = head->next; node != NULL; node = next) 
    {
        next = node->next;
        free(node);
    }    
    free(head);
    
    return LIST_OK;
}

/**
 * @brief  ��������Ƿ�Ϊ��
 * @param[in]  head ����ͷָ��
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


