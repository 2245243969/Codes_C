//顺序队列的功能
//优点：实现简单，操作高效，入队和出队的时间复杂度均为O(1)
//缺点：固定大小，当队列已满时无法插入新元素，且需要移动元素位置来保持队列的连续性

#include <stdio.h>

#define MAX_SIZE 100

#define OK 1
#define ERROR 0

//定义队列结构体
typedef struct {
    int data[MAX_SIZE];
    int front;//定义队首索引
    int rear;//定义队尾索引
}Queue;

//初始化队列
int InitQueue(Queue *queue){
    queue->front=0;
    queue->rear=0;
    return OK;
}

//判断队列是否为空
int QueueEmpty(Queue *queue){
    if(queue->rear==queue->front){
        return OK;
    }else{
        return ERROR;
    }
}

//判断队列是否已满
int QueueFull(Queue *queue){
    if(queue->front==MAX_SIZE){
        return OK;
    }else{
        return ERROR;
    }
}

//入队
int EnQueue(Queue *queue,int e){
    if(QueueFull(queue)){
        printf("The Queue is full!!!\n");
        return ERROR;
    }
    queue->data[queue->rear]=e;
    queue->rear++;
}

//出队
int DeQueue(Queue *queue){
    if(QueueEmpty(queue)){
        printf("The Queue is empty!!!\n");
        return ERROR;
    }
    int e=queue->data[queue->front];
    queue->front++;
    return e;
}

//获取队列长度
int LengthQueue(Queue *queue){
    int length=queue->rear-queue->front;
    return length;
}

//获取队列的头元素
int HeadQueue(Queue *queue){
    if(QueueEmpty(queue)){
        printf("The Queue is empty!!!\n");
        return ERROR;
    }
    int head = queue->front;
    return head;
}

int main(){
    Queue queue;
    InitQueue(&queue);

    EnQueue(&queue,1);
    EnQueue(&queue,2);
    EnQueue(&queue,3);

    printf("The length of the Queue is:%d\n", LengthQueue(&queue));
    printf("the DeElement is:%d\n", DeQueue(&queue));
    printf("the DeElement is:%d\n", DeQueue(&queue));
    printf("The length of the Queue is:%d\n", LengthQueue(&queue));

    return 0;
}