/**********************************************************************
后缀表达式求值
**********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char oprArray[10] = { '+', '-', '*', '/', '(', ')' };	//操作符数组


typedef struct StackChar
{
	char c;
	struct StackChar *next;
}*SC;			//操作符栈指针变量

typedef struct StackFloat
{
	float f;
	struct StackFloat *next;
}*SF;			//操作数栈指针变量


/*
创建操作符栈
*/
SC create_cstack()
{
	//申请栈空间
	SC S = (SC)malloc(sizeof(struct StackChar));
	if (NULL == S)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	S->next = NULL;

	return S;
}

/*
创建操作数栈
*/
SF create_fstack()
{
	//申请栈空间
	SF S = (SF)malloc(sizeof(struct StackFloat));
	if (NULL == S)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	S->next = NULL;

	return S;
}

/*
操作符进栈
*/
void c_push(char c, SC S)
{
	//申请进栈元素空间初始化
	//opr代表操作数、符
	SC opr = (SC)malloc(sizeof(struct StackChar));
	if (NULL == opr)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	opr->c = c;
	opr->next = S->next;
	S->next = opr;
}

/*
操作符进栈
*/
void f_push(float f, SF S)
{
	//申请进栈元素空间初始化
	//opr代表操作数、符
	SF opr = (SF)malloc(sizeof(struct StackFloat));
	if (NULL == opr)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	opr->f = f;
	opr->next = S->next;
	S->next = opr;
}

/*
弹栈并返回栈顶元素
*/
char c_pop(SC S)
{
	//判断栈是否为空
	if (NULL == S->next)
		printf("The stack is empry.\n");

	//返回栈顶元素，释放空间
	SC temp = S->next;
	char c = temp->c;
	S->next = temp->next;
	free(temp);

	return c;
}

/*
弹栈并返回栈顶元素
*/
float f_pop(SF S)
{
	//判断栈是否为空
	if (NULL == S->next)
		printf("The stack is empry.\n");

	//返回栈顶元素，释放空间
	SF temp = S->next;
	float f = temp->f;
	S->next = temp->next;
	free(temp);

	return f;
}

/*
判断是操作数还是操作符
*/
int is_ptr(char element)
{
	int i;
	for (i = 0; i < 6; i++)
		if (element == oprArray[i])
			return 1;
	return 0;
}

//两个操作数进行运算
float operate(float a, char opr, float b)
{
	float result;
	switch(opr)
	{
		case '+': return result = a + b;
		case '-': return result = a - b;
		case '*': return result = a * b;
		case '/': return result = a / b;
		default: return 0;
	}
}

/*
分割字符串,返回指针数组
*/
char ** splite(char *expression)
{
	char *token = strtok(expression, ",");
	char static *arrExpression[100];

	int i = 0;
	while (NULL != token)
	{
		arrExpression[i] = token;
		//printf("splite is %s\n", arrExpression[i]);
		token = strtok(NULL, ",");
		i++;
	}

	return arrExpression;
}

/*
返回表达式长度
*/
int exp_len(char *expression)
{
	//拷贝字符串
	//防止postfix函数调用时与splite函数发生冲突
	//导致程序结果错误
	char rl[100];
	strcpy(rl, expression);
	
	//分割字符串
	//每次分割一个count加一
	char *token = strtok(rl, ",");
	int count=0;
	while (NULL != token)
	{
		count++;
		token = strtok(NULL, ",");
	}

	return count;
}

/*
计算后缀表达式
*/
float postfix(char *expression)
{
	float a, b;				//操作数啊a，b以
	float tpResult;				//临时计算结果
	char opr;				//操作符
	int count=exp_len(expression);		//获得表达式字符数组长度
	char **elements = splite(expression);	//二级指针指向表达式字符数组
	SF fStack = create_fstack();		//初始化操作数栈

	//后缀表达式运算
	int i;
	for (i = 0; i < count; i++)
	{
		//printf("结果是%s\n", *&elements[3]);
		if (!is_ptr(**&elements[i]))				//如果是操作数则进栈
		{
			printf("%d\n", atoi(*&elements[i]));
			f_push(atoi(*&elements[i]), fStack);
		}
		else							//操作数出栈，运算后进栈
		{
			a = f_pop(fStack);
			b = f_pop(fStack);
			opr = **&elements[i];
			tpResult = operate(a, opr, b);
			f_push(tpResult, fStack);
		}
	}

	float x = f_pop(fStack);
	return x;
}

void main()
{
	char exp[100];
	float result;

	printf("请输入连续的不含有括号的后缀表达式(操作数之间逗号分隔)：\n");
	scanf("%s", &exp);
	printf("你输入的表达式为：%s\n", exp);
	result = postfix(exp);
	printf("后缀表达式运算结果为%f\n", result);
}
