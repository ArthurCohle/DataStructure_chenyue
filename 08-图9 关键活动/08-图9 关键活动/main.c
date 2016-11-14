//
//  main.c
//  08-图9 关键活动
//
//  Created by ztb on 16/10/21.
//  Copyright © 2016年 ztb. All rights reserved.
//

//
//  main.c
//  08-图8 How Long Does It Take
//
//  Created by ztb on 16/10/21.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

#define MAXN 102
#define INFINITY 65535

int G[MAXN][MAXN] ;
int earliest[MAXN];
int latest[MAXN];
int indegree[MAXN];
int outdegree[MAXN];

void intial(int n);
void late_time(int n,int max);
int early_time(int n);
int max(int a, int b);
int min(int a, int b);

int main()
{
    //freopen("test.txt", "r", stdin);
    int n,m;
    scanf("%d %d",&n,&m);//读入节点，读入活动数
    intial(n);
    
    int i;
    int s,e,c;//source,end,cost
    for(i=1;i<=m;i++)//读入数据
    {
        scanf("%d %d %d",&s,&e,&c);
        G[s][e] = c;//有向边
        indegree[e]++;//入度初始化
        outdegree[s]++;//出度初始化
    }
    
    int flag;
    flag = early_time(n);
    if(flag == -1)
    {
        printf("0\n");
    }
    else
    {
        printf("%d\n",flag);
        late_time(n,flag);//进行latest【】处理
        for (int i = 1; i <= n; i++)
        {
            for (int j = n; j >= 1; j--)
            {
                if (G[i][j] >= 0 && (latest[j] - earliest[i] == G[i][j]))
                    printf("%d->%d\n", i, j);
            }
        }
    }
    
    return 0;
}


void late_time(int n,int max)
{
    int queue[n];//建立一个简单队列
    int first = -1,rear = -1;
    
    for(int i=1; i<=n; i++)//将入度为0的节点压进去
    {
        if(outdegree[i] == 0)
        {
            queue[++rear] = i; //入队
            latest[i] = max;
        }
    }
    
    
    while(first < rear)
    {
        int v = queue[++first];//出队
        for( int i=n; i>=1; i--) //对V的每个邻接点处理
        {
            if(G[i][v]>=0)
            {
                outdegree[i]--;//出度减一
                latest[i] = min(latest[i],latest[v]-G[i][v]);
                if(outdegree[i] == 0)
                {
                    queue[++rear] = i;
                }
            }
            
        }
    }
}

int early_time(int n)
{
    int queue[n];//建立一个简单队列
    int first = -1,rear = -1;
    
    for(int i=1; i<=n; i++)//将入度为0的节点压进去
    {
        if(indegree[i] == 0)
        {
            queue[++rear] = i; //入队
        }
    }
    
    int cnt = 0;
    while(first < rear)
    {
        int v = queue[++first];//出队
        cnt++;
        for( int i=1; i<=n; i++) //对V的每个邻接点处理
        {
            if(G[v][i]>=0)
            {
                indegree[i]--;//入度减一
                earliest[i] = max(earliest[i],earliest[v]+G[v][i]);
                if(indegree[i] == 0)
                {
                    queue[++rear] = i;
                }
            }
            
        }
    }
    
    int ans = 0;
    if (cnt != n)//不能拓扑排序
    {
        ans = -1;
    }
    else
    {
        ans = earliest[0];//可以拓扑排序，找最大值
        for(int i=1; i<=n; i++)
        {
            if(earliest[i] > ans)
            {
                ans = earliest[i];
            }
        }
    }
    
    return ans;
}

void intial(int n)
{
    int i,j;
    for( i=1;i<=n;i++)//节点从1开始
    {
        for(j=0;j<=n;j++)
        {
            G[i][j] = -1;
        }
        earliest[i] = 0;
        indegree[i] = 0;
        outdegree[i] = 0;
        latest[i] = INFINITY;
    }
    
}

int max(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
int min(int a, int b)
{
    if(a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
