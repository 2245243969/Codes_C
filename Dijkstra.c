//Dijkstra算法的实现

#include<stdio.h>
#include <stdbool.h>

#define MAXINT 10000//表示无穷大
#define MAXVEX 100//表示最大顶点数

typedef struct{
    int vexnum;//顶点数量
    int arc[MAXVEX][MAXVEX];//邻接矩阵
}MGraph;

//Dijkstra算法
//传入的Path数组存储了最短路径上的前驱结点
//传入的D数组存储源点到各顶点的最短路径长度
void ShortestPath_Dijkstra(MGraph G,int v0,int *D,int *Path){
    bool S[MAXVEX];//判断顶点v是否已被包含在最短路径集合S中
    int min,w,v;

    //初始化
    for(v=0;v<G.vexnum;v++){
        S[v]=false;//初始时，集合S为空
        D[v]=G.arc[v0][v];//将v0到各个顶点的初始路径权值赋值给D
        if(D[v]<MAXINT){
            Path[v]=v0;//如果v0到v有路径，前驱设置为v0
        }else{
            Path[v]=-1;//如果v0到v没有路径，前驱设置为-1
        }
    }
    D[v0]=0;//源点到自身的距离为0
    S[v0]=true;//将v0加入S集合

    //开始主循环，每次求得v0到某个顶点的最短路径,将v加到S集
    for(int i=1;i<G.vexnum;i++)//对其余n-1各顶点，依次进行计算
    {
        min=MAXINT;
        //找到当前未处理顶点中距离v0最近的顶点v
        for(w=0;w<G.vexnum;w++){
          if(!S[w]&&D[w]<min){
              v=w;
              min=D[w];
          }
        }

        S[v]=true;//将顶点v加入S集合

        //更新从源点到其他所有顶点的距离
        for(w=0;w<G.vexnum;w++){
            //如果顶点w不在S中，并且v到w有边，并且通过v到w的路径比当前D[w]值小，则更新D[w]的值
            if(!S[w]&&G.arc[v][w]<MAXINT&&D[v]+G.arc[v][w]<D[w]){
                D[w]=D[v]+G.arc[v][w];
                Path[w]=v;//更新前驱结点
            }
        }
    }
}
int main() {
    MGraph G;
    int v0 = 0;  // 源点
    int D[MAXVEX];  // 存储源点到各顶点的最短路径长度
    int Path[MAXVEX];  // 存储最短路径上的前驱顶点

    // 初始化图（这里举例一个包含9个顶点的图）
    G.vexnum = 9;
    int graph[9][9] = {
            {0, 4, MAXINT, MAXINT, MAXINT, MAXINT, MAXINT, 8, MAXINT},
            {4, 0, 8, MAXINT, MAXINT, MAXINT, MAXINT, 11, MAXINT},
            {MAXINT, 8, 0, 7, MAXINT, 4, MAXINT, MAXINT, 2},
            {MAXINT, MAXINT, 7, 0, 9, 14, MAXINT, MAXINT, MAXINT},
            {MAXINT, MAXINT, MAXINT, 9, 0, 10, MAXINT, MAXINT, MAXINT},
            {MAXINT, MAXINT, 4, 14, 10, 0, 2, MAXINT, MAXINT},
            {MAXINT, MAXINT, MAXINT, MAXINT, MAXINT, 2, 0, 1, 6},
            {8, 11, MAXINT, MAXINT, MAXINT, MAXINT, 1, 0, 7},
            {MAXINT, MAXINT, 2, MAXINT, MAXINT, MAXINT, 6, 7, 0}
    };

    // 将图的邻接矩阵复制到结构体中
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            G.arc[i][j] = graph[i][j];
        }
    }

    // 调用Dijkstra算法
    ShortestPath_Dijkstra(G, v0, D, Path);

    // 输出最短路径结果
    printf("Vertex \t Distance from Source\t Path\n");
    for (int i = 0; i < G.vexnum; ++i) {
        printf("%d \t %d \t\t\t %d\n", i, D[i], Path[i]);
    }

    return 0;
}


