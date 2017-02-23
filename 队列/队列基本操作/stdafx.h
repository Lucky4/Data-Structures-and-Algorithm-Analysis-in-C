#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>


typedef int ElementType;


/*
数组实现队列结构
*/
typedef struct QueueRecord
{
	int Capcity;
	int Size;
	int Front;
	int Rear;
	ElementType *Array;
}*Queue;


int IsEmpty(Queue Q);					//判断队列是否为空
int IsFull(Queue Q);					//判断队列是否已满
Queue CreateQueue(int MaxElements);		//创建队列
void DisposeQueue(Queue Q);				//销毁队列
void MakeEmpty(Queue Q);				//清空队列
void Enqueue(ElementType X, Queue Q);	//入队
void Dequeue(Queue Q);					//出队
ElementType Front(Queue Q);				//返回队头元素
ElementType FrontAndDequeue(Queue Q);	//返回队头元素并出队