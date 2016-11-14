//
//  main.c
//  08-图7 公路村村通
//
//  Created by ztb on 16/10/21.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#define MaxSize 1000
#define INFINITY 65535

typedef struct
{
    int n, m;
    int Cost[MaxSize][MaxSize];
}MGraph;


void InitializeGraph(MGraph *G)
{
    int i,j;
    for(i = 0; i < G->n; i++)
    {
        for( j = 0; j < G->n; j++)
        {
            G->Cost[i][j] = INFINITY;
        }
    }
}

void LowestCost(MGraph *G)
{
    int LowCost[MaxSize], Parent[MaxSize];
    int i, V, W, count;
    int MinCost;
    int TotalCost;
    for(i = 0; i < G->n; i++)
    {
        Parent[i] = 0;
        LowCost[i] = G->Cost[0][i];
    }
    Parent[0] = -1;
    LowCost[0] = 0;
    count = 1;
    TotalCost = 0;
    while(1)
    {
        MinCost = INFINITY;
        for(i = 0;i < G->n; i++)
        {
            if(LowCost[i])
            {
                if(LowCost[i] < MinCost)
                {
                    MinCost = LowCost[i];
                    V = i;
                }
            }
        }
        if(MinCost == INFINITY)
            break;
        TotalCost += LowCost[V];
        LowCost[V] = 0;
        count++;
        for(W = 0; W < G->n;W++)
        {
            if(LowCost[W] && G->Cost[V][W] != INFINITY)
            {
                if(G->Cost[V][W] < LowCost[W])
                {
                    LowCost[W] = G->Cost[V][W];
                    Parent[W] = V;
                }
            }
        }
    }
    if(count == G->n)
        printf("%d\n", TotalCost);
    else
        printf("-1\n");
    return;
}

int main()
{
    MGraph G;
    
    int i, c1, c2;
    
    scanf("%d %d\n", &G.n, &G.m);
    InitializeGraph(&G);
    for(i = 0; i < G.m; i++)
    {
        scanf("%d %d ", &c1, &c2);
        c1--;
        c2--;
        scanf("%d\n",&G.Cost[c1][c2]);
        G.Cost[c2][c1] = G.Cost[c1][c2];
    }
    LowestCost(&G);
}
