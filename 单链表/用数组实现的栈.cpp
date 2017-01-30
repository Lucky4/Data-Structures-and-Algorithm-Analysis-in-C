/**********************************************************************
栈基本操作
用链表实现的栈结构的缺点是总是需要动态的分配资源，如果想解决这个问题可以
用另一个栈结构存储被删除的数据，而使用数组实现则效率更高一些，唯一的不足
就是就是需要提前的申请空间大小,这里只是实现了一些栈简答操作。
增加了find_min操作。
**********************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct StackRecord
{
	int capcity;
	int topOfStack;
	int *array;
}*Stack;	//栈指针变量


void dispose_stack(Stack S);
int is_empty(Stack S);
void make_empty(Stack S);
int is_full(Stack S);
Stack create_statck(int maxElements);
Stack create_mstatck(int maxElements);
void push(int x, Stack S, Stack M);
int top(Stack S);
void pop(Stack S, Stack M);
int top_and_pop(Stack S, Stack M);
int find_min(Stack M);


void main()
{
	Stack S = create_statck(5);
	Stack M = create_mstatck(1);

	push(10, S, M);
	push(3, S, M);
	printf("min is:%d\n", find_min(M));
	pop(S, M);
	printf("min is:%d\n", find_min(M));
}


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
创建最小值栈例程
*/
Stack create_mstatck(int maxElements)
{
	Stack m;

	//申请栈空间
	m = (Stack)malloc(sizeof(struct StackRecord));
	if (NULL == m)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	//申请栈数组空间,栈初始化
	m->array = (int*)malloc(sizeof(int) * maxElements);
	if (NULL == m->array)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	m->capcity = maxElements;
	make_empty(m);

	return m;
}

/*
进栈历程
*/
void push(int x, Stack S, Stack M)
{
	if (is_full(S))
	{
		printf("Full stack.\n");
	}
	else
	{	//如果当前进栈值比M的栈顶值小替换
		if (!is_empty(M))
		{
			if (x < top(M))
				M->array[M->topOfStack] = x;
		}
		else
		{
			M->array[++M->topOfStack] = x;
		}

		S->array[++S->topOfStack] = x;
	}
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
void pop(Stack S, Stack M)
{
	int i;

	if (is_empty(S))
	{
		printf("Empty stack.\n");
	}
	else
	{	//如果要弹栈的元素是最小值
		//最小值栈弹栈,S弹栈,当S栈不为空时找出最小值进入最小值栈
		if (top(M) == top(S))
		{
			M->topOfStack--;
			S->topOfStack--;
		}
		if (!is_empty(S))
		{
			int min = S->array[0];
			for (i = 0; i <= S->topOfStack; i++)
			{
				if (S->array[i] < min)
					min = S->array[i];
			}

			M->array[++M->topOfStack] = min;
		}
	}
}

/*
给出元素并弹栈例程
*/
int top_and_pop(Stack S, Stack M)
{
	int i, topValue;

	if (!is_empty(S))
	{	
		if (top(M) == top(S))
		{
			M->topOfStack--;
			topValue = S->array[S->topOfStack--];
		}
		if (!is_empty(S))
		{
			int min = S->array[0];
			for (i = 0; i <= S->topOfStack; i++)
			{
				if (S->array[i] < min)
					min = S->array[i];
			}
			M->array[M->topOfStack] = min;
		}

		return topValue;
	}
	printf("Empty stack.\n");

	return 0;
}

/*
找出栈中最小元素
*/
int find_min(Stack M)
{
	return top(M);
}