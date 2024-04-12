//循环列表的一些功能
//循环列表的优点：解决了普通列表在出队操作后浪费存储空间的问题
//适用：需要频繁进行入队和出队操作的场景，例如消息队列，任务调度等
//特点：队尾和队头可以通过取模运算实现循环的移动

#include <stdio.h>

#define MAX_SIZE 100

#define OK 1
#define ERROR 0

typedef struct {
    int data[MAX_SIZE];
    int front;//队首指引
    int rear;//队尾指引
    int size;//直接用size来记录存储的数据的多少，简化空和满的判断
}CircularQueue;

//初始化循环队列
int InitQueue(CircularQueue *queue){
    queue->front=0;
    queue->rear=0;
    queue->size=0;
    return OK;
}

//判断循环队列是否为空
int EmptyQueue(CircularQueue *queue){
    if(queue->size==0){
        return OK;
    }else;{
        return ERROR;
    }
}

//判断循环列表是否为满
int FullQueue(CircularQueue *queue){
    if(queue->size==MAX_SIZE){
        return OK;
    }else{
        return ERROR;
    }
}

//入队
int EnQueue(CircularQueue *queue,int e){
    if(FullQueue(queue)){
        printf("The CircularQueue is full!!!");
        return ERROR;
    }else{
        queue->data[queue->rear]=e;
        queue->rear=(queue->rear+1)%MAX_SIZE;
        queue->size++;
        return OK;
    }
}

//出队
int DeQueue(CircularQueue *queue){
    if(EmptyQueue(queue)){
        printf("The CircularQueue is empty!!!");
        return ERROR;
    }else{
        int e=queue->data[queue->front];
        queue->front=(queue->front+1)%MAX_SIZE;
        queue->size--;
        return e;
    }
}

//获取队列长度
int LengthQueue(CircularQueue *queue){
    return queue->size;
}

int main(){
    CircularQueue queue;
    InitQueue(&queue);

    EnQueue(&queue,1);
    EnQueue(&queue,2);
    EnQueue(&queue,3);
    EnQueue(&queue,4);

    printf("The length of the CircularQueue is:%d\n", LengthQueue(&queue));

    printf("The De_element is:%d\n", DeQueue(&queue));
    printf("The De_element is:%d\n", DeQueue(&queue));
    return 0;
}

