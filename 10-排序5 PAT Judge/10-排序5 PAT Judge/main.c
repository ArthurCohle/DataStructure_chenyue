//
//  main.c
//  10-排序5 PAT Judge
//
//  Created by ztb on 16/11/5.
//  Copyright © 2016年 ztb. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct stu{
    int id;
    int s[6];//各题分数
    int score;//总分
    int pass;//完全正确的题目数
    int ns;//无提交或无任何通过编译标志，0代表没有通过
} Stu;

void sort(Stu stu[], int N);
int compare(const Stu *s1, const Stu *s2);

int main(int argc, char const *argv[])
{
    // freopen("test.txt", "r", stdin);
    int N, K, M;
    scanf("%d %d %d", &N, &K, &M);
    Stu *student = (Stu*)malloc(sizeof(Stu)*(N+1));
    for (int i = 1; i <= N; i++){
        student[i].id = 0, student[i].score = 0, student[i].pass = 0, student[i].ns = 0;
        for (int j = 1; j <= K; j++)
            student[i].s[j] = -2;
    }
    int p[6];//各题满分
    for (int i = 1; i <= K; i++)
        scanf("%d", &p[i]);
    int id, p_id, ps;
    for (int i = 0; i < M; i++){
        scanf("%d %d %d", &id, &p_id, &ps);
        if (ps > student[id].s[p_id])
            student[id].s[p_id] = ps;
    }
    for (int i = 1; i <= N; i++){
        student[i].id = i;
        for (int j = 1; j <= K; j++){
            if (student[i].s[j] >= 0){
                student[i].score += student[i].s[j];
                student[i].ns = 1;
            }
            if (student[i].s[j] == p[j])
                student[i].pass++;
        }
    }
    sort(student, N);
    int rank = 1;
    int score = student[1].score;
    for (int i = 1; i <= N; i++){
        if (student[i].ns == 0)
            // break;   //break不应该退出了整个for循环吗，为什么结果都过了
            continue;   //我没想明白这里为什么用break和continue对结果无影响，都过了
        if (student[i].score != score){
            rank = i;
            score = student[i].score;
        }
        printf("%d %05d %d", rank, student[i].id, student[i].score);
        for (int j = 1; j <= K; j++){
            if (student[i].s[j] >= 0)
                printf(" %d", student[i].s[j]);
            else if (student[i].s[j] == -1)
                printf(" 0");
            else
                printf(" -");
        }
        printf("\n");
    }
    free(student);
    return 0;
}

void sort(Stu student[], int N)
{
    Stu *tmp = (Stu*)malloc(sizeof(Stu));
    for (int P = 2; P <= N; P++){
        *tmp = student[P];
        int i;
        for (i = P; i > 1 && compare(&student[i-1], tmp); i--)
            student[i] = student[i-1];
        student[i] = *tmp;
    }
    free(tmp);
}

int compare(const Stu *s1, const Stu *s2)
{
    if (s1->score < s2->score)
        return 1;
    else if (s1->score == s2->score)
        return s1->pass < s2->pass;
    else
        return 0;
}
