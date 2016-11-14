//
//  main.c
//  09-排序2 Insert or Merge
//
//  Created by ztb on 16/10/30.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemenType;


void swap(ElemenType *a, ElemenType *b)
{
    ElemenType temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}

void PercDown(ElemenType A[], int i, int N)
{
    ElemenType temp;
    int Parent, Child;
    temp = A[i];
    for(Parent = i;Parent <= N; Parent = Child)
    {
        Child = 2*Parent + 1;
        if((Child+1 <=N-1) && A[Child + 1] > A[Child])
            Child++;
        if(temp >= A[Child])
            break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = temp;
}

void Bubble_Sort(ElemenType A[], int N)
{
    int P, i, flag;
    for(P = N -1; P >= 0; P--)
    {
        flag = 0;
        for( i = 0; i < P; i++)
        {
            if(A[i] > A[i + 1])
            {
                swap(A+i, A+i+1);
                flag = 1;
            }
        }
        if(flag == 0)
        {
            break;
        }
    }
}


void Insertion_Sort(ElemenType A[], int N)
{
    int P, i, temp;
    for(P = 1; P < N; P++)
    {
        temp = A[P];
        for( i = P; i >= 1 && A[i-1] > temp; i--)
        {
            A[i] = A[i-1];
        }
        A[i] = temp;
    }
}


void Shell_Sort(ElemenType A[], int N)
{
    int P, i, temp, D;
    for(D = N/2; D > 0; D/=2)
    {
        for(P = D; P < N; P++)
        {
            temp = A[P];
            for( i = P; i >= D && A[i-D] > temp; i -= D)
            {
                A[i] = A[i-D];
            }
            A[i] = temp;
        }
    }
}


void Merge(ElemenType A[], ElemenType TmpA[], int L,int R, int RightEnd)
{
    int LeftEnd, Tmp, Num,i;
    LeftEnd = R - 1;
    Tmp = L;
    Num = RightEnd - L + 1;
    while(L <= LeftEnd && R <= RightEnd)
    {
        if(A[L] <= A[R])
        {
            TmpA[Tmp++] = A[L++];
        }
        else
        {
            TmpA[Tmp++] = A[R++];
        }
    }
    while(L <= LeftEnd)
    {
        TmpA[Tmp++] = A[L++];
    }
    while(R <= RightEnd)
    {
        TmpA[Tmp++] = A[R++];
    }
    for(i = 0; i < Num; i++)
    {
        A[RightEnd] = TmpA[RightEnd];
        RightEnd--;
    }
}


void Sort(ElemenType A[],ElemenType TmpA[], int L, int RightEnd)
{
    int center;
    if(L < RightEnd)
    {
        center = (L + RightEnd)/2;
        Sort(A, TmpA, L, center);
        Sort(A, TmpA, center + 1, RightEnd);
        Merge(A, TmpA, L, center + 1, RightEnd);
    }
}


void Merge_Sort(ElemenType A[], int N)
{
    ElemenType *TmpA;
    TmpA = malloc(N*sizeof(ElemenType));
    if(TmpA != NULL)
    {
        Sort(A, TmpA, 0, N-1);
    }
}


void Show(ElemenType A[], int N)
{
    int i;
    for(i = 0; i < N; i++ )
    {
        if(i == 0)
        {
            printf("%d", A[i]);
        }
        else
        {
            printf(" %d", A[i]);
        }
    }
    printf("\n");
}


bool IsEqual(ElemenType A[], ElemenType B[], int N)
{
    int i;
    for(i = 0; i < N; i++)
    {
        if(A[i] != B[i])
        {
            return false;
        }
    }
    return true;
}


bool IsInsertion(ElemenType A[], ElemenType B[], int N)
{
    int i, Length, C[N], flag;
    flag = 0;
    for(i = 0; i < N; i++)
    {
        C[i] = A[i];
    }
    for(Length = 2; Length < N;Length ++)
    {
        Insertion_Sort(C, Length);
        if(flag)
        {
            Show(C, N);
            return true;
        }
        if(IsEqual(C, B, N))
        {
            printf("Insertion Sort\n");
            flag = 1;
        }
    }
    return false;
}


void IsMerge(ElemenType A[], ElemenType B[], int N)
{
    int i, Length, C[N], flag;
    flag = 0;
    for(i = 0; i < N; i++)
    {
        C[i] = A[i];
    }
    for(Length = 2; Length <= N; Length *= 2)
    {
        for(i = 0;i + Length < N; i += Length)
        {
            Insertion_Sort(C + i, Length);
        }
        Insertion_Sort(C + i, N - i);
        if(flag)
        {
            Show(C, N);
            return;
        }
        if(IsEqual(C, B, N))
        {
            printf("Merge Sort\n");
            flag = 1;
        }
    }
}


int main()
{
    int i, N;
    
    scanf("%d\n", &N);
    ElemenType A[N], B[N];
    
    for(i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
    for(i = 0; i < N; i++)
    {
        scanf("%d", &B[i]);
    }
    if(!IsInsertion(A, B, N))
    {
        IsMerge(A, B, N);
    }
}
