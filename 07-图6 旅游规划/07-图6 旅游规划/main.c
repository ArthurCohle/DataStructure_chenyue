//
//  main.c
//  07-图6 旅游规划
//
//  Created by ztb on 16/10/20.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 500
#define INFINITY 65535

int s, d;
typedef struct LengthAndCharge
{
    int Length;
    int Charge;
}LC;

typedef struct
{
    int n;
    int m;
    LC Data[MaxSize][MaxSize];
}MGraph;


void Dijkstra(MGraph G)
{
    int Collected[MaxSize], Path[MaxSize], Length[MaxSize], Charge[MaxSize];
    int i, W, V;
    
    for(i = 0; i < G.n; i++)
    {
        Collected[i] = 0;
    }
    Collected[s] = 1;
    for(W = 0; W < G.n; W ++)
    {
        Length[W] = G.Data[s][W].Length;
        Charge[W] = G.Data[s][W].Charge;
    }
    while(1)
    {
        V = s;
        for(i = 0; i < G.n; i++)
        {
            if(!Collected[i] && Length[i] < Length[V])
                V = i;
        }
        if(V == s)
            break;
        Collected[V] = 1;
        for(W = 0; W < G.n; W++)
        {
            if(G.Data[V][W].Length != INFINITY && !Collected[W])
            {
                if(Length[V] + G.Data[V][W].Length < Length[W])
                {
                    Length[W] = Length[V] + G.Data[V][W].Length;
                    Path[W] = V;
                    Charge[W] = Charge[V] + G.Data[V][W].Charge;
                }
                else if((Length[V] + G.Data[V][W].Length == Length[W]) && (Charge[V] + G.Data[V][W].Charge < Charge[W]))
                {
                    Charge[W] = Charge[V] + G.Data[V][W].Charge;
                    Path[W] = V;
                }
            }
        }
    }
    printf("%d %d\n", Length[d], Charge[d]);
}


int main()
{
    MGraph G;
    int i, j, city1, city2;
    scanf("%d %d %d %d\n", &G.n, &G.m, &s, &d);
    for(i = 0; i < G.n; i++)
    {
        for(j = 0; j < G.n; j++)
        {
            G.Data[i][j].Length = INFINITY;
            G.Data[i][j].Charge = INFINITY;
        }
    }
    for(i = 0; i < G.m; i++)
    {
        scanf("%d %d ",&city1,&city2);
        scanf("%d %d\n",&G.Data[city1][city2].Length, &G.Data[city1][city2].Charge);
        G.Data[city2][city1].Length = G.Data[city1][city2].Length;
        G.Data[city2][city1].Charge = G.Data[city1][city2].Charge;
    }
    Dijkstra(G);
    return 0;
}
