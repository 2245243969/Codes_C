//关于双向链表的一些功能
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;//存入的数据类型为int型

typedef struct DuLNode{
    ElemType data;//数据域
    struct DuLNode *prior;//指向的直接前域
    struct DuLNode *next;//指向的直接后域
}DuLNode;
typedef struct DuLNode *DuLinkList;//DuLinkList为指向结构体DuLnode的指针类型

//双向链表的初始化
Status InitList(DuLinkList *L){
    //构造一个空的双向链表L
    *L=(DuLinkList)malloc(sizeof(DuLNode));
    (*L)->next=NULL;
    (*L)->prior=NULL;
}

//前插法创建双向链表(如果想依次存入12345，需要依次逆向输入54321）
void CreatList_H(DuLinkList *L, int n){
    DuLinkList p,r;//p为新插入的结点
    *L = (DuLinkList) malloc(sizeof(DuLNode));
    r = *L;
    r->next=NULL;
    r->prior=NULL;
    for (int i = 0; i < n; i++){
        p = (DuLNode *) malloc(sizeof(DuLNode));//为新的p结点动态分配内存
        scanf("%d", &p->data);
        p->next=r->next;
        p->prior=r;
        r->next=p;

    }
}

////后插法创造双向链表（如果想依次存入12345，只需依次正向输入12345）
void CreatList_R(DuLinkList *L, int n){

}

//打印元素
Status PrintElem(DuLinkList *L) {
    DuLinkList p;
    p = (*L)->next;
    while (p) {
        printf("%d", p->data);
        p = p->next;
    }
}

int main(){
    DuLinkList L;
    int n;
    printf("Plsase enter the initial number for the LinkList:");
    scanf("%d", &n);
    InitList(&L);
    CreatList_H(&L,n);
    PrintElem(&L);
}