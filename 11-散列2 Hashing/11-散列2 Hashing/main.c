//
//  main.c
//  11-散列2 Hashing
//
//  Created by ztb on 11/15/16.
//  Copyright © 2016 ztb. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#define MaxSize 10000
enum InfoType {Legitimate, Empty, Deleted};
typedef int ElementType;
ElementType Pri[MaxSize];
struct HashCell
{
    ElementType Element;
    enum InfoType Info;
};
typedef struct HashCell *Cell;
typedef int Postion;
struct HashTbl
{
    int TableSize;
    Cell Cells;
};
typedef struct HashTbl *HashTable;


HashTable CreateHashTable(int TableSize);

Postion FindKey(HashTable H, ElementType Key);
Postion InsertKey(HashTable H, ElementType Key);
//int NextPrime(int N);
int NextPrime(int N)
{
    int i,P;
    if(N <= 2)
        return 2;
    P = N%2 ? N:N+1;
    while(1)
    {
        for(i = (int)sqrt(P);i > 2; i--)
        {
            if(P%i == 0)
            {
                break;
            }
        }
        if(i <= 2)
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
//int NextPrime(int x)
//{
//    if (x < 2)//要注意1不是素数
//        x++;
//    int i;
//    for (int Next = x; ; Next++){
//        for (i = 2; i * i <= Next; i++)
//            if (Next % i == 0)
//                break;
//        if (i * i > Next)
//            return Next;
//    }
//}
int Hash(int TableSize, ElementType Key)
{
    return Key%TableSize;
}


HashTable CreateHashTable(int TableSize)
{
    HashTable H;
    int i;
    H = malloc(sizeof(struct HashTbl));
    H->TableSize = NextPrime(TableSize);
    H->Cells = malloc(H->TableSize*sizeof(struct HashCell));
    for(i = 0; i < H->TableSize; i++)
    {
        H->Cells[i].Element = -1;
        H->Cells[i].Info = Empty;
    }
    return H;
}


Postion FindKey(HashTable H, ElementType Key)
{
    Postion NewPos,CurrentPos;
    int CNum;
    CNum = 0;
    CurrentPos = Hash(H->TableSize, Key);
    NewPos = CurrentPos;
    while(H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Element != Key)
    {
//        if(++CNum % 2)
//        {
        CNum++;
        NewPos = CurrentPos + CNum*CNum;
//            NewPos = CurrentPos + (CNum + 1)/2*(CNum + 1)/2;
            while(NewPos >= H->TableSize)
            {
                NewPos = NewPos - H->TableSize;
            }
//        }
//        else
//        {
//            NewPos = CurrentPos - (CNum )/2*(CNum)/2;
//            while(NewPos < 0)
//            {
//                NewPos += H->TableSize;
//            }
//        }
        if(CNum > H->TableSize)/*若冲突次数大于列表长度则表示无法找到合适位置，将newpos置为-1，返回。*/
        {
            NewPos = -1;
            break;
        }
    }
    return NewPos;
}

Postion InsertKey(HashTable H, ElementType Key)
{
    Postion Pos;
    Pos = FindKey(H, Key);
    if(Pos != -1)
    {
        H->Cells[Pos].Element = Key;
        H->Cells[Pos].Info = Legitimate;
    }
    return Pos;
}


int main()
{
    int MSize, N;
    int i;
    HashTable H;
    ElementType Key;
    scanf("%d %d\n", &MSize, &N);
    H = CreateHashTable(MSize);
    for(i = 0; i < N; i++)
    {
        scanf("%d", &Key);
        Pri[i] = InsertKey(H, Key);
    }
    for(i = 0; i < N; i++)
    {
        if(i != 0)
        {
            printf(" ");
        }
        if(Pri[i] == -1)
        {
            printf("-");
        }
        else
        {
            printf("%d",Pri[i]);
        }
    }
    printf("\n");
    return 0;
}
