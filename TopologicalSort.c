//拓扑排序，以栈实现，为DFS算法（深度优先），如果以队列实现的话就是广度优先，甚至处理入度为0的顶点不需要什么顺序，只不过输出的结果有随机性
#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX_NUM 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;

typedef struct ArcNode{
    int adjvex;//指向弧头顶点的位置
    struct ArcNode*nextarc;//指向下一条弧的指针
}ArcNode;

typedef struct VNode{
    int data;//顶点信息
    ArcNode *firstarc;//指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList veryices;//邻接表
    int vexnum,arcnum;//图的顶点数和弧数
}ALGraph;

typedef struct{
    int data[MAX_VERTEX_NUM];
    int top;
}Stack;

//初始化栈
void InitStack(Stack*S){
    S->top=-1;
}

//入栈操作
Status Push(Stack*S,int e){
    if(S->top==MAX_VERTEX_NUM-1){
        return ERROR;//栈溢出
    }
    S->data[++(S->top)]=e;
    return OK;
}

//出栈操作
Status Pop(Stack*S,int *e){
    if(S->top==-1){
        return ERROR;//栈下溢
    }
    *e=S->data[(S->top)--];
    return OK;
}

//判断栈是否为空
Status StackEmpty(Stack S){
    if(S.top==-1){
        return TRUE;
    }
    return FALSE;
}

//计算所有顶点的入度
void FindDegree(ALGraph G,int indegree[]){
    for(int i=0;i<G.vexnum;i++){
        indegree[i]=0;//初始化所有顶点的入度为0
    }
    for(int i=0;i<G.vexnum;i++){
        //对于每一个顶点i，遍历其所有的邻接结点（即从顶点i出发的所有边）
        for(ArcNode*p=G.veryices[i].firstarc;p;p=p->nextarc){
            indegree[p->adjvex]++;//增加相邻顶点的入度
        }
    }
}

//拓扑排序
Status TopologicalSort(ALGraph G){
    Stack S;
    int indegree[MAX_VERTEX_NUM];
    int topo[MAX_VERTEX_NUM];//拓扑序列
    int count=0;
    int m=0;//拓扑序列的指引
    FindDegree(G,indegree);//计算所有顶点的入度
    InitStack(&S);//初始化栈

    for(int i=0;i<G.vexnum;i++){
        if(indegree[i]==0){//如果顶点的入度为0
            Push(&S,i);//将顶点入栈
        }
    }

    while(!StackEmpty(S)){
        int i;
        Pop(&S,&i);//从栈中弹出一个顶点
        topo[m++]=i;//加入topo序列中

        for(ArcNode*p=G.veryices[i].firstarc;p;p=p->nextarc){
            int k=p->adjvex;
            indegree[k]--;//将与pop出来的顶点的一条弧上的下一个顶点的入度减一
            if(indegree[k]==0){
                Push(&S,k);//如果入度变为0，将其入栈
            }

        }
count++;
    }
    if(count<G.vexnum){
        return ERROR;//处理的顶点数小于总顶点数，则说明有环
    }else{
        return OK;//拓扑排序成功
    }
}