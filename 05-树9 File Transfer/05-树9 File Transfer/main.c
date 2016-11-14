//
//  main.c
//  05-树9 File Transfer
//
//  Created by ztb on 16/10/11.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#define MaxSize 10001

typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MaxSize];

void Initialization(SetType S, int n)
{
    int i;
    for(i = 1;i <= n; i ++)
    {
        S[i] = -1;
    }
}


SetName Find(SetType S, ElementType X)
{
    for(; S[X] >= 0; X = S[X]);
    return X;
}


void Union(SetType S, SetName Root1, SetName Root2)
{
    if(S[Root2] < S[Root1])
    {
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
    else
    {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}


void Input_connection(SetType S)
{
    ElementType c1, c2;
    SetName Root1, Root2;
    
    scanf("%d %d\n", &c1, &c2);
    Root1 = Find(S, c1);
    Root2 = Find(S, c2);
    if(Root1 != Root2)
    {
        Union(S, Root1, Root2);
    }
    return;
}


void Check_connection(SetType S)
{
    ElementType c1, c2;
    SetName Root1, Root2;
    
    scanf("%d %d\n", &c1, &c2);
    Root1 = Find(S, c1);
    Root2 = Find(S, c2);
    if(Root1 != Root2)
    {
        printf("no\n");
    }
    else
    {
        printf("yes\n");
    }
    return;
}


void Check_network(SetType S, int n)
{
    int i, counter;
    counter = 0;
    for(i = 1;i <= n;i++)
    {
        if(S[i] < 0)
            counter++;
    }
    if(counter == 1)
    {
        printf("The network is connected.\n");
    }
    else
    {
        printf("There are %d components.\n", counter);
    }
}


int main()
{
    SetType S;
    int n;
    char in;
    scanf("%d\n", &n);
    Initialization(S, n);
    do
    {
        scanf("%c", &in);
        switch(in)
        {
            case 'I':Input_connection(S);break;
            case 'C':Check_connection(S);break;
            case 'S':Check_network(S, n);break;
        }
    }while(in != 'S');
    return 0;
}
