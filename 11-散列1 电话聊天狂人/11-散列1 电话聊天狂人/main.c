//
//  main.c
//  11-散列1 电话聊天狂人
//
//  Created by ztb on 16/11/14.
//  Copyright © 2016年 ztb. All rights reserved.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXD 5 /*参与散列映射计算的字符个数*/
#define KEYLENGTH 11 /* 关键词字符串的最大长度 */
#define MAXTABLESIZE 1000000
typedef char ElementType[KEYLENGTH+1];/* 关键词类型用字符串 */
typedef int Index; /* 散列地址类型 */
typedef struct LNode *PtrToLNode;
struct LNode
{
    PtrToLNode Next;
    ElementType Data;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
typedef struct TblNode *HashTable;
struct TblNode/* 散列表结点定义 */
{
    int TableSize; /* 表的最大长度 */
    List Heads; /* 指向链表头结点的数组 */
};


int NextPrime(int N)
{
    int i,P;
    P = N%2 ? N+2:N+1;
    while(P < MAXTABLESIZE)
    {
        for(i = (int)sqrt(P);i > 2; i--)
        {
            if(P%i == 0)
            {
                break;
            }
        }
        if(i == 2)
        {
            break;
        }
        else
        {
            P += 2;
        }
    }
    return P;
}


int Hash(int Key, int P)
{
    return Key%P;
}

HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;
    H = malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Heads = malloc(sizeof(struct LNode)*H->TableSize);
    for(i = 0; i < H->TableSize; i++)
    {
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Count = 0;
        H->Heads[i].Next = NULL;
    }
    return H;
}

Position Find( HashTable H, ElementType Key )
{
    Position P;
    Index Pos;
    /* 初始散列位置 */
    Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize);
    P = H->Heads[Pos].Next; /* 从该链表的第1个结点开始 */ /* 当未到表尾,并且Key未找到时 */
    while( P && strcmp(P->Data, Key) )
        P = P->Next;
    return P; /* 此时P或者指向找到的结点,或者为NULL */
}
bool Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos;
    P = Find(H, Key);
    if(!P)
    {
        NewCell = malloc(sizeof(struct LNode));
        NewCell->Count = 1;
        strcpy(NewCell->Data, Key);
        Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize);
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else
    {
        P->Count++;
        return false;
    }
}

void ScanAndOutput( HashTable H )
{
    int i, MaxCnt, PCnt;
    MaxCnt = PCnt = 0;
    ElementType MinPhone;
    List Ptr;
    MinPhone[0] = '\0';
    for (i=0; i<H->TableSize; i++)/* 扫描链表 */
    {
        Ptr = H->Heads[i].Next;
        while (Ptr)
        {
            if (Ptr->Count > MaxCnt)
            {
                MaxCnt = Ptr->Count;/* 更新最大通话次数 */
                strcpy(MinPhone, Ptr->Data);
                PCnt = 1;
            }
            else if (Ptr->Count == MaxCnt)
            {
                PCnt ++; /* 狂人计数 */
                if ( strcmp(MinPhone, Ptr->Data)>0 )
                    strcpy(MinPhone, Ptr->Data); /* 更新狂人的最小手机号码 */
            }
        Ptr = Ptr->Next;
        }
    }
    printf("%s %d", MinPhone, MaxCnt);
    if ( PCnt > 1 )
        printf(" %d", PCnt);
    printf("\n");
}


void DestoryTable(HashTable H)
{
    Position temp;
    int i;
    
    for(i = H->TableSize - 1;i >= 0; i--)/*释放各个结点空间*/
    {
        while(H->Heads[i].Next)
        {
            temp = H->Heads[i].Next;
            H->Heads[i].Next = temp->Next;
            free(temp);
        }
    }
    free(H->Heads);/*释放List数组空间*/
    free(H);/*释放HashTable空间*/
    return;
}


int main()
{
    int i, N;
    HashTable H;
    ElementType Key;
    

    scanf("%d\n",&N);
    H = CreateTable(2*N);
    for(i = 0;i < N; i++ )
    {
        scanf("%s", Key);
        Insert(H, Key);
        scanf("%s", Key);
        Insert(H, Key);
    }
    ScanAndOutput(H);
    DestoryTable(H);
    return 0;
}










