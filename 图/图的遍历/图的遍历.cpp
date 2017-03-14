#include "stdafx.h"


#define NUM 100 	//图中节点个数
int STATUS[NUM];	//保存被访问过节点信息

/*
创建图结构
*/
Graph CreateGraph(int Start, int End, Graph OriginG)
{
	int i;
	Graph G, tmp;

	//若图为空则创建图，否则令G指向原始的图
	if (NULL == OriginG)
	{
		//申请邻接表头节点存储空间
		G = (Graph)malloc(sizeof(struct Head));
		if (NULL == G)
		{
			printf("Out of space.\n");
			exit(-1);
		}
		G->pNext = NULL;

		//初始化邻接表头结点表
		for (i = 0; i < NUM; i++)
		{
			tmp = (Graph)malloc(sizeof(struct Head));
			if (NULL == tmp)
			{
				printf("Out of space.\n");
				exit(-1);
			}
			tmp->data = i;
			tmp->pAdj = NULL;
			tmp->pNext = G->pNext;
			G->pNext = tmp;
		}
	}
	else
		G = OriginG;

	//申请外链接节点存储空间
	PNODE newNode = (PNODE)malloc(sizeof(struct Node));
	if (NULL == newNode)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	else
	{
		//外链接接节点初始化
		newNode->vertex = End;
		newNode->pNext = NULL;
	}

	//通过图的弧信息为图初始化
	tmp = G->pNext;
	for (i = 0; i < NUM; i++)
	{
		if (tmp->data == Start)
		{
			newNode->pNext = tmp->pAdj;
			tmp->pAdj = newNode;
			newNode->vertex = End;
			break;
		}
		tmp = tmp->pNext;
	}

	return G;
}

/*
节点是否被访问过
*/
int has_visited(PNODE Child)
{
	if (Child == NULL)
		return 0;

	return STATUS[Child->vertex] == 1;
}

/*
寻找下一条弧起始点
*/
Graph next_vertex(Graph G, int info)
{
	Graph pStart = G->pNext;
	while (pStart->data != info)
		pStart = pStart->pNext;

	return pStart;
}

/*
图的深度优先遍历
*/
void DFS(Graph G, int Start)
{
	//图指针,遍历,查找图开始的节点并指向它
	Graph pTraverse = next_vertex(G, Start);

	//创建栈结构存储遍历过的节点
	PSTACK S = CreateStack();

	//将Start节点作为深度遍历森林的根，并标记为已遍历过
	Push(pTraverse->data, S);
	STATUS[pTraverse->data] = 1;
	printf("%d ", Top(S));

	//使用栈结构存储遍历过节点，模拟递归的的执行方式
	while (!IsStackEmpty(S))
	{
		if (pTraverse->pAdj != NULL)					//若邻接表头节点表的某个点有外链接表即该条弧起始点有终止点
		{
			//下一个要遍历的节点（即弧尾）
			PNODE pChild = pTraverse->pAdj;

			if (pChild == NULL)							//若要遍历的节点（即弧尾）是空，则让pTraverse指向空，if循环判断条件时便转向执行出栈操作
			{
				pTraverse->pAdj = NULL;
				continue;
			}

			if (has_visited(pChild))					//若要遍历的节点已经遍历过则转向遍历父节点的下一个儿子
			{
				//寻找下个未遍历过的节点
				while (has_visited(pChild))
				{
					pChild = pChild->pNext;
				}

				if (pChild == NULL)						//若下一个弧终点为空，则弹栈
				{
					Pop(S);
					if (IsStackEmpty(S))				//若栈为空意味着遍历结束，跳出循环
						break;

					//返回图的该节点的上一个节点的弧起始节点状态
					pTraverse = next_vertex(G, Top(S));
				}
				else 
				{	//若要遍历的节点未遍历过
					//输出节点信息
					printf("%d ", pChild->vertex);

					//将向下遍历到的节点信息入栈
					Push(pChild->vertex, S);
					STATUS[pChild->vertex] = 1;

					//寻找下一条弧的起始点
					pTraverse = next_vertex(G, pChild->vertex);
				}
			}
			else
			{	//若要遍历的节点未遍历过
				//输出节点信息
				printf("%d ", pChild->vertex);

				//将向下遍历到的节点信息入栈
				Push(pChild->vertex, S);
				STATUS[pChild->vertex] = 1;

				//寻找下一条弧的起始点
				pTraverse = next_vertex(G, pChild->vertex);
			}
		}
		else
		{	//若下一个弧终点为空，则弹栈，退回到当前探测节点的上一个节点
			//继续探测退回节点的下一个节点
			//若栈为空意味着遍历结束，跳出循环
			Pop(S);
			if (IsStackEmpty(S))
				break;

			//返回图的该节点的上一个节点的弧起始节点状态
			pTraverse = next_vertex(G, Top(S));
		}
	}
	printf("\n");
	return;
}

/*
图的广度优先遍历
*/
void BFS(Graph G, int Start)
{
	//图指针,遍历,查找图开始的节点并指向它
	Graph pTraverse = next_vertex(G, Start);

	//创建队列结构存储遍历过的节点
	PQUEUE Q = CreateQueue();

	//将Start节点作为深度遍历森林的根，并标记为已遍历过
	EnQueue(pTraverse->data, Q);
	STATUS[pTraverse->data] = 1;
	printf("%d ", Front(Q));

	//只要队列中有元素存在，就遍历其邻接节点
	while (!IsQueueEmpty(Q))
	{
		PNODE pChild = pTraverse->pAdj;

		while (pChild != NULL)
		{
			printf("%d ", pChild->vertex);
			EnQueue(pChild->vertex, Q);
			pChild = pChild->pNext;
		}
		DeQueue(Q);
		pTraverse = next_vertex(G, Front(Q));
	}

	printf("\n");
	return;
}
















int main()
{
	Graph G = NULL;
	int flag = 1, C, trav_begin;

	while (flag)
	{
		printf("-------------------------------请输入进行的操作-------------------------------\n");
		printf("|                                                                            |\n");
		printf("|                              1.创建图                                      |\n");
		printf("|                              2.DFS                                         |\n");
		printf("|                              3.BFS                                         |\n");
		printf("------------------------------------------------------------------------------\n");

		scanf("%d", &C);
		switch (C)
		{
		case 1:
			int start, end;
			printf("请输入弧的起始定点和终点\n");
			scanf("%d%d", &start, &end);
			G = CreateGraph(start, end, G);
			break;

		case 2:
			printf("请输入遍历起始节点\n");
			scanf("%d", &trav_begin);
			DFS(G, trav_begin);
			break;

		case 3:
			printf("请输入遍历起始节点\n");
			scanf("%d", &trav_begin);
			BFS(G, trav_begin);

		default:
			flag = 0;
			break;
		}
	}
    return 0;
}

