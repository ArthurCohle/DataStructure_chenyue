//
//  main.c
//  06-图2 Saving James Bond - Easy Version
//
//  Created by ztb on 16/10/15.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MaxSize 100


typedef struct
{
    int x;
    int y;
}Coordinate;


Coordinate C[MaxSize];
int Visited[MaxSize];
int answer;
void SetVisited(int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        Visited[i] = 0;
    }
}


int FirstJump(int i,int d)
{
    if(pow(C[i].x, 2) + pow(C[i].y, 2) <= pow((d +15), 2))
        return 1;
    else
        return 0;
}


int Jump(int i, int k,int d)
{
    if(pow(C[i].x-C[k].x, 2) + pow(C[i].y - C[k].y, 2) <= pow(d, 2))
        return 1;
    else
        return 0;
}


int IsSave(int i,int d)
{
    if(abs(abs(C[i].x) - 50) <= d || abs(abs(C[i].y) - 50) <= d)
        return 1;
    else
        return 0;
}


void DFS(int i,int n,int d)
{
    int k;
    Visited[i] = 1;
    if(IsSave(i, d))
        answer = 1;
    else
    {
        for(k = 0; k < n; k++)
        {
            if(!Visited[k] && Jump(i, k, d))
            {
                DFS(k,n,d);
                if(answer == 1)
                    break;
            }
        }
    }
    return ;
}


int main()
{
    int n, i, d;
    answer = 0;
    scanf("%d %d\n", &n, &d);
    for(i = 0;i < n; i++)
    {
        scanf("%d %d\n", &C[i].x, &C[i].y);
    }
    SetVisited(n);
    for(i = 0;i < n ; i++)
    {
        if(!Visited[i] && FirstJump(i,d))
        {
            DFS(i,n,d);
            if (answer == 1)
                break;
        }
    }
    if(answer == 1)
        printf("Yes\n");
    else
        printf("No\n");
}
