//Prim算法
#include<stdio.h>
#include<limits.h>
//#include <limits.h> 是 C 语言中的标准库头文件之一，它定义了各种整数类型的限制和属性。
// 通过包含该头文件，可以使用其中定义的常量和宏来获取与整数类型相关的一些信息。


#define MAXVEX 100

//构建邻接矩阵无向图
typedef struct {
    int vexs[MAXVEX];//顶点表
    int arcs[MAXVEX][MAXVEX];//邻接矩阵
    int vexnum;//图当前的顶点数
    int arcnum;//图当前的边数

} AMGraph;

typedef int VerTexType;//假设顶点类型为int

//定义closedge结构体数组，以记录从U到V-U具有最小权值的边
typedef struct {
    VerTexType adjvex;//最小边在U中的那个顶点
    int lowcost;//最小边上的权值
} Closedge[MAXVEX];

//定位顶点函数：返回顶点U在图中的索引，如果所有顶点都是连续存储的话则不需要此函数，U即为其在图中的索引
int LocateVex(AMGraph G, VerTexType u) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vexs[i] == u) {
            return i;
        }
    }
    return -1;
}

//从closedge中选择权重最小且未加入MST的顶点索引
int Min(Closedge closedge, int G_vexnum) {
    int min = INT_MAX;
    int min_index;
    for (int i = 0; i < G_vexnum; i++) {
        //条件确保了该顶点还未包含在MST中且当前顶点的边权重比当前记录的最小值要小
        if (closedge[i].lowcost != 0 && closedge[i].lowcost < min) {
            min = closedge[i].lowcost;
            min_index = i;
        }
    }
    return min_index;
}

//Prim算法构造最小生成树
void MinSpanTree_Prim(AMGraph G, VerTexType u) {
    //无向图以邻接矩阵形式存储，从顶点u出发构造G的最小生成树T，输出T的各条边
    int k = LocateVex(G, u);//k为顶点u在无向图的数组下标
    //初始化closedge数组，先把图中所有的点与顶点所对应的边的权重都初始化在closedge数组中
    Closedge closedge;
    for (int j = 0; j < G.vexnum; j++) {
        if (j != k) {
            closedge[j].adjvex = u;//设定与顶点j相连的顶点为u（起始顶点），即adjvex为起始顶点u
            closedge[j].lowcost = G.arcs[k][j];//lowcost为图中边u到j的权重，如果没有边相连的话应该为INT_MAX
        }
    }
    closedge[k].lowcost = 0;//表示起始顶点已经包含在最小生成树中
    for (int i = 1; i < G.vexnum; i++) {
        //从closedge中选择权重最小的顶点K
        k = Min(closedge, G.vexnum);

        //输出当前的最小边
        int u0 = closedge[k].adjvex;
        int v0 = G.vexs[k];
        printf("%d - %d\n", u0, v0);

        //将选择的顶点k加入MST,权重设为0
        closedge[k].lowcost = 0;//lowcost为0表示了该点已经存入了MST中

        //更新closedge数组，加入新顶点后重新选择最小边
        for (int j = 0; j < G.vexnum; j++) {
            if (G.arcs[k][j] < closedge[j].lowcost) {
                closedge[j].adjvex = G.vexs[k];
                closedge[j].lowcost = G.arcs[k][j];
            }
        }
    }
}
