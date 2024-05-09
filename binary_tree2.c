//有关二叉树的一些操作
//这里的二叉树用数组存储结构
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

/* 数组表示下的二叉树结构体 */
typedef struct {
    int *tree;  // 指向存储二叉树元素的数组
    int size;   // 数组大小，表示二叉树的节点数
} ArrayBinaryTree;

/* 构造函数 */
ArrayBinaryTree *newArrayBinaryTree(int *arr, int arrSize) {
    // 分配内存并初始化结构体
    ArrayBinaryTree *abt = (ArrayBinaryTree *)malloc(sizeof(ArrayBinaryTree));
    abt->tree = malloc(sizeof(int) * arrSize);  // 分配内存并复制数组元素
    memcpy(abt->tree, arr, sizeof(int) * arrSize);
    abt->size = arrSize;  // 设置数组大小
    return abt;
}

/* 析构函数 */
void delArrayBinaryTree(ArrayBinaryTree *abt) {
    // 释放内存
    free(abt->tree);
    free(abt);
}

/* 列表容量 */
int size(ArrayBinaryTree *abt) {
    // 返回数组大小
    return abt->size;
}

/* 获取索引为 i 节点的值 */
int val(ArrayBinaryTree *abt, int i) {
    // 若索引越界，则返回 INT_MAX ，代表空位
    if (i < 0 || i >= size(abt))
        return INT_MAX;
    return abt->tree[i];
}

/* 层序遍历 */
int *levelOrder(ArrayBinaryTree *abt, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    // 直接遍历数组，将非空节点值存入结果数组
    for (int i = 0; i < size(abt); i++) {
        if (val(abt, i) != INT_MAX)
            res[index++] = val(abt, i);
    }
    *returnSize = index;
    return res;
}

/* 左子节点索引 */
int left(int i) {
    return 2 * i + 1;
}

/* 右子节点索引 */
int right(int i) {
    return 2 * i + 2;
}
//在数组表示下的二叉树中，节点的存储顺序是按照层序遍历的顺序依次存储在数组中的。即从上到下，从左到右依次存储每个节点。
//因此，对于任意一个节点的索引 i，其左子节点的索引是 2 * i + 1，右子节点的索引是 2 * i + 2。
//这种存储方式在完全二叉树中特别明显，因为完全二叉树中没有空缺的节点，所有的层级都被填满，因此按照层序遍历的顺序存储在数组中会形成连续的结构。
//但即使是非完全二叉树，节点的存储方式仍然按照层序遍历的顺序进行，只是会有一些空缺的位置。左子节点和右子节点的计算方法仍然适用于这种情况。
//因此，无论二叉树是否为完全二叉树，都可以使用 2 * i + 1 和 2 * i + 2 的计算方法来获取节点的左子节点和右子节点索引。

/* 深度优先遍历 */
//注意，两个递归遍历并不在if语句里面，if语句里面只有一行代码，表示将当前结点的值存入数组中
void dfs(ArrayBinaryTree *abt, int i, char *order, int *res, int *index) {
    // 若为空位，则返回
    if (val(abt, i) == INT_MAX)
        return;
    //order用来确定遍历方式
    // 前序遍历
    if (strcmp(order, "pre") == 0)
        res[(*index)++] = val(abt, i);
    // 递归遍历左子树
    dfs(abt, left(i), order, res, index);
    // 中序遍历
    if (strcmp(order, "in") == 0)
        res[(*index)++] = val(abt, i);
    // 递归遍历右子树
    dfs(abt, right(i), order, res, index);
    // 后序遍历
    if (strcmp(order, "post") == 0)
        res[(*index)++] = val(abt, i);
}

/* 前序遍历 */
int *preOrder(ArrayBinaryTree *abt, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    // 调用深度优先遍历函数，指定前序遍历方式
    dfs(abt, 0, "pre", res, &index);
    *returnSize = index;
    return res;
}

/* 中序遍历 */
int *inOrder(ArrayBinaryTree *abt, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    // 调用深度优先遍历函数，指定中序遍历方式
    dfs(abt, 0, "in", res, &index);
    *returnSize = index;
    return res;
}

/* 后序遍历 */
int *postOrder(ArrayBinaryTree *abt, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * size(abt));
    int index = 0;
    // 调用深度优先遍历函数，指定后序遍历方式
    dfs(abt, 0, "post", res, &index);
    *returnSize = index;
    return res;
}
