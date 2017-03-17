#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 7    // 图的最大节点数

int TopNum[7];              // 入度数组

typedef struct EdgeNode     // 邻接顶点
{
    int adjvertex;
    struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode    // 顶点
{
    int vertex;
    EdgeNode *firstEdge;
}VertexNode, HeadCellArray[MAX_VERTEX_NUM];

typedef struct Graph         // 图结构
{
    int numVertex, numEdge;
    HeadCellArray headCellArray;
}Graph;

typedef struct QueueRecord    // 队列结构（数组）
{
    int capacity;
    int rear;
    int front;
    int size;
    int *array;
}Queue, *QueueLink;

int IsEmpty(Queue Q)    // 判断队列是否为空
{
    return Q.size==0;
}

int IsFull(Queue Q)
{
    return Q.size==Q.capacity;    // 判断队列是否已满
}

void MakeEmpty(Queue Q)    // 清空队列
{
    Q.size=0;
    Q.rear=0;
    Q.front=1;
}

Queue CreateQueue(int numVertex)    // 创建队列
{
    Queue Q;

    Q=*(Queue*)malloc(sizeof(struct QueueRecord));
    Q.capacity=numVertex;
    Q.array=(int*)malloc(sizeof(int)*numVertex);
    MakeEmpty(Q);

    return Q;
}

void Enqueue(int x, Queue Q)    // 入队
{
    if(IsFull(Q))
    {
        printf("队列已满\n");
        exit(1);
    }

    Q.size++;
//    printf("size=%d", Q.size);

    if(++Q.rear==Q.capacity)
        Q.rear=0;

    Q.array[Q.rear]=x;    
    printf("Q.array=%d\n", Q.array[Q.rear]);

    printf("入队成功\n");

    return;
}

int FrontAndDequeue(Queue Q)    // 出队并且返回
{
    int result;

    if(IsEmpty(Q))
    {
        printf("队列已空\n");
        exit(1);
    }

    result=Q.array[Q.front];   
    Q.array[Q.front]=100;    // 已经出队的元素标志为100
    Q.front++;
    if(Q.front==Q.capacity)
        Q.front=0;
    Q.size--;

    return result;
}

void DisposeQueue(Queue Q)    // 销毁队列
{
    QueueLink p=&Q;

    if(p != NULL)
    {
        free(p->array);
        free(p);
    }

    return;
}

int * MakeIndegree(Graph G)
{
    int i;
    int *indegree;
    EdgeNode *p;

    indegree=(int*)malloc(sizeof(int)*G.numVertex);

    for (i=0;i<G.numVertex;i++)
    {
        p = G.headCellArray[i].firstEdge;
        while(p)
        {
            (indegree[p->adjvertex])++;
            p = p->next;
        }
    }

    return indegree;
}

void Topsort(Graph G)
{
    int i, v, w;
    int counter=0;
    int *indegree;
    Queue Q;
    EdgeNode *p;

    Q=CreateQueue(7);
    indegree=MakeIndegree(G);

    for(i=0;i<7;i++)
    {
        if(indegree[i]==0)
        {
            printf("Has a indegree zero\n");
            Enqueue(i ,Q);
        }
    }

    while(IsEmpty(Q)!=1)
    {
        printf("开始循环");
        v=FrontAndDequeue(Q);
        TopNum[v]=++counter;

        p=G.headCellArray[v].firstEdge;
        while(p)
        {
            w=p->adjvertex;
            indegree[w]=indegree[w]-1;

            printf("\n");
            printf("w=%d", indegree[w]);
            printf("\n");

            if(indegree[w]==0)
                Enqueue(w, Q);
            p=p->next;
        }
    }

//    if(counter != 7)
//    {
//        printf("counter=%d\n", counter);
//        printf("Graph has a cycle");
//        exit(1);
//    }

//    DisposeQueue(Q);

    return;
}

Graph InitGraph()
{
    Graph G;
    EdgeNode *p;
    int i, u, v;

    printf("请输入节点数和边数：\n");
    scanf("%d%d", &G.numVertex, &G.numEdge);

    for (i=0;i<G.numVertex;i++)
    {
        G.headCellArray[i] = *(VertexNode*)malloc(sizeof(VertexNode));
        G.headCellArray[i].vertex=i;
        G.headCellArray[i].firstEdge=NULL;
    }

    for (i=0;i<G.numEdge;i++) 
    {
        printf("请输入边(u, v),即u->v\n");
        scanf("%d%d", &u, &v);

        p=(EdgeNode*)malloc(sizeof(EdgeNode));
        p->adjvertex=v;
        p->next=G.headCellArray[u].firstEdge;
        G.headCellArray[u].firstEdge=p;
    }

    return G;
}

void PrintGraph(Graph G)
{
    int i;
    EdgeNode *p;

    for(i=0;i<G.numVertex;i++)
    {
        printf("顶点%d", G.headCellArray[i].vertex);
        p=G.headCellArray[i].firstEdge;
        while(p)
        {
            printf("->%3d", p->adjvertex);
            p=p->next;
        }
        printf("\n");
    }
}

void main()
{
    int i, *p, temp;
    Graph G;

    G=InitGraph();
    PrintGraph(G);

/*
    p=MakeIndegree(G);
    for(i=0;i<7;i++)
        printf("%4d", p[i]);
*/
/*
    temp=FindNewVertexOfIndegreeZero(p, 7);
    printf("%d\n", temp);
*/
    Topsort(G);    
    for(i=0;i<MAX_VERTEX_NUM;i++)
        printf("%4d\n", TopNum[i]);

}

