#define QUEUE_SIZE   4


typedef enum{
    Q_EMPTY=0,
    Q_FULL=0,
    Q_DONE

}queue_S;


queue_S  In_queue(int data);
queue_S  De_queue(int *pdata);
