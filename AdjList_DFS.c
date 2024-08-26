//算法设计题，判断以邻接表方式存储的有向图中是否存在由顶点vi到顶点vj（i！=j）的路径。
#include <stdio.h>
#include <stdlib.h>

//定义邻接表的结点结构
struct AdjListNode {
    int dest;//目标顶点的编号
    struct AdjListNode *next;//指向下一个邻接结点的指针
};

//定义邻接表的头结点结构
struct AdjList {
    struct AdjListNode *head;//指向邻接结点链表第一个结点的指针
};

//定义图的结构
struct Graph {
    int v;//顶点的总数
    struct AdjList *array;//指向邻接表数组的指针
};

//创建新的邻接结点
struct AdjListNode *newAdjListNode(int dest) {
    struct AdjListNode *newNode = (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

//创建图
struct Graph *createGraph(int v) {
    struct Graph *newGraph = (struct Graph *) malloc(sizeof(struct Graph));
    newGraph->v = v;
    newGraph->array = (struct AdjList *) malloc(sizeof(struct AdjList));
    for (int i = 0; i < v; i++) {
//头结点中只包含指针，而顶点的编码就是数组下标加一，头结点与邻接结点不同点在于头结点只有指向下一个结点的指针，但是邻接结点还有下一个目标顶点的编号
        newGraph->array[i].head = NULL;
    }
    return newGraph;
}

//添加边
void addEdge(struct Graph *graph, int src, int dest) {
    struct AdjListNode *newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

//深度优先DFS
int AdjListDFS(struct Graph *graph, int vi, int vj, int visited[]) {
    if (vi == vj) {
        return 1;
    }
    visited[vi] = 1;
    struct AdjListNode *current = graph->array[vi].head;
    while (current != NULL) {
        int neighbor = current->dest;
        if (visited[neighbor] == 0) {
            if (AdjListDFS(graph, neighbor, vj, visited)) {
                return 1;
            }
        }
        current = current->next;
    }
    return 0;
}

// 检查是否存在从顶点 vi 到顶点 vj 的路径
int isPath(struct Graph *graph, int vi, int vj) {
    if (vi < 0 || vj < 0 || vi >= graph->v || vj >= graph->v) {
        printf("Invalid vertex indices.\n");
        return 0;
    }
    //初始化访问数组，标记所有顶点都为未访问状态
    int visited[graph->v];
    for (int i = 0; i < graph->v; i++) {
        visited[i] = 0;
    }
    //调用DFS
    int a = AdjListDFS(graph, vi, vj, visited);
    return a;
}

int main() {
    // 创建一个有向图
    int v = 4; // 顶点总数
    struct Graph *graph = createGraph(v);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 0);

    // 检查路径是否存在
    int vi = 0; // 起始顶点
    int vj = 2; // 目标顶点
    if (isPath(graph, vi, vj)) {
        printf("Path exists from vertex %d to vertex %d.\n", vi, vj);
    } else {
        printf("No path exists from vertex %d to vertex %d.\n", vi, vj);
    }
    return 0;
}