//有关二叉搜索树的一些操作
//二叉搜索树的概念
//1.对于根节点，左子树中所有节点的值<根节点的值<右子树中所有节点的值。
//2.任意节点的左、右子树也是二叉搜索树，即同样满足条件 1. 。

/* 查找节点 */
TreeNode *search(BinarySearchTree *bst, int num) {
    TreeNode *cur = bst->root;
    // 循环查找，越过叶节点后跳出
    while (cur != NULL) {
        if (cur->val < num) {
            // 目标节点在 cur 的右子树中
            cur = cur->right;
        } else if (cur->val > num) {
            // 目标节点在 cur 的左子树中
            cur = cur->left;
        } else {
            // 找到目标节点，跳出循环
            break;
        }
    }
    // 返回目标节点
    return cur;
}

/* 插入节点 */
void insert(BinarySearchTree *bst, int num) {
    // 若树为空，则初始化根节点
    if (bst->root == NULL) {
        bst->root = newTreeNode(num);
        return;
    }
    TreeNode *cur = bst->root, *pre = NULL;
    // 循环查找，越过叶节点后跳出
    while (cur != NULL) {
        // 找到重复节点，直接返回
        if (cur->val == num) {
            return;
        }
        pre = cur;//可以知道pre存储的是当前cur的父亲结点的位置，当之后的cur==NULL时，我们可以通过pre回溯到cur的父节点
        if (cur->val < num) {
            // 插入位置在 cur 的右子树中
            cur = cur->right;
        } else {
            // 插入位置在 cur 的左子树中
            cur = cur->left;
        }
    }
    // 插入节点
    TreeNode *node = newTreeNode(num);
    if (pre->val < num) {
        pre->right = node;
    } else {
        pre->left = node;
    }
}

/* 删除节点 */
// 由于引入了 stdio.h ，此处无法使用 remove 关键词
void removeItem(BinarySearchTree *bst, int num) {
    // 若树为空，直接提前返回
    if (bst->root == NULL)
        return;
    TreeNode *cur = bst->root, *pre = NULL;
    // 循环查找，越过叶节点后跳出
    while (cur != NULL) {
        // 找到待删除节点，跳出循环
        if (cur->val == num)
            break;
        pre = cur;
        if (cur->val < num) {
            // 待删除节点在 root 的右子树中
            cur = cur->right;
        } else {
            // 待删除节点在 root 的左子树中
            cur = cur->left;
        }
    }
    // 若无待删除节点，则直接返回
    if (cur == NULL)
        return;
    // 判断待删除节点是否存在子节点
    if (cur->left == NULL || cur->right == NULL) {
        /* 子节点数量 = 0 or 1 */
        // 当子节点数量 = 0 / 1 时， 将要删除结点的左孩子或者右孩子存入child中，以便后续删除结点和将child连入pre中
        TreeNode *child = cur->left != NULL ? cur->left : cur->right;
        // 删除节点 cur
        //还要判断cur是pre的左子结点还是右子结点
        if (pre->left == cur) {
            pre->left = child;
        } else {
            pre->right = child;
        }
        // 释放内存
        free(cur);
    } else {
        /* 子节点数量 = 2 */
        // 获取中序遍历中 cur 的下一个节点
        TreeNode *tmp = cur->right;
        while (tmp->left != NULL) {
            tmp = tmp->left;
        }
        int tmpVal = tmp->val;
        // 递归删除节点 tmp
        removeItem(bst, tmp->val);
        // 用 tmp 覆盖 cur
        cur->val = tmpVal;
    }
}