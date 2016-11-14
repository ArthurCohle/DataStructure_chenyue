//
//  main.c
//  05-树8 堆中的路径
//
//  Created by ztb on 16/10/10.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MinData -10001

typedef int ElementType;
typedef struct HeapStruct* MinHeap;
struct HeapStruct
{
    ElementType* Elements;
    int Size;
    int Capacity;
};

MinHeap Create(int MaxSize);
bool IsFull(MinHeap H);
void Insert(MinHeap H, ElementType item);
bool IsEmpty(MinHeap H);
ElementType DeleteMin(MinHeap H);
MinHeap BuildMinHeap(MinHeap H);

MinHeap Create(int MaxSize)
{
    MinHeap H = malloc(sizeof(struct HeapStruct));
    H->Elements = malloc((MaxSize+1)*sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MinData;
    return H;
}


MinHeap BuildMinHeap(MinHeap H)
{
    int Parent, Child, i;
    ElementType temp;
    for(i = H->Size/2; i > 0; i--)
    {
        temp = H->Elements[i];
        for(Parent = i; Parent * 2 <= H->Size;Parent = Child)
        {
            Child = Parent * 2;
            if((Child != H->Size) && (H->Elements[Child] > H->Elements[Child + 1]))
            {
                Child ++;
            }
            if(temp <= H->Elements[Child])
                break;
            else
                H->Elements[Parent] = H->Elements[Child];
        }
        H->Elements[Parent] = temp;
    }
    return H;
}

void Insert(MinHeap H, ElementType item)
{
    int i;
    i = ++H->Size;
    for(; H->Elements[i/2] > item; i /= 2)
        H->Elements[i] = H->Elements[i/2];
    H->Elements[i] = item;
}
int main()
{
    int i, j, N, M, flag, item;
    MinHeap H;
    
    scanf("%d %d", &N, &M);
    H = Create(N);
    for(j = 1; j <= N;j++)
    {
        scanf("%d", &item);
        Insert(H, item);
    }
    H = BuildMinHeap(H);
    for(j = 1;j <= M;j++)
    {
        scanf("%d", &i);
        flag = 0;
        while(i)
        {
            if(!flag)
                flag = 1;
            else
                printf(" ");
            printf("%d",H->Elements[i]);
            i /= 2;
        }
        printf("\n");
    }
}
