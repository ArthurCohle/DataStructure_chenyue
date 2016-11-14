//
//  main.c
//  07-图5 Saving James Bond - Hard Version
//
//  Created by ztb on 16/10/19.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MaxSize 101


typedef struct
{
    int x;
    int y;
}Coordinate;

typedef struct queue
{
    int rear;
    int front;
    int Data[MaxSize];
}*Queue;


Queue CreateQ()
{
    Queue q;
    q = (Queue)malloc(sizeof(struct queue));
    q->rear = 0;
    q->front = 0;
    return q;
}


void AddQ(Queue q, int x)
{
    q->rear = (q->rear + 1)%MaxSize;
    q->Data[q->rear] = x;
}


int DeleteQ(Queue q)
{
    q->front = (q->front + 1)%MaxSize;
    return q->Data[q->front];
}


int IsFullQ(Queue q)
{
    if((q->rear + 1) % MaxSize == q->front)
        return 1;
    return 0;
}


int IsEmptyQ(Queue q)
{
    if(q->front == q->rear)
        return 1;
    return 0;
}


typedef struct stack
{
    int Data[MaxSize];
    int top;
}*Stack;

Stack CreateS()
{
    Stack s;
    s = (Stack)malloc(sizeof(struct stack));
    s->top = -1;
    return s;
}


void PushS(Stack s, int x)
{
    s->top++;
    s->Data[s->top] = x;
}


int PopS(Stack s)
{
    return s->Data[s->top--];
}


int IsFullS(Stack s)
{
    if(s->top == MaxSize - 1)
        return 1;
    return 0;
}


int IsEmptyS(Stack s)
{
    if(s->top == -1)
        return 1;
    return 0;
}


Coordinate C[MaxSize];
int Visited[MaxSize];
int n, d;
void SetVisited()
{
    int i;
    for(i = 0; i < n; i++)
    {
        Visited[i] = 0;
    }
}


int FirstJump(int i)
{
    if(pow(C[i].x, 2) + pow(C[i].y, 2) <= pow((d +7.5), 2))
        return pow(C[i].x, 2) + pow(C[i].y, 2);
    else
        return 0;
}


int Jump(int i, int k)
{
    if(pow(C[i].x-C[k].x, 2) + pow(C[i].y - C[k].y, 2) <= pow(d, 2))
        return 1;
    else
        return 0;
}


int IsSave(int i)
{
    if(abs(abs(C[i].x) - 50) <= d || abs(abs(C[i].y) - 50) <= d)
        return 1;
    else
        return 0;
}


int comp(const void*a,const void*b)
{
    return FirstJump(*(int*)a)-FirstJump(*(int*)b);
}


void BFS()
{
    int i, k, last, tail, step, V, W;
    int b[n], path[MaxSize];
    Queue q;
    
    q = CreateQ();
    
    Stack s;
    
    s = CreateS();
    
    for(i = 0; i < n; i++)
    {
        b[i] = i;
    }
    qsort(b, n, sizeof(int), comp);
    for(i = 0; i < n; i++)
    {
        if(!Visited[b[i]] && FirstJump(b[i]))
        {
            AddQ(q, b[i]);
            Visited[b[i]] = 1;
            tail = b[i];
        }
    }
    step = 2;
    last = tail;
    while(!IsEmptyQ(q))
    {
        V = DeleteQ(q);
        if(IsSave(V))
        {
            printf("%d\n", step);
            for(k = 1; k < step; k++)
            {
                PushS(s, V);
                V = path[V];
            }
            while(!IsEmptyS(s))
            {
                V = PopS(s);
                printf("%d %d\n", C[V].x, C[V].y);
            }
            return;
        }
        for(W = 0; W < n; W++)
        {
            if(!Visited[W] && Jump(V, W))
            {
                AddQ(q, W);
                path[W] = V;
                Visited[W] = 1;
                tail = W;
            }
        }
        if(V == last)
        {
            step++;
            last = tail;
        }
    }
    printf("0\n");
    
}


int main()
{
    int i;
    
    scanf("%d %d\n", &n, &d);
    for(i = 0;i < n; i++)
    {
        scanf("%d %d\n", &C[i].x, &C[i].y);
    }
    SetVisited();
    if(d >= (100-15)/2 ) //第一步可以直接跳到岸上则直接输出1。
    {
        printf("1\n");
    }
    else
        BFS();
}
