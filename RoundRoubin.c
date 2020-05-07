#include <stdio.h>
#include <stdlib.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct
{
    char *name;
    int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct Node
{
    Item data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node *head;
    Node *tail;
} Queue;
/*
 *
 */
void init(Queue *q)
{
   q->tail=q->head=NULL;

}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(q->head==q->tail==NULL)
        return 1;
    else
        return 0;
}
/*
 *
 */
Item dequeue(Queue *q)
{
    if(isEmpty(q))
    {
        return NULL;
    }
    else
    {
        Item item=malloc(sizeof(Item));
        item=q->head->data;
        Node* n=q->head;
        q->head=q->head->next;
        free(n);
    return item;
    }
}
/*
 *
 */
void enqueue(Queue *q, Item val)
{
    Node *p=malloc(sizeof(Node));
    p->data=val;
    p->next=NULL;
    if(isEmpty(&q))
    {
       q->head=q->tail=p;
       printf("llll");

    }
    else
    {
        q->tail->next=p;
        q->tail=p;
    }
    printf("%s",q->head->data->name);
    printf("%s",q->tail->data->name);


}
/*
 *
 */
void destroy(Queue *q)
{
    while(!isEmpty(&q))
        dequeue(&q);
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    int i=0,x;
    Item val;
    Queue q;
    init(&q);
    FILE *file=fopen(filename,"r");
    while(!feof(file))
    {
        Item item=(Process*)malloc(sizeof(Item));
        item->name=(char*)malloc(sizeof(char));
        fscanf(file,"%s%d%d",item->name,&x,&val->remaining_time);
        if(x==i){
            enqueue(&q,item);
        }

        else
        {
            while(x>=i||!isEmpty(&q))
            {
                if(!isEmpty(&q))
                {
                    printf("idle %d ---> %d\n",i++,i);
                    if(x==i)
                        enqueue(&q,item);


                }

                else
                {

                    val=dequeue(&q);
                    val->remaining_time--;
                    printf("%s %d-->%d\n",val->name,i++,i);
                    if(val->remaining_time==0)
                        printf("%s halts\n",val->name);
                    else
                    {
                        printf("\n");
                        if(x==i)
                            enqueue(&q,item);
                        enqueue(&q,val);
                        printf("aaa");
                    }
                }
            }
        }
    }
}
/*
 *
 */
int main(int argc, char**argv)
{
    if(argc!=2)
    {
        printf("Usage: %s filename \n", argv[0]);
        exit(1);
    }
    printf("%s",argv[1]);
    RoundRobin(argv[1]);

    return 0;
}
