#include <stdio.h>
//交换元素函数
void swap(int arr[],int i,int j){
    int temp= arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

//快速排序的分区函数
int partition(int arr[],int left,int right){
    int pivot=arr[right];//选择最后一个元素作为基准
    int slow=left,fast=left;//定义快慢指针
    while(fast<right){
        //如果快指针所指的元素比基准小，则交换快慢指针的值
        if(arr[fast]<pivot){
            swap(arr,slow,fast);
            slow++;
        }
        fast++;
    }
    //最后交换slow所指元素和基准的值，完成一次分区
    swap(arr,slow,right);
    //返回下标slow
    return slow;
}

//快速排序函数
void quick_sort(int arr[],int left,int right){
    if(left<right){
        //分区，返回基准的最终位置
        int pi= partition(arr,left,right);
        // 递归地对基准左边和右边的子数组进行排序
        quick_sort(arr,left,pi-1);
        quick_sort(arr,pi+1,right);
    }
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, n - 1);
    printf("Sorted array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}