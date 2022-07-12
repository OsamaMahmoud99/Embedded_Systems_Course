#include "Stack.h"

static int Stack[STACK_SIZE];
static int sp = 0;

stack_t* stack_create(int size)
{
    stack_t* s = malloc(sizeof(stack_t));
    s->dataArray = malloc(size*sizeof(int));
    s->sp = 0;
    s->stacksize = size;
    return s;
}
void stack_delete(stack_t* s)
{
    free(s->dataArray);
    free(s);
}
/*stack_t stack_create(int size)
{
    stack_t s;
    s.dataArray = malloc(size*sizeof(int));
    s.sp = 0;
    s.stacksize = size;
    return s;
}
*/

/*void stack_delete(stack_t s)
{
    free(s.dataArray);
}
*/

stack_S Push(stack_t *ps , int data)
{
    stack_S status = DONE;
    if((ps->sp) == (ps->stacksize))
    {
        status = STACK_FULL;
    }
    else
    {
        ps->dataArray[ps->sp] = data;
        ps->sp++;
        status = DONE;
    }

    return status;
}
stack_S Pop(stack_t *ps , int *pdata)
{
    stack_S status = DONE;
    if(ps->sp == 0)
    {
        status = STACK_EMPTY;
    }
    else
    {
        ps->sp--;
        *pdata = ps->dataArray[ps->sp];
        status = DONE;
    }
    return status;

}
/*stack_S Push(int data)
{
    stack_S status = DONE;
    if(sp == STACK_SIZE)
    {
        status = STACK_FULL;
    }
    else
    {
        Stack[sp] = data;
        sp++;
        status = DONE;
    }

    return status;
}
*/
/*stack_S Pop(int *pdata)
{
    stack_S status = DONE;
    if(sp == 0)
    {
        status = STACK_EMPTY;
    }
    else
    {
        sp--;
        *pdata = Stack[sp];
        status = DONE;
    }
    return status;

}
*/
