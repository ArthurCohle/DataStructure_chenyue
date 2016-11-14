//
//  main.c
//  10-排序4 统计工龄
//
//  Created by ztb on 16/11/5.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#define MaxWorkAge 50

int A[MaxWorkAge+1];

void SetA()
{
    int i;
    for(i = 0; i <= MaxWorkAge; i++)
    {
        A[i] = 0;
    }
}
int main()
{
    int N, i, WorkAge;
    
    scanf("%d\n", &N);
    SetA();
    for(i = 0; i < N; i++)
    {
        scanf("%d", &WorkAge);
        A[WorkAge]++;
    }
    for(WorkAge = 0; WorkAge <= MaxWorkAge; WorkAge++)
    {
        if(A[WorkAge] != 0)
        {
            printf("%d:%d\n",WorkAge, A[WorkAge]);
        }
    }
}
