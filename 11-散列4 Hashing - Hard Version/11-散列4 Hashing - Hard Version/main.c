//
//  main.c
//  11-散列4 Hashing - Hard Version
//
//  Created by ztb on 16/11/2016.
//  Copyright © 2016 ztb. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 1000
int Mark[MaxSize];
typedef int ElementType;

typedef struct HashTbl
{
    int TableSize;
    ElementType *Cells;
}*HashTable;


int Hash(int TableSize, int Key)
{
    return Key%TableSize;
}


HashTable InitilizeTable(int TableSize)
{
    HashTable H;
    H = malloc(sizeof(struct HashTbl));
    H->TableSize = TableSize;
    H->Cells = malloc(H->TableSize*sizeof(ElementType));
    return H;
}


void Swap(int *a, int *b)
{
    int Temp;
    Temp = *a;
    *a = *b;
    *b = Temp;
    return;
}


void Sort(ElementType A[], int N)
{
    int i,j;
    for(i = N - 1; i > 0; i--)
    {
        for(j = 0; j < i; j++)
        {
            if(A[j+1] < A[j])
            {
                Swap(&A[j+1], &A[j]);
            }
        }
    }
    return;
}


void Show(ElementType A[],int N)
{
    int i;
    for(i = 0; i < N; i++)
    {
        if(i != 0)
        {
            printf(" ");
        }
        printf("%d", A[i]);
    }
    printf("\n");
    return;
}


bool Check(HashTable H, ElementType Key)//检查Key能否插入给定位置
{
    int Pos;
    Pos = Hash(H->TableSize, Key);
    while(1)
    {
        if(Mark[Pos]==0)//Mark[pos]=0说明pos处可插入
            break;
        Pos++;
        while(Pos >= H->TableSize)
        {
            Pos -= H->TableSize;
        }
    }
    if(H->Cells[Pos] == Key)//检查可插入位置是否为给定位置
    {
        Mark[Pos] = 1;
        return true;
    }
    else
        return false;
}


int main()
{
    int N,CPostiveNum;
    int Key;
    int i, j;
    int CNum;
    int InsertedNum;
    ElementType Postive[MaxSize];
    HashTable H;
    
    CPostiveNum = 0;
    scanf("%d\n", &N);
    for(i = 0; i < N; i++)
    {
        Mark[i] = 0;
    }
    H = InitilizeTable(N);
    for(i = 0; i < N; i++)
    {
        scanf("%d", &Key);
        H->Cells[i] = Key;
        if(Key >= 0)
        {
            Postive[CPostiveNum++] = Key;//记录非空处的key
        }
    }
    Sort(Postive, CPostiveNum);//对非负序列排序
    CNum = 0;
    InsertedNum = 0;
    for(i= 0; i < CPostiveNum - 1; i++)/*对非负序列从小到大进行插入,插入位置与给定位置不同时则与后方元素调换位置再进行插入操作，如此循环，直到成功插入为止。再进行下个元素的插入。当所有元素都成功插入时，外循环结束。*/
    {
        for(j = 0;j < CPostiveNum - i; j++)
        {
            Swap(&Postive[i], &Postive[i + j]);
            if(Check(H,Postive[i]))
            {
                break;
            }
        }
    }
    Show(Postive, CPostiveNum);
    return 0;
}
