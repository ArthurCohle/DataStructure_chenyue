//
//  main.c
//  06-图3 六度空间
//
//  Created by ztb on 16/10/15.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 10000
#define MaxSize 10000
enum GraphType {DG, UG, DN, UN};
int Visited[MaxVertexNum];


typedef struct Node
{
    int AdjV;
    struct Node* Next;
}EdgeNode;


typedef int VertexType;
typedef struct Vnode
{
    VertexType Vertex;
    EdgeNode* FirstEdge;
}VertexNode;


typedef VertexNode AdjList[MaxVertexNum];
typedef struct
{
    AdjList Adjlist;
    int n, e;
    enum GraphType GType;
}ALGraph;

void CreateALGraph(ALGraph* G)
{
    int i, j, k, flag;
    EdgeNode *edge, *temp;
    
    G->GType = UG;
    scanf("%d %d\n", &(G->n), &(G->e));
    for(i = 0;i < G->n; i++)
    {
        G->Adjlist[i].Vertex = i;
        G->Adjlist[i].FirstEdge = NULL;
    }
    for(k = 0; k < G->e; k++)
    {
        scanf("%d %d\n", &i, &j);
        i--;
        j--;
        edge = (EdgeNode*)malloc(sizeof(EdgeNode));
        edge->AdjV = j;
        edge->Next = G->Adjlist[i].FirstEdge;
        temp = G->Adjlist[i].FirstEdge;
        flag = 0;
        while(edge->Next && edge->Next->AdjV < edge->AdjV)
        {
            edge->Next = edge->Next->Next;
            if(!flag)
                flag = 1;
            else
                temp = temp->Next;
        }
        if(edge->Next == G->Adjlist[i].FirstEdge)
        {
            G->Adjlist[i].FirstEdge = edge;
        }
        else
        {
            temp->Next = edge;
        }
        edge = (EdgeNode*)malloc(sizeof(EdgeNode));
        edge->AdjV = i;
        edge->Next = G->Adjlist[j].FirstEdge;
        temp = G->Adjlist[j].FirstEdge;
        flag = 0;
        while(edge->Next && edge->Next->AdjV < edge->AdjV)
        {
            edge->Next = edge->Next->Next;
            if(!flag)
                flag = 1;
            else
                temp = temp->Next;
        }
        if(edge->Next == G->Adjlist[j].FirstEdge)
        {
            G->Adjlist[j].FirstEdge = edge;
        }
        else
        {
            temp->Next = edge;
        }
    }
}


typedef struct
{
    VertexType Data[MaxSize];
    int front;
    int rear;
}Queue;


void AddQ(Queue* Q,VertexType X)
{
    Q->rear = (Q->rear + 1) % MaxSize;
    Q->Data[Q->rear] = X;
}


VertexType DeleteQ(Queue* Q)
{
    Q->front = (Q->front + 1) % MaxSize;
    return Q->Data[Q->front];
}


int IsFull(Queue Q)
{
    if((Q.rear+1) % MaxSize == 0)
    {
        return 1;
    }
    else
        return 0;
}


int IsEmpty(Queue Q)
{
    if(Q.front == Q.rear)
        return 1;
    else
        return 0;
}


void BFS(ALGraph G)
{
    Queue Q;
    VertexType U, V;
    EdgeNode *W;
    int count, i, level, last, tail;
    float percent;
    for(U = 0; U < G.n; U++)
    {
        Q.front = 0;
        Q.rear = 0;
        for(i = 0; i < G.n; i++)
        {
            Visited[i] = 0;
        }
        level = 0;
        AddQ(&Q, U);
        Visited[U] = 1;
        count = 1;
        last = U;
        while(!IsEmpty(Q))
        {
            V = DeleteQ(&Q);
            for (W = G.Adjlist[V].FirstEdge; W ; W = W->Next)
            {
                if(!Visited[W->AdjV])
                {
                    AddQ(&Q, W->AdjV);
                    Visited[W->AdjV] = 1;
                    count++;
                    tail = W->AdjV;
                }
            }
            if(V == last)
            {
                level++;
                last = tail;
            }
            if(level == 6)
            {
                break;
            }
        }
        percent = (float)count/G.n*100;
        printf("%d: %.2f%%\n",U + 1,percent);

    }
}


int main()
{
    ALGraph G;
    CreateALGraph(&G);
    BFS(G);
}

