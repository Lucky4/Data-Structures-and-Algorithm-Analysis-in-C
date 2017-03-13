#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


/*
图的邻接表存储结构
在邻接表中用一个单链表存储每个节点作为头结点，
每个头结点外链接一个链表存储图中每条边的终止节点。
*/
typedef struct Node
{	//链表结构存储弧所指向的节点
	int vertex;		//有向图中表示一条边即弧所指向的点信息
	struct Node *pNext;	//依附于该节点的下一个节点
}NODE, *PNODE;
typedef struct Head
{	//链表结构存储弧的起始点
	int data;		//弧起始点信息
	PNODE pAdj;		//弧尾节点信息
	struct Head *pNext;	//依附于该节点的下一个节点
}*Graph;


//创建图结构
Graph CreateGraph(int, int, Graph);

//图的深度优先遍历
void DFS(Graph);

//图的广度优先遍历
void BFS(Graph);


/*
栈结构声明
*/
typedef struct SNode
{	//栈节点保存节点信息和下一个节点的地址
	int data;
	struct SNode *pNext;
}SNODE, *PSNODE;
typedef struct Stack
{	//栈结构，保存栈顶指针
	PSNODE TopOfStack;
}STACK, *PSTACK;


//创建栈结构
PSTACK CreateStack();

//判断栈是否为空
int IsStackEmpty(PSTACK);

//入栈
void Push(int, PSTACK);

//出栈
void Pop(PSTACK);

//返回栈顶元素
int Top(PSTACK);


/*
队列结构
*/
typedef struct QNode
{	//队列节点保存节点信息和下一个节点的地址
	int data;
	struct QNode *pNext;
}QNODE, *PQNODE;
typedef struct Queue
{	//队列结构，保存队头指针和队尾指针
	PQNODE Front;
	PQNODE Rear;
}QUEUE, *PQUEUE;


//创建队列
PQUEUE CreateQueue();

//判断队列是否为空
int IsQueueEmpty(PQUEUE);

//入队
void EnQueue(int, PQUEUE);

//出队
void DeQueue(PQUEUE);

//返回栈顶元素
int Front(PQUEUE);
