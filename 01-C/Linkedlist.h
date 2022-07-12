
#define NULLPTR   (void*)0

typedef struct node
{
    int data;
    struct node* next;

}node_t;

node_t*list_createNode(int data);
void list_addNodeToLast(node_t*head , int data);
void list_addNodeToLast2(node_t**phead , int data);
void list_addNodeToFirst(node_t**head , int data);
void list_print(node_t *head);
int  list_editByData(node_t *head , int oldData , int NewData);
void list_removeData(node_t**phead , int oldData);
void list_insertAfter(node_t**phead , int oldData , int newData);
