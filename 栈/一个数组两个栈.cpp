/**********************************************************************
用一个数组实现两个栈
**********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct StackRecord
{
	int capcity;
	int topOfStack1;		//自底向上的栈顶指针
	int topOfStack2;		//自顶向下的栈顶指针
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
判断栈bottom栈是否为空例程
*/
int is_bottom_empty(Stack S)
{
	return S->topOfStack1 == -1;
}

/*
判断栈top栈是否为空例程
*/
int is_top_empty(Stack S)
{
	return S->topOfStack2 == S->capcity;
}

/*
创建bottom空栈历程
*/
void make_bottom_empty(Stack S)
{
	S->topOfStack1 = -1;
}

/*
创建top空栈历程
*/
void make_top_empty(Stack S)
{
	S->topOfStack2 = S->capcity;
}

/*
判断栈满的历程
*/
int is_full(Stack S)
{
	return (S->topOfStack1 + 1) == S->topOfStack2;
}

/*
使用一个数组实现两个栈
只需设置两个栈顶指针
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
	make_bottom_empty(s);
	make_top_empty(s);

	return s;
}

/*
bottom栈进栈例程
*/
void push_bottom(int x, Stack S)
{
	if (is_full(S))
		printf("Full stack.\n");
	else
		S->array[++S->topOfStack1] = x;
}

/*
top栈进栈例程
*/
void push_top(int x, Stack S)
{
	if (is_full(S))
		printf("Full stack.\n");
	else
		S->array[--S->topOfStack2] = x;
}


/*
bottom栈返回栈顶例程
*/
int top_bottom(Stack S)
{
	if (!is_bottom_empty(S))
		return S->array[S->topOfStack1];
	printf("Empty stack.\n");

	return 0;
}

/*
top栈返回栈顶例程
*/
int top_top(Stack S)
{
	if (!is_top_empty(S))
		return S->array[S->topOfStack2];
	printf("Empty stack.\n");

	return 0;
}


/*
bottom栈出栈例程
*/
void pop_bottom(Stack S)
{
	if (is_bottom_empty(S))
		printf("Empty stack.\n");
	else
		S->topOfStack1--;
}

/*
top栈出栈例程
*/
void pop_top(Stack S)
{
	if (is_top_empty(S))
		printf("Empty stack.\n");
	else
		S->topOfStack2++;
}

/*
bottom栈给出元素并弹栈例程
*/
int b_top_and_pop(Stack S)
{
	if (!is_bottom_empty(S))
		return S->array[S->topOfStack1--];
	printf("Empty stack.\n");

	return 0;
}

/*
top栈给出元素并弹栈例程
*/
int t_top_and_pop(Stack S)
{
	if (!is_top_empty(S))
		return S->array[S->topOfStack1++];
	printf("Empty stack.\n");

	return 0;
}







int main()
{
	int capcity;
	int choose = 0;
	int value;
	Stack S;

	//初始化栈
	printf("请输入栈容量：\n");
	scanf("%d", &capcity);
	S = create_statck(capcity);

	while (1)
	{
		printf("请输入操作：\n");
		printf("1.bottom进栈\n");
		printf("2.bottom出栈\n");
		printf("3.top进栈\n");
		printf("4.top出栈\n");
		printf("q.退出\n");
		switch (scanf("%d", &choose))
		{
		case 1:
			printf("请输入bottom进栈元素：\n");
			scanf("%d", &value);
			push_bottom(value, S);
			break;

		case 2:
			printf("请输入bottom出栈元素：\n");
			pop_bottom(S);
			break;

		case 3:
			printf("请输入top进栈元素：\n");
			scanf("%d", &value);
			push_top(value, S);
			break;

		case 4:
			printf("请输入top出栈元素：\n");
			pop_top(S);
			break;

		default:
			int i;
			for (i = 0; i < S->capcity; i++)
			{
				printf("栈中元素为：%d\t", S->array[i]);
			}
			return 0;
		}
	}
}
