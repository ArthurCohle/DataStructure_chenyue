//
//  main.c
//  11-散列3 QQ帐户的申请与登陆
//
//  Created by ztb on 16/11/2016.
//  Copyright © 2016 ztb. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode *Position;
typedef struct ListNode{
    char account[11], password[17];
    Position Next;
} *List;

typedef struct HashTbl{
    int TableSize;
    List *TheLists;//建立一个ListNode的指针数组
} *HashTable;

int NextPrime(int x);
HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(char Key[], HashTable H);
void Insert(char Key[], char password[], HashTable H);
int Hash(int Key, int TableSize);
int Find_account(char Key[], HashTable H);
int Check_passwrod(Position P, char password[]);

int main(int argc, char const *argv[])
{
    //  freopen("test.txt", "r", stdin);
    int N;
    scanf("%d\n", &N);
    HashTable H = InitializeTable(2 * N);
    char c, s1[11] = {}, s2[17] ={};
    for (int i = 0; i < N; i++){
        scanf("%c %s %s\n", &c, s1, s2);
        if (c == 'N'){
            if (Find_account(s1, H) != 1){
                Insert(s1, s2, H);
                printf("New: OK\n");
            }else
                printf("ERROR: Exist\n");
        }
        if (c == 'L'){
            if (Find_account(s1, H) == 1){
                if (Check_passwrod(Find(s1, H), s2))
                    printf("Login: OK\n");
                else
                    printf("ERROR: Wrong PW\n");
            }else
                printf("ERROR: Not Exist\n");
        }
    }
    DestroyTable(H);
    return 0;
}

int NextPrime(int x)
{
    int i;
    for (int Next = x; ; Next++){
        for (i = 2; i * i <= Next; i++)
            if (Next % i == 0)
                break;
        if (i * i > Next)
            return Next;
    }
}

HashTable InitializeTable(int TableSize)
{
    HashTable H;
    H = (HashTable)malloc(sizeof(struct HashTbl));
    H->TableSize = NextPrime(TableSize);
    H->TheLists = (List*)malloc(sizeof(List)*H->TableSize);
    for (int i = 0; i != H->TableSize; i++){
        H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
        H->TheLists[i]->Next = NULL;
    }
    return H;
}

void DestroyTable(HashTable H)
{
    for (int i = 0; i < H->TableSize; i++)
        free(H->TheLists[i]);
    free(H->TheLists);
    free(H);
}

Position Find(char Key[], HashTable H)
{
    Position P;
    List L;
    L = H->TheLists[Hash(atoi(Key + 3), H->TableSize)];
    P = L->Next;
    while (P != NULL && strcmp(P->account, Key)){
        P = P->Next;
    }
    return P;
}

int Find_account(char Key[], HashTable H)
{
    Position P;
    List L;
    L = H->TheLists[Hash(atoi(Key + 3), H->TableSize)];
    P = L->Next;
    while (P != NULL){
        if (strcmp(P->account, Key) == 0)
            return 1;
        else
            P = P->Next;
    }
    return 0;
}

void Insert(char Key[], char password[], HashTable H)
{
    Position Pos, Tmp;
    List L = H->TheLists[Hash(atoi(Key + 3), H->TableSize)];
    Pos = Find(Key, H);
    if (Pos == NULL){
        Tmp = (List)malloc(sizeof(struct ListNode));
        strcpy(Tmp->account, Key);
        strcpy(Tmp->password, password);
        Tmp->Next = L->Next;
        L->Next = Tmp;
    }
}

int Hash(int Key, int TableSize)
{
    return (Key % TableSize);
}

int Check_passwrod(Position P, char password[])
{
    if (strcmp(P->password, password) == 0)
        return 1;
    else
        return 0;
}
