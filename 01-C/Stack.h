#define STACK_SIZE   4
#define NULLPTR     (void*)0

typedef struct
{
    int *dataArray;
    int sp;
    int stacksize;

}stack_t;

typedef enum{
    STACK_EMPTY=0,
    STACK_FULL=0,
    DONE

}stack_S;

stack_t* stack_create(int size);
stack_S Push(stack_t *ps , int data);
stack_S Pop(stack_t *ps , int *pdata);
//stack_t stack_create(int size);
//stack_S Push(int data);
//stack_S Pop(int *pdata);

