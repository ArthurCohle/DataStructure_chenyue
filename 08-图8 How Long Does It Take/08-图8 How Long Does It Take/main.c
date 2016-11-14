//
//  main.c
//  08-图8 How Long Does It Take
//
//  Created by ztb on 16/10/21.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
/* 图的邻接表表示法 */
#define ERROR -1
#define MaxVertexNum 100    /* 最大顶点数设为100 */
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;        /* 邻接点下标 */
    WeightType Weight;  /* 边权重 */
    PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;/* 边表头指针 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;     /* 顶点数 */
    int Ne;     /* 边数   */
    AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

typedef int Position;
typedef int ElementType;
struct QNode {
    ElementType *Data;     /* 存储元素的数组 */
    Position Front, Rear;  /* 队列的头、尾指针 */
    int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;

LGraph CreateGraph( int VertexNum );
void InsertEdge( LGraph Graph, Edge E );
LGraph BuildGraph();
bool TopSort( LGraph Graph, Vertex TopOrder[] );
Queue CreateQueue( int MaxSize );
bool IsFull( Queue Q );
bool AddQ( Queue Q, ElementType X );
bool IsEmpty( Queue Q );
ElementType DeleteQ( Queue Q );


//全局变量
int Earliest[MaxVertexNum] = {0};//用来计算每个事项的完成时间


int main()
{
    //freopen("in1.txt","r",stdin);
    //freopen("in2.txt","r",stdin);
    LGraph Graph;
    bool flag;
    Vertex TopOrder[MaxVertexNum] = {0};
    
    Graph = BuildGraph();//建表
    flag = TopSort( Graph, TopOrder);//拓扑排序
    if(flag == false)
    {
        printf("Impossible");
    }
    else if(flag == true)
    {
        int max = Earliest[0];
        for(int i=0; i<Graph->Nv; i++)//一条路径花费时间最大的就是结果
        {
            if(max<Earliest[i])
            {
                max = Earliest[i];
            }
        }
        printf("%d",max);// 输出
        
    }
    return 0;
}



LGraph CreateGraph( int VertexNum )
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V;
    LGraph Graph;
    
    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接表头指针 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;
    
    return Graph;
}

void InsertEdge( LGraph Graph, Edge E )
{
    PtrToAdjVNode NewNode;
    
    /* 插入边 <V1, V2> */
    /* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* 将V2插入V1的表头 */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
    
    
}

LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    int Nv, i;
    
    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */
    
    scanf("%d", &(Graph->Ne));   /* 读入边数 */
    if ( Graph->Ne != 0 ) { /* 如果有边 */
        E = (Edge)malloc( sizeof(struct ENode) ); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge( Graph, E );
        }
    }
    
    free(E);
    return Graph;
}

/* 邻接表存储 - 拓扑排序算法 */

bool TopSort( LGraph Graph, Vertex TopOrder[] )
{ /* 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 */
    int Indegree[MaxVertexNum], cnt;
    Vertex V;
    PtrToAdjVNode W;
    Queue Q = CreateQueue( Graph->Nv );
    
    /* 初始化Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        Indegree[V] = 0;
    
    /* 遍历图，得到Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        for (W=Graph->G[V].FirstEdge; W; W=W->Next)
            Indegree[W->AdjV]++; /* 对有向边<V, W->AdjV>累计终点的入度 */
    
    /* 将所有入度为0的顶点入列 */
    for (V=0; V<Graph->Nv; V++)
        if ( Indegree[V]==0 )
        {
            AddQ(Q, V);
            Earliest[V] = 0;//所有入度为0的顶点所花费时间均为0
        }
    /* 下面进入拓扑排序 */
    cnt = 0;
    while( !IsEmpty(Q) ){
        V = DeleteQ(Q); /* 弹出一个入度为0的顶点 */
        TopOrder[cnt++] = V; /* 将之存为结果序列的下一个元素 */
        
        /* 对V的每个邻接点W->AdjV */
        for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
        {
            if ( --Indegree[W->AdjV] == 0 )/* 若删除V使得W->AdjV入度为0 */
            {
                AddQ(Q, W->AdjV); /* 则该顶点入列 */
                if(Earliest[V] + W->Weight  > Earliest[W->AdjV])
                {
                      Earliest[W->AdjV] = Earliest[V] + W->Weight;
                }
                //                if( ( ( Earliest[V] + W->Weight ) > Earliest[W->AdjV] ) && Earliest[W->AdjV] )
                //                {   //有多条路径到达，选择花费时间最长的
                //
                //                    Earliest[W->AdjV] = Earliest[V] + W->Weight;
                //                }
            }
            else if( Earliest[V] + W->Weight  > Earliest[W->AdjV] )
            {
                  Earliest[W->AdjV] = Earliest[V] + W->Weight;
            }
        }
    } /* while结束*/
    
    if ( cnt != Graph->Nv )
        return false; /* 说明图中有回路, 返回不成功标志 */
    else
        return true;
}
//队列相关


Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

bool IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}

bool AddQ( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) {
        printf("队列满");
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

bool IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}

ElementType DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) {
        printf("队列空");
        return ERROR;
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}
