//有关单链表的一些功能（带头结点）

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;//存入的数据类型为int型

typedef struct LNode {
    ElemType data;//结点的数据域
    struct LNode *next;//结点的指针域
} LNode;
typedef struct LNode *LinkList;//LinkList为指向结构体LNode的指针类型

//链表的初始化
Status InitList(LinkList *L) {
    //构造一个空的单链表L
    *L = (LinkList) malloc(sizeof(LNode));//产生头节点，使L指向头节点
    (*L)->next = NULL;//头结点的指针域为空
    return 0;
}

//前插法创建单链表(如果想依次存入12345，需要依次逆向输入54321）
void CreatList_H(LinkList *L, int n) {
    LinkList p, r;//p为插入的新结点
    *L = (LinkList) malloc(sizeof(LNode));
    r = *L;
    r->next = NULL;
    for (int i = 0; i < n; i++) {
        p = (LNode *) malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = NULL;
        p->next = r->next;
        r->next = p;
    }
}

//后插法创造单链表（如果想依次存入12345，只需依次正向输入12345）
void CreatList_R(LinkList *L, int n) {
    LinkList p;//p为插入的新结点
    LinkList r;//r为尾指针
    *L = (LinkList) malloc(sizeof(LNode));
    (*L)->next = NULL;//先建立一个带头结点的空链表
    r = (*L);
    for (int i = 0; i < n; i++) {
        p = (LNode *) malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = NULL;
        r->next = p;
        r = p;
    }
}

//求单链表的长度
int ListLength(LinkList *L) {
    LinkList p;//用于指向除头结点以外的结点
    int count = 0;
    p = (*L)->next;
    while (p) {
        count++;
        p = p->next;
    }
    return count;
}

//单链表的销毁（需要一个一个结点的销毁）
Status DestoryList(LinkList *L) {
    LinkList p = *L;
    while (*L) {
        *L = (*L)->next;
        free(p);
        p = *L;
    }
    return OK;
}

//在链表中插入新元素
//即将值为e的新节点插入表中的第i个结点的位置
Status ListInsert(LinkList *L, int i, ElemType e) {
    LinkList p, q;
    p = *L;//指向头结点
    //建立并初始化需要插入的结点，用指针q指向它
    q = (LNode *) malloc(sizeof(LNode));
    q->data = e;
    q->next = NULL;

    for (int j = 0; p && j < i - 1; j++) {
        if (i > ListLength(L) + 1) {
            return ERROR;
        }
        p = p->next;
    }
    //将新结点与前后结点相关联
    q->next = p->next;
    p->next = q;
    return OK;
}

//在链表中删除某一个元素
Status deleElem(LinkList *L,int i){
    LinkList p,q;
    p =(*L);
    //将p移动到要删除结点的前一个结点
    int j=0;
    for(j;p&&j<j-1;j++){
        p=p->next;
    }
    if(!(p->next)||(j>i-1)){
        return ERROR;
    }
    q=p->next;
    p->next=q->next;
    free(q);
    return OK;
}

//打印元素
Status PrintElem(LinkList *L) {
    LinkList p;
    p = (*L)->next;
    while (p) {
        printf("%d", p->data);
        p = p->next;
    }
}


int main() {
    LinkList L;
    int n;
    printf("Plsase enter the initial number for the LinkList:");
    scanf("%d", &n);
    InitList(&L);
    CreatList_R(&L, n);
    int i;
    ElemType e;
    printf("Please enter the location number of a new Lnode that you want to insret");
    scanf("%d", &i);
    printf("Please enter an element for the new Lnode data");
    scanf("%d", &e);
    ListInsert(&L, i, e);
    PrintElem(&L);
    return 0;
}
