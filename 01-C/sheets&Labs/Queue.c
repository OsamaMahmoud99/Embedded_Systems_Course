
#include "Queue.h"


static int Queue[QUEUE_SIZE];
static int In = 0;
static int Out = 0;
static int C_flag = 0;



queue_S  In_queue(int data)
{
    queue_S status = Q_DONE;
    if(In == QUEUE_SIZE)
    {
        In = 0;
        C_flag = 1;
    }
    if((In == Out) && (C_flag==1))
    {
        status = Q_FULL;
    }
    else
    {
        Queue[In] = data;
        In++;
        status = Q_DONE;
    }
    return status;
}

queue_S  De_queue(int *pdata)
{
    queue_S status = Q_DONE;
    if((In == Out)&&(C_flag == 0))
    {
        status = Q_EMPTY;
    }
    else
    {
        *pdata = Queue[Out];
        Out++;
        status = Q_DONE;
    }

    if(Out == QUEUE_SIZE)
    {
        Out = 0;
        C_flag = 0;
    }

    return status;
}
