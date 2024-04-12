//队列的链式存储结构
//优点：不需要预先指定固定的大小，可以动态地添加和删除元素

#include<stdio.h>
#include<stdlib.h>

#define OK 1;
#define ERROR 0;

//定义队列结点的结构体
typedef struct LinkQueueNode{
    int data;
    struct LinkQueueNode *next;
}LinkQueueNode;

//定义队列的结构体
typedef struct{
    LinkQueueNode *front;//队头指针
    LinkQueueNode *rear;//队尾指针
}LinkQueue;

//初始化队列
void InitQueue(LinkQueue *queue){
    queue->front=NULL;
    queue->rear=NULL;
}

//判断队列是否为空
int EmptyQueue(LinkQueue *queue){
    if(queue->front==NULL){
        return OK;
    }else{
        return ERROR;
    }
}

//入队
int EnQueue(LinkQueue *queue,int e){
    LinkQueueNode *newNode=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));//动态分配结点内存
    if(!newNode){
        printf("malloc ERROR!!!");
        return ERROR;
    }
    newNode->data=e;
    newNode->next=NULL;//新结点初始化时不指向其他结点

    if(EmptyQueue(queue)){
        //队列为空时，队头和队尾都指向新结点
        queue->front=newNode;
        queue->rear=newNode;
        return OK;
    }else{
        queue->rear->next=newNode;//将新节点添加到队尾
        queue->rear=newNode;//队尾指针指向新结点
        return OK;
    }
}

//出队
int DeQueue(LinkQueue *queue){
    if(EmptyQueue(queue)){
        printf("The LinkQueue is empty!!!");
        return ERROR;
    }
    LinkQueueNode *temp=queue->front;//保存要删除的结点
    int temp_data=temp->data;//保存要删除的结点中的数据
    queue->front=queue->front->next;//更新队头指针

    if(queue->front==NULL){
        //如果删除了一个元素之后，整一个队列为空队列，更新队尾指针也为空
        queue->rear=NULL;
    }
    free(temp);
    return temp_data;
}

//销毁队列
int DestroyQueue(LinkQueue *queue){
    LinkQueueNode *temp;
    while(queue->front !=NULL){
        temp=queue->front;
        queue->front=queue->front->next;
        free(temp);//释放每一个结点的内存
    }
    queue->rear=NULL;
    return OK;
}
