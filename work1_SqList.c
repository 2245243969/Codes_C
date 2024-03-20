/*给定一个顺序存储的线性表L={a1,a2,...,an},请设计一个算法查找该线性表中最长的递增子序列。例如（1，9，2，5，7，3，4，6，9，0)中最长的递增子序列是(3,4,6,9)*/
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define InitSize 1000

typedef struct {
    ElemType *data;
    int MaxSize;
    int length;
} SqList;

void InitList(SqList *L) {
    L->data = (int *) malloc(sizeof(int) * InitSize);
    L->MaxSize = InitSize;
    L->length = 0;

    if (L->data == NULL) {
        printf("initialization failed\n");
    }
}

void FilledList(SqList *L, int n) {
    for (int i = 0; i < n; i++) {
        int number = 0;
        scanf("%d", &L->data[i]);
        L->length++;
    }

}

int main() {
    SqList L;
    InitList(&L);
    int n;
    printf("Please enter the size for the SpList:");
    scanf("%d", &n);
    if (n > InitSize) {
        printf("The size is bigger than the max store space");
    }
    FilledList(&L, n);
    int maxcount = 0;
    int count = 1;
    int *Max_data_address;

    for (int i = 1; i < n; i++) {

        if (L.data[i] > L.data[i - 1]) {
            count++;
        }
        if (count >= maxcount && L.data[i] < L.data[i - 1]) {
            maxcount = count;
            count = 1;

        }
        if (i == n - 1 && count >= maxcount || count == n) {
            maxcount = count;
        }
        if (count < maxcount && L.data[i] < L.data[i - 1]) {
            count = 1;
        }

    }
    count = 1;
    for (int i = 1; i <= n; i++) {
        if (L.data[i] > L.data[i - 1]) {
            count++;
        }
        if (count < maxcount && L.data[i] < L.data[i - 1]) {
            count = 1;
        }
        if (count == maxcount) {
            Max_data_address = &L.data[i - maxcount + 1];
            count = 1;
            for (int a = 1; a <= maxcount; a++) {
                if (a == maxcount) {
                    printf("%d\n", *Max_data_address);
                } else {
                    printf("%d,", *Max_data_address);
                }
                Max_data_address++;
            }
        }
    }
    return 0;
}