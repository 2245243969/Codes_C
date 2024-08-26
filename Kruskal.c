//克鲁斯卡尔算法，构建最小生成树、

#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 100
#define INFINITY INT_MAX

//构建邻接矩阵无向图
typedef struct {
    int vexnum;//总顶点数
    int arcnum;//总边数
    int matrix[MAXVEX][MAXVEX]; // 邻接矩阵
} MGraph;

//辅助数组Edges的定义
typedef struct {
    int head;//边的始点
    int tail;//边的终点
    int weight;//边的权值
} Edge;

//将edges数组中的元素按权值从小到大排序
void bubbleSort(Edge edges[], int edgeCount) {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge t = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = t;
            }
        }
    }
}

// Kruskal算法生成最小生成树
void MiniSpanTree_Kruskal(MGraph *G) {
    Edge edges[MAXVEX * (MAXVEX - 1) / 2];//无向图最多有n(n-1)/2条边，称为无向完全图
    //将邻接矩阵中的边存入edges数组中
    int edgeCount = 0;
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            if (G->matrix[i][j] != INFINITY) {
                edges[edgeCount].head = i;
                edges[edgeCount].tail = j;
                edges[edgeCount].weight = G->matrix[i][j];
                edgeCount++;
            }
        }
    }
    //将edges数组按权值从小到大排序
    bubbleSort(edges, edgeCount);

    //Vexset为辅助数组，表示各顶点自成一个连接分量
    int Vexset[G->vexnum];
    for (int i = 0; i < G->vexnum; i++) {
        Vexset[i] = i;
    }

    // Kruskal算法构造最小生成树
    for (int i = 0; i < edgeCount; i++) {
        //LocateVex 函数的作用是找到顶点在顶点数组中的位置。
        // 但如果假设顶点的编号是连续的整数（例如从0开始编号），那么我们可以省略这个函数，因为我们可以直接使用顶点编号作为索引。这会使代码更简单。
        int v1 = edges[i].head;
        int v2 = edges[1].tail;
        int vs1 = Vexset[v1];
        int vs2 = Vexset[v2];
        if (vs1 != vs2) {
            printf("Edge (%d, %d) weight: %d\n", edges[i].head, edges[i].tail, edges[i].weight); // 输出此边
            for (int j = 0; j < G->vexnum; j++) {
                if (Vexset[j] == vs2) {
                    Vexset[j] = vs1;
                }
            }
        }
    }

}


