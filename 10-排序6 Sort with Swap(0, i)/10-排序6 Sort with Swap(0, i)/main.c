//
//  main.c
//  10-排序6 Sort with Swap(0, i)
//
//  Created by ztb on 16/11/5.
//  Copyright © 2016年 ztb. All rights reserved.
//

//#include <stdio.h>
//#define MaxSize 100000
//
//
//int N, A[MaxSize],Sorted;
//
//
//void Swap(int *a, int *b);
//int CheckNum(int Num);
//int IsSorted();
//void Show();
//
//int main()
//{
//    int i,SwapTimes, Location0;
//    scanf("%d", &N);
//    Sorted = 0;
//    SwapTimes = 0;
//    for(i = 0; i < N; i++)
//    {
//        scanf("%d", &A[i]);
//        if(i != 0)
//        {
//            if(A[i] == i)
//            {
//                Sorted++;
//            }
//        }
//    }
//    Location0 = CheckNum(0);
//    while(!IsSorted())
//    {
//        if(Location0 != 0)
//        {
//            i = CheckNum(Location0);
//            printf("%d<->%d\n",A[Location0],A[i]);
//            Swap(&A[Location0], &A[i]);
//            Sorted++;
//            SwapTimes++;
//        }
//        else
//        {
//            for(i = 1; i < N;i++)
//            {
//                if(A[i] != i)
//                    break;
//            }
//            Swap(&A[0], &A[i]);
//            SwapTimes++;
//        }
//        Location0 = i;
//    }
//    printf("%d\n",SwapTimes);
//}
//
//
//void Swap(int *a, int *b)
//{
//    int temp;
//    temp = *a;
//    *a = *b;
//    *b = temp;
////    Show();
//}
//
//
//int CheckNum(int Num)
//{
//    int i;
//    for(i = 0; i < N; i++)
//    {
//        if(A[i] == Num)
//            break;
//    }
//    return i;
//}
//
//
//int IsSorted()
//{
//    if(Sorted != N-1)
//        return 0;
//    return 1;
//}
//
//
//void Show()
//{
//    int i;
//    printf("log:");
//    for(i = 0; i < N; i++)
//    {
//        printf(" %d",A[i]);
//    }
//    printf("\n");
//}


//int main()
//{
//    int N,i;
//    int Sorted[MaxSize], A[MaxSize];
//    int j,circle,Mark,count,circleNum;
//    
//    scanf("%d", &N);
//    for(i = 0; i < N; i++)
//    {
//        Sorted[i] = 0;
//    }
//    for(i = 0; i < N; i++)
//    {
//        scanf("%d", &A[i]);
//        if(A[i] == i)
//        {
//            Sorted[i] = 1;
//        }
//    }
//    count = 0;
//    circleNum = 0;
//    for(i = 0; i < N; i++)
//    {
//        if(!Sorted[i])
//        {
//            Sorted[i] = 1;
//            Mark = i;//记录入口值
////            printf("Mark:%d\n",Mark);
//            j = i;//j用于迭代
//            circle = 1;//初始化环的长度
//            while(A[j] != Mark)
//            {
//                circle++;
////                printf("%d->%d\n",j,A[j]);
//                j = A[j];
//                Sorted[j] = 1;
//            }
////            printf("Circle%d:%d\n",Mark,circle);
//            count += circle;
//            circleNum++;
//        }
//    }
//    count = count + circleNum;
//    if(A[0] != 0)
//    {
//        count -= 2;
//    }
//    printf("%d\n",count);
////    printf("circleNum:%d\n",circleNum);
//}
#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
// int findNotOk(int A[], int N)
int findNotOk(int A[], int begin, int N)// 要从begin开始，从1开始会超时
{
    for (int i = begin; i < N; i++)
        if (A[i] != i)
            return i;
    return 0;
}

int main(int argc, char const *argv[])
{
    // freopen("test.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    int A[N], tmp;
    for (int i = 0; i < N; i++){
        scanf("%d", &tmp);
        A[i] = tmp;
    }
    int cnt = 0;
    int current = findNotOk(A, 1, N);
    printf("current:%d\n",current);
    while(current != 0){
        if (A[0] == 0){//
            A[0] = A[current];
            A[current] = 0;
            cnt++;
        }
        while (A[0] != 0){
            printf("%d<->%d\n",A[0],A[A[0]]);
            swap(&A[0], &A[A[0]]);
            cnt++;
        }
        current = findNotOk(A, current, N);
        printf("current:%d\n",current);
    }
    printf("%d", cnt);
    return 0;
}
