//有关二叉树的一些操作
//这里的二叉树用链式存储结构
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

/* 二叉树节点结构体 */
typedef struct TreeNode {
    int val;                // 节点值
    int height;             // 节点高度
    struct TreeNode *left;  // 左子节点指针
    struct TreeNode *right; // 右子节点指针
} TreeNode;

/* 构造函数 */
TreeNode *newTreeNode(int val) {
    TreeNode *node;

    node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* 层序遍历 */
//实际上跟是运用了队列的思想，将二叉树的结点按照顺序依次存入队列中，然后把队列中每一个结点的值再存入数组中
int *levelOrder(TreeNode *root, int *size) {
    /* 声明辅助变量和数据结构 */
    int front, rear;        // 前后指针，用于队列操作
    int index, *arr;        // 索引和动态数组指针，用于存储遍历结果
    TreeNode *node;         // 当前处理的节点指针
    TreeNode **queue;       // 辅助队列，用于层序遍历

    /* 分配队列内存 */
    queue = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_SIZE);
    // 队列指针
    front = 0, rear = 0;
    // 将根节点加入队列
    queue[rear++] = root;

    /* 分配遍历结果数组内存 */
    arr = (int *)malloc(sizeof(int) * MAX_SIZE);
    // 数组指针
    index = 0;

    /* 开始层序遍历 */
    while (front < rear) {
        // 从队列中取出一个节点
        node = queue[front++];
        // 将该节点的值保存到遍历结果数组中
        arr[index++] = node->val;

        // 若左子节点存在，则将其加入队列
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        // 若右子节点存在，则将其加入队列
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
    }

    // 更新数组长度的值
    *size = index;
    // 动态调整数组大小，使其恰好容纳遍历结果
    arr = realloc(arr, sizeof(int) * (*size));

    // 释放辅助队列内存
    free(queue);
    // 返回层序遍历结果数组
    return arr;
}

/* 前序遍历 */
void preOrder(TreeNode *root, int *size) {
    if (root == NULL)
        return;
    // 访问优先级：根节点 -> 左子树 -> 右子树
    int *arr;
    arr[(*size)++] = root->val;
    preOrder(root->left, size);
    preOrder(root->right, size);
}

/* 中序遍历 */
void inOrder(TreeNode *root, int *size) {
    if (root == NULL)
        return;
    // 访问优先级：左子树 -> 根节点 -> 右子树
    int *arr;
    inOrder(root->left, size);
    arr[(*size)++] = root->val;
    inOrder(root->right, size);
}

/* 后序遍历 */
void postOrder(TreeNode *root, int *size) {
    if (root == NULL)
        return;
    // 访问优先级：左子树 -> 右子树 -> 根节点
    int *arr;
    postOrder(root->left, size);
    postOrder(root->right, size);
    arr[(*size)++] = root->val;
}