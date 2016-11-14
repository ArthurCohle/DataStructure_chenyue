
#include <stdio.h>
#include <stdlib.h>

#define MinData 0

typedef struct TreeNode* HuffmanTree;
struct TreeNode
{
    int weight;
    HuffmanTree Left;
    HuffmanTree Right;
};

typedef struct HeapStruct* MinHeap;
struct HeapStruct{
    HuffmanTree elements;
    int size;
    int capacity;
};

MinHeap MinHeap_Build(int weight[], int Maxsize);
MinHeap MinHeap_Create(int Maxsize);
void MinHeap_Insert(MinHeap H, HuffmanTree HT);
HuffmanTree MinHeap_Delete(MinHeap H);
HuffmanTree HuffmanTree_Build(MinHeap H);
void Get_wpl(HuffmanTree HT, int *wpl, int layer);

int code_length(char *a);
int compare(char *c1, char *c2);

int main()
{
    int N;
    scanf("%d\n", &N);
    char c[N];
    int f[N];
    for (int i = 0; i < N; ++i){
        if(i == N-1)
            scanf("%c %d", &c[i], &f[i]);
        else
            scanf("%c %d ", &c[i], &f[i]);
    }
    MinHeap MH = MinHeap_Build(f, N);
    HuffmanTree HT = HuffmanTree_Build(MH);
    int MinWpl = 0;
    Get_wpl(HT, &MinWpl, 0);
    int M;
    scanf("%d\n", &M);
    char ch[N], code[N][64];
    for (int j = 0; j < M; ++j){
        for (int i = 0; i < N; ++i)
            scanf("%c %s\n", &ch[i], code[i]);
        int flag = 1;
        for (int i = 0; i < N; ++i){
            for (int k = i+1; k < N; ++k){
                if(compare(code[i], code[k])){
                    if(flag)
                        printf("No\n");
                    flag = 0;
                }
            }
        }
        int stu_wpl = 0;
        if(flag){
            for (int i = 0; i < N; ++i)
                stu_wpl += f[i]*code_length(code[i]);
            if(MinWpl == stu_wpl)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}

int code_length(char *a)
{
    int len = 0;
    while(*a != '\0'){
        a++;
        len++;
    }
    return len;
}

int compare(char *c1, char *c2)
{
    char *a = c1, *b = c2;
    while(*a!='\0' && *b!='\0'){
        if(*a != *b)
            return 0;
        a++;
        b++;
    }
    return 1;
}

MinHeap MinHeap_Build(int weight[], int Maxsize)
{
    MinHeap H = MinHeap_Create(Maxsize);
    HuffmanTree Temp = (HuffmanTree)malloc(sizeof(struct TreeNode));
    for (int i = 0; i < Maxsize; ++i){
        Temp->weight = weight[i];
        Temp->Left = NULL;
        Temp->Right = NULL;
        MinHeap_Insert(H, Temp);
    }
    free(Temp);
    return H;
}

MinHeap MinHeap_Create(int MaxSize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
    H->elements = (HuffmanTree)malloc(sizeof(struct TreeNode)*(MaxSize + 1));//因为elemens[0]作为哨兵，从[1]开始存放，所以分配MaxSize+1空间
    H->size = 0;
    H->capacity = MaxSize;
    H->elements[0].weight = MinData;//将elements[0]作为哨兵
    return H;
}

void MinHeap_Insert(MinHeap H, HuffmanTree HT)
{
    if(H->size == H->capacity)
        return;
    int i;
    i = ++H->size;//i指向插入后堆中的最后一个元素的位置
    for(; H->elements[i/2].weight > HT->weight; i/=2) //比较插入的结点和其父结点的大小
        H->elements[i] = H->elements[i/2];
    H->elements[i] = *HT;
}

HuffmanTree MinHeap_Delete(MinHeap H)
{
    HuffmanTree Temp, MinNode;
    if(H->size == 0)
        return NULL;
    MinNode = (HuffmanTree)malloc(sizeof(struct TreeNode));
    Temp = (HuffmanTree)malloc(sizeof(struct TreeNode));
    *MinNode = H->elements[1];//取出根结点的最小值
    *Temp = H->elements[H->size--];//用最小堆的最后一个元素从根结点开始向上过滤下层结点
    int Parent, Child;
    for(Parent = 1; Parent*2 <= H->size; Parent = Child){
        Child = Parent*2;
        if(Child != H->size && (H->elements[Child].weight > H->elements[Child+1].weight))
            Child++;//当存在右子结点，且右子节点小于左子节点时，Child指向较小者
        if(Temp->weight > H->elements[Child].weight)
            H->elements[Parent] = H->elements[Child];//移动Temp到下一层
        else
            break;
    }
    H->elements[Parent] = *Temp;
    free(Temp);
    return MinNode;
}

HuffmanTree HuffmanTree_Build(MinHeap H)
{
    HuffmanTree HT;
    int times = H->size;//H->size的值会发生变化，所以要用另一个变量来存储
    HT = (HuffmanTree)malloc(sizeof(struct TreeNode));
    for (int i = 1; i < times; ++i){//执行初始 H->size-1 次合并
        HT->Left = MinHeap_Delete(H);
        HT->Right = MinHeap_Delete(H);
        HT->weight = HT->Left->weight + HT->Right->weight;
        MinHeap_Insert(H, HT);
    }
    free(HT);
    HT = MinHeap_Delete(H);
    return HT;
}

void Get_wpl(HuffmanTree HT, int *wpl, int layer)
{
    if(HT->Left == NULL && HT->Right == NULL)
        *wpl += layer * HT->weight;
    else{
        Get_wpl(HT->Left, wpl, layer+1);
        Get_wpl(HT->Right, wpl, layer+1);
    } 
}
