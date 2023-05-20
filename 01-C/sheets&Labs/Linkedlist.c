
#include"Linkedlist.h"

node_t*list_createNode(int data)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));

    new_node->data = data;
    new_node->next = NULLPTR;

    return new_node;
}

void list_addNodeToLast(node_t*head , int data)
{
    node_t *new_node = list_createNode(data);
    node_t *current = head;

    while(current->next != NULLPTR)
    {
        current = current->next;
    }
    current->next = new_node;
}

void list_addNodeToLast2(node_t**phead , int data)
{
    node_t *new_node = list_createNode(data);
    node_t *current = *phead;

    if(*phead == NULLPTR)
    {
        *phead = new_node;
        return;
    }

    while(current->next != NULLPTR)
    {
        current = current->next;
    }
    current->next = new_node;
}

void list_print(node_t *head)
{
    node_t *current = head;

    while(current != NULLPTR)
    {
        printf("%d\n",current->data);
        current = current->next;
    }
    printf("==============================\n");
}
int list_editByData(node_t *head , int oldData , int NewData)
{
    node_t *current = head;
    char flag = 0;
    if(head == 0)
    {
        return -1;
    }
    while(current != NULLPTR)
    {
        if(current->data == oldData)
        {
            current->data = NewData;
            flag = 1;
            break;
        }
        current = current->next;
    }
    return flag;
}

void list_addNodeToFirst(node_t**phead , int data)
{
    node_t *new_node = list_createNode(data);
    new_node->next = *phead;
    *phead = new_node;
}

void list_removeData(node_t**phead , int oldData)
{
    if(*phead == NULLPTR)
    {
        return;
    }
    node_t *current = *phead;
    node_t *temp;
    if(current->data == oldData)
    {
        temp = current;
        *phead = current->next;
        free(temp);
        return;
    }

    while(current->next != NULLPTR)
    {
        if(current->next->data == oldData)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
         current = current->next;
    }
}

void list_insertAfter(node_t**phead , int oldData , int newData)
{
    node_t *new_node = list_createNode(newData);
    node_t *current = *phead;
    node_t *temp;
    while(current != NULLPTR)
    {
        if(current->data == oldData)
        {
            temp = current->next;
            current->next = new_node;
            new_node->next = temp;
            break;
        }
        current = current->next;
    }
}

