//有关单链表的一些功能（带头结点）

#include <stdio.h>
#include <stdlib.h>

#define OK 1

typedef int Status;
typedef int ElemType;//存入的数据类型为int型

typedef struct LNode{
    ElemType data;//结点的数据域
    struct LNode *next;//结点的指针域
}LNode;
typedef struct LNode *LinkList;//LinkList为指向结构体LNode的指针类型

//链表的初始化
Status InitList(LinkList *L){
    //构造一个空的单链表L
    *L=(LinkList)malloc(sizeof(LNode));//产生头节点，使L指向头节点
    (*L)->next=NULL;//头结点的指针域为空
    return 0;
}

//前插法创建单链表(如果想依次存入12345，需要依次逆向输入54321）
void CreatList_H(LinkList* L,int n){
    LinkList p;//p为插入的新结点
    *L=(LinkList)malloc(sizeof(LNode));
    (*L)->next=NULL;//先建立一个带头结点的空链表
    for(int i=0;i<n;i++){
        p=(LNode *)malloc(sizeof(LNode));
        scanf("%d",&p->data);
        p->next=NULL;
        (*L)->next=p;//头结点的指针域为新的结点p的地址
    }
}

//后插法创造单链表（如果想依次存入12345，只需依次正向输入12345）
void CreatList_R(LinkList* L,int n){
    LinkList p;//p为插入的新结点
    LinkList r;//r为尾指针
    *L=(LinkList)malloc(sizeof(LNode));
    (*L)->next=NULL;//先建立一个带头结点的空链表
    r=(*L);
    for(int i=0;i<n;i++){
        p=(LNode *)malloc(sizeof(LNode));
        scanf("%d",&p->data);
        p->next=NULL;
        r->next=p;
        r=p;
    }
}

//单链表的销毁（需要一个一个结点的销毁）
Status DestoryList(LinkList* L){
    LinkList p=*L;
    while(*L){
        *L=(*L)->next;
        free(p);
        p=*L;
    }
    return OK;
}


int main(){
    return 0;
}
