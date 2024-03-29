//有关顺序栈的一些功能
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int SElemType;
typedef int Status;

typedef struct {
    SElemType *base;//栈的底指针
    SElemType top;//栈的顶指针
    int maxsize;//栈的可用最大容量
}SqStack;

//栈的初始化
Status InitStack(SqStack *S,int maxsize){
    S->base=(int*)malloc(sizeof(int)*maxsize);
    //判断是否初始化失败
    if(!S->base){
        printf("OVERFLOW!!!");
        return ERROR;
    }
    S->maxsize=maxsize;
    S->top = -1;
    return OK;
}

//顺序栈的入栈
Status Push(SqStack *S,SElemType e){
    //判断顺序栈是否已满
    if(S->top==S->maxsize-1){
        printf("The SqStack is fulled!!!");
        return ERROR;
    }
    else{
        S->top++;
        S->base[S->top]=e;
        return OK;
    }
}

//顺序表的出栈
Status Pop(SqStack *S,SElemType *e){
    //判断顺序栈是否为空
    //将栈顶元素出栈。将 top 指针指向的元素取出
    if(S->top==-1){
        printf("The SqStack is emptied!!!");
        return ERROR;
    }else{
    S->top--;
    *e=S->base[S->top];
    return OK;
    }
}

//取栈顶元素
SElemType GetTop(SqStack *S){
    if(S->top!=-1){
        return S->base[S->top];
    }else{
        printf("The SqStack is emptied!!!");
        return ERROR;
    }
}

int main(){
    SqStack S;
    printf("Please enter the maxsize for SqStack:");
    int maxsize;
    scanf("%d",&maxsize);
    InitStack(&S,maxsize);
printf("Please enter the original numer that you want to push into the SqStack:");
int number;
scanf("%d",&number);
for(int i=1;i<=number;i++){
    SElemType e;
    scanf("%d",&e);
    Push(&S,e);
}
return 0;
}