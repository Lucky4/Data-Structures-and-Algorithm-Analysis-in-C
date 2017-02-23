#include "stdafx.h"

/*
判断队列是否为空
*/
int IsEmpty(Queue Q)
{
	return Q->Size == 0;
}

/*
判断队列是否已满
*/
int IsFull(Queue Q)
{
	return Q->Size == Q->Capcity;
}

/*
创建队列
*/
Queue CreateQueue(int MaxElements)
{
	//申请队列存储结构空间
	Queue Q = (Queue)malloc(sizeof(struct QueueRecord));
	if (NULL == Q)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	//申请队列的数组存储结构空间
	Q->Array = (int *)malloc(MaxElements*sizeof(int));
	if (NULL == Q->Array)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	//初始化
	MakeEmpty(Q);
	Q->Capcity = MaxElements;
	return Q;
}

/*
销毁队列
*/
void DisposeQueue(Queue Q)
{
	free(Q->Array);
	free(Q);
}

/*
清空队列
*/
void MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 0;
	Q->Rear = 1;
}

/*
入队
*/
void Enqueue(ElementType X, Queue Q)
{
	if (IsFull(Q))
	{
		printf("The queue is full.\n");
		exit(-1);
	}
	else
	{
		Q->Size++;
		if (Q->Rear == Q->Capcity - 1)
			Q->Rear = 0;
		else
			Q->Rear++;
		Q->Array[Q->Rear] = X;
	}
}

/*
出队
*/
void Dequeue(Queue Q)
{
	if (IsEmpty(Q))
	{
		printf("The queue is empty.\n");
		exit(-1);
	}
	else
	{
		Q->Size--;
		if (Q->Front == Q->Capcity - 1)
			Q->Front = 0;
		else
			Q->Front++;
	}
}

/*
返回队头元素
*/
ElementType Front(Queue Q)
{
	if (!IsEmpty(Q))
		return Q->Array[Q->Front];
	else
		printf("When front the Queue, the queue is empty.\n");
	return -1;
}

/*
返回队头元素并出队
*/
ElementType FrontAndDequeue(Queue Q)
{
	ElementType X;

	if (IsEmpty(Q))
	{
		printf("The queue is empty.\n");
		exit(-1);
	}
	else
	{
		Q->Size--;
		if (Q->Front == Q->Capcity - 1)
			Q->Front = 0;
		else
		{
			X = Q->Array[Q->Front];
			Q->Front++;
		}
	}

	return X;
}

//展示队列元素
void show(Queue Q)
{
	int i;
	if (Q->Front <= Q->Rear)
	{
		printf("The queue elements is:\n");
		for (i = Q->Front; i <= Q->Rear; i++)
			if(Q->Array[i] > 0)
				printf("%d\t", Q->Array[i]);
		printf("\n");
	}
	else
	{
		printf("The queue elements is:\n");
		for (i = Q->Front; i < Q->Capcity; i++)
			if (Q->Array[i] > 0)
				printf("%d\t", Q->Array[i]);
		for (i = 0; i <= Q->Rear; i++)
			if (Q->Array[i] > 0)
				printf("%d\t", Q->Array[i]);
		printf("\n");
	}
}









int main()
{
	Queue Q = NULL;
	int flag = 1, c, capcity, element;

	while (flag)
	{
		if (Q == NULL)
			printf("The queue basic operate has been here, please input the choice.\n");

		printf("|--------------------------Choices------------------------------|\n");
		printf("|                    1.Create Queue.                            |\n");
		printf("|                    2.Enqueue.                                 |\n");
		printf("|                    3.Deueue.                                  |\n");
		printf("|                    4.Front.                                   |\n");
		printf("|                    5.Front And Dequeue.                       |\n");
		printf("|                    6.Dispose Queue.                           |\n");
		printf("|                    7.exit.                                    |\n");
		printf("|---------------------------------------------------------------|\n");

		printf("Please input the choice:\n");
		scanf("%d", &c);
		switch (c)
		{
		case 1:
			 printf("Please input the capcity.\n");
			 scanf("%d", &capcity);

			 Q = CreateQueue(capcity);
			 printf("Create queue success.\n");
			 break;

		case 2:
			printf("Please input the enqueue element.\n");
			scanf("%d", &element);

			Enqueue(element, Q);
			show(Q);
			break;

		case 3:
			Dequeue(Q);
			show(Q);
			break;

		case 4:
			printf("The front element is: %d\n", Front(Q));
			break;

		case 5:
			printf("Before dequeue element is: %d\n", FrontAndDequeue(Q));
			break;

		case 6:
			DisposeQueue(Q);
			break;

		default:
			flag = 0;
			break;
		}
	}
    return 0;
}

