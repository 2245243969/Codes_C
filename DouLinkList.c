//关于双向链表的一些功能
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Status;
typedef int ElemType;//存入的数据类型为int型

typedef struct DuLNode {
    ElemType data;//数据域
    struct DuLNode *prior;//指向的直接前域
    struct DuLNode *next;//指向的直接后域
} DuLNode;
typedef struct DuLNode *DuLinkList;//DuLinkList为指向结构体DuLnode的指针类型

//双向链表的初始化
Status InitList(DuLinkList *L) {
    //构造一个空的双向链表L
    *L = (DuLinkList) malloc(sizeof(DuLNode));
    (*L)->next = NULL;
    (*L)->prior = NULL;
}

//前插法创建双向链表(如果想依次存入12345，需要依次逆向输入54321）
void CreatList_H(DuLinkList *L, int n) {
    DuLinkList p, r;//p为新插入的结点
    *L = (DuLinkList) malloc(sizeof(DuLNode));
    r = *L;
    r->next = NULL;
    r->prior = NULL;
    for (int i = 0; i < n; i++) {
        p = (DuLNode *) malloc(sizeof(DuLNode));//为新的p结点动态分配内存
        scanf("%d", &p->data);
        if (i == 0) {
            p->next = r->next;
            p->prior = r;
            r->next = p;
        } else {
            p->next = r->next;
            p->prior = r;
            r->next->prior = p;
            r->next = p;
        }
    }
}

////后插法创造双向链表（如果想依次存入12345，只需依次正向输入12345）
void CreatList_R(DuLinkList *L, int n) {
    DuLinkList p;//p为插入的新结点
    DuLinkList r;//r为尾指针
    *L = (DuLinkList) malloc(sizeof(DuLNode));
    (*L)->next = NULL;
    (*L)->prior = NULL;//先建立一个带头结点的空链表
    r = (*L);
    for (int i = 0; i < n; i++) {
        p = (DuLNode *) malloc(sizeof(DuLNode));
        scanf("%d", &p->data);
        p->next = NULL;
        r->next = p;
        p->prior = r;
        r = p;
    }
}

//计算双向链表的长度
Status DuListLength(DuLinkList *L) {
    DuLinkList p;
    p = (*L)->next;
    int length = 0;
    while (p) {
        p = p->next;
        length++;
    }
    return length;
}

//双向链表的插入
//即在带头结点的双向链表中第i个位置之前插入元素e
Status DuListInsert(DuLinkList *L, int i, ElemType e) {
    DuLinkList p, s;
    p = (*L);
    int length = DuListLength(&p);
//判断是不是在链表尾后的一个位置插入元素
    if (i == length + 1) {
        while (p->next) {
            p = p->next;
        }
        s = (DuLNode *) malloc(sizeof(DuLNode));
        s->data = e;
        s->prior = p;
        s->next = NULL;
        p->next = s;
        return OK;
    } else {
        if (i <= length) {
            for(int j=1;j<=i;j++){
                p=p->next;
            }
            s = (DuLNode *) malloc(sizeof(DuLNode));
            s->data = e;
            s->prior = p->prior;
            p->prior->next = s;
            p->prior = s;
            s->next = p;
            return OK;
        } else {
            printf("Insert ERROR!!!");
            return ERROR;
        }
    }

}

//双向链表的删除
//即在带头结点的双向链表中第i个位置删除结点
Status DuLinkListDelete(DuLinkList *L, int i) {
    DuLinkList p;
    p = (*L);
    //判断第i位置在双向链表中存不存在
    if (i == 0) {
        printf("Delete ERROR!!!");
        return ERROR;
    }
    for (int j = 1; j <= i; j++) {
        p = p->next;
        if (!p) {
            printf("Delete ERROR!!!");
            return ERROR;
        }

    }
    if (p->next != NULL) {
        p->prior->next = p->next;
        p->next->prior = p->prior;
        free(p);//判断i位置是不是尾结点
    } else {
        p->prior->next = NULL;
        free(p);

    }
    return OK;
}

//打印元素
Status PrintElem(DuLinkList *L) {
    DuLinkList p;
    p = (*L)->next;
    while (p) {
        printf("%d", p->data);
        p = p->next;
    }
    return OK;
}

int main() {
    DuLinkList L;
    int n;
    printf("Please enter the initial number for the LinkList:");
    scanf("%d", &n);
    InitList(&L);
    CreatList_H(&L, n);
    int length = DuListLength(&L);
    printf("%d\n", length);
    int i;
    ElemType e;
    printf("Please enter the location number of a new DuLNode that you want to delete");
    scanf("%d %d", &i,&e);

    DuListInsert(&L, i,e);
    PrintElem(&L);
    return 0;
}