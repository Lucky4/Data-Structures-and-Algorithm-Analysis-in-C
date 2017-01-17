/**********************************************************************
栈基本操作
用链表实现的栈结构的缺点是总是需要动态的分配资源，如果想解决这个问题可以
用另一个栈结构存储被删除的数据，而使用数组实现则效率更高一些，唯一的不足
就是就是需要提前的申请空间大小,这里只是实现了一些栈简答操作。
**********************************************************************/

#include "stdafx.h"
#include <stdint.h>
#include <stdlib.h>


typedef struct StackRecord
{
	int capcity;
	int topOfStack;
	int *array;
}*Stack;	//栈指针变量



/*
释放栈例程
*/
void dispose_stack(Stack S)
{
	if (NULL != S)
	{
		free(S->array);
		free(S);
	}
}

/*
判断栈是否为空例程
*/
int is_empty(Stack S)
{
	return S->topOfStack == -1;
}

/*
创建一个空栈历程
*/
void make_empty(Stack S)
{
	S->topOfStack = -1;
}

/*
判断栈满的历程
*/
int is_full(Stack S)
{
	return S->topOfStack == S->capcity - 1;
}

/*
创建栈例程
*/
Stack create_statck(int maxElements)
{
	Stack s;

	//申请栈空间
	s = (Stack)malloc(sizeof(struct StackRecord));
	if (NULL == s)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	//申请栈数组空间,栈初始化
	s->array = (int*)malloc(sizeof(int) * maxElements);
	if (NULL == s->array)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	s->capcity = maxElements;
	make_empty(s);

	return s;
}

/*
进栈历程
*/
void push(int x, Stack S)
{
	if (is_full(S))
		printf("Full stack.\n");
	else
		S->array[++S->topOfStack] = x;
}

/*
返回栈顶例程
*/
int top(Stack S)
{
	if (!is_empty(S))
		return S->array[S->topOfStack];
	printf("Empty stack.\n");

	return 0;
}

/*
出栈例程
*/
void pop(Stack S)
{
	if (is_empty(S))
		printf("Empty stack.\n");
	else
		S->topOfStack--;
}

/*
给出元素并弹栈例程
*/
int top_and_pop(Stack S)
{
	if (!is_empty(S))
		return S->array[S->topOfStack--];
	printf("Empty stack.\n");

	return 0;
}
