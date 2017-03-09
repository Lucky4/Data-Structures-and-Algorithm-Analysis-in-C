#include "targetver.h"
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


#define ElementType int


/*
优先队列数组实现
*/
typedef struct HeapStrcut	//堆结构
{
	int Capcity;
	int Size;
	ElementType *Elements;
}*PriorityQueue;


PriorityQueue Initialize(int MaxElements);	//创建初始化优先队列
void Insert(ElementType X, PriorityQueue H);//插入
ElementType DeleteMin(PriorityQueue H);		//删除最小节点
int IsEmpty(PriorityQueue H);				//判断优先队列是否为空
int IsFull(PriorityQueue H);				//判断优先队列是否已满