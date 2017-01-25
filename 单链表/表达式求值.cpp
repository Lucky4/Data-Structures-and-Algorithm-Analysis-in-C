/**********************************************************************
表达式求值,根据输入的中缀表达式（标准）转化为后缀表达式进行求值
思路不进行赘述，源于《数据结构与算法分析—C语言描述》54页
**********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char oprArray[6] = { '+', '-', '*', '/', '(', ')' };	//操作符数组


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
判断字符栈是否为空
*/
int is_cstack_empty(SC S)
{
	return S->next == NULL;
}

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
char c_top_pop(SC S)
{
	//判断栈是否为空
	if (NULL == S->next)
		printf("When top and pop the stack is empry.\n");

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
float f_top_pop(SF S)
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
弹栈操作
*/
void c_pop(SC S)
{
	//判断栈是否为空
	if (NULL == S->next)
		printf("When pop, the stack is empry.\n");

	//返回栈顶元素，释放空间
	SC temp = S->next;
	S->next = temp->next;
	free(temp);

	return;
}

/*
返回栈顶元素
*/
char c_top(SC S)
{
	if (!is_cstack_empty(S))
		return S->next->c;
	else
		return '0';
}

/*
判断字符栈中是否有某个元素
*/
int opr_in_cstack(char c, SC S)
{
	SC p = S->next;
	while (NULL != p)
	{
		if (c == p->c)
			return 1;
		p = p->next;
	}

	return 0;
}

/*
判断是操作数还是操作符
*/
int is_ptr(char element)
{
	int i = 0;
	while (oprArray[i])
	{
		if (element == oprArray[i])
			return 1;
		i++;
	}
	return 0;
}

/*
两个操作数进行运算
*/
float operate(float a, char opr, float b)
{
	float result;
	switch(opr)
	{
		case '+': return result = a + b;
		case '-': return result = a - b;
		case '*': return result = a * b;
		case '/': return result = b / a;
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
返回后缀表达式长度
*/
int postfix_len(char *expression)
{	//拷贝字符串
	//防止postfix函数调用时与splite函数发生冲突
	//导致程序结果错误
	char rl[100];
	strcpy(rl, expression);

	//分割字符串
	//每次分割一个count加一
	char *token = strtok(rl, ",");
	int count = 0;
	while (NULL != token)
	{
		count++;
		token = strtok(NULL, ",");
	}

	return count;
}

/*
返回表达式长度
*/
int exp_len(char *expression)
{
	return strlen(expression);
}

/*
判断两个操作符优先级返回优先级大的操作符,返回e表示相等
之后看到哈希的时候是否可以用哈希的方式查找比较优先级
*/
char prio_operator(char opr1, char opr2)
{
	//定义两个操作符的优先级
	int level1, level2;

	//第一个操作符优先级
	if (opr1 == '+' || opr1 == '-')
		level1 = 1;
	if (opr1 == '*' || opr1 == '/')
		level1 = 2;
	if (opr1 == '(' || opr1 == ')')
		level1 = 3;
	//第二个操作符优先级
	if (opr2 == '+' || opr2 == '-')
		level2 = 1;
	if (opr2 == '*' || opr2 == '/')
		level2 = 2;
	if (opr2 == '(' || opr2 == ')')
		level2 = 3;

	//比较优先级
	if (level1 < level2)
		return opr2;
	if(level1 > level2)
		return opr1;
	if(level1 == level2)	//equal相等
		return 'e';
}

/*
计算后缀表达式
*/
float postfix(char *expression)
{
	float a, b;		//操作数啊a，b
	float tpResult;		//临时计算结果
	char opr;		//操作符

	int count = postfix_len(expression);	//获得表达式字符数组长度
	char **elements = splite(expression);	//二级指针指向表达式字符数组

	SF fStack = create_fstack();		//初始化操作数栈

	//后缀表达式运算
	int i;
	for (i = 0; i < count; i++)
	{
		if (!is_ptr(**&elements[i]))	//如果是操作数则进栈
		{
			printf("%d\n", atoi(*&elements[i]));
			f_push(float(atoi(*&elements[i])), fStack);
		}
		else		//操作数出栈，运算后进栈
		{
			a = f_top_pop(fStack);
			b = f_top_pop(fStack);
			opr = **&elements[i];
			tpResult = operate(a, opr, b);
			f_push(tpResult, fStack);
		}
	}

	float x = f_top_pop(fStack);
	return x;
}

/*
表达式求值
利用2个栈结构求得后缀表达式，通过后缀表达式函数求结果
*/
float evalute_expression(char *expression)
{
	char prioOpr;					//优先级高的操作符
	char postExpression[100];			//后缀表达式
	char *postExp = postExpression;			//后缀表达式指针

	int count = exp_len(expression);		//获得表达式字符数组长度

	SC cStack = create_cstack();			//初始化操作符栈

	//表达式运算
	int i;
	for (i = 0; i < count; i++)			//循环遍历表达式每个字符
	{
		if (!is_ptr(expression[i]))		//如果是操作数则将其保存至后缀表达式
		{
			*postExp++ = expression[i];
			if(is_ptr(expression[i+1]) || expression[i + 1] == '\0')
				*postExp++ = ',';
			continue;
		}

		if (!is_cstack_empty(cStack))		//如果操作符栈不为空并且是操作符
		{
			char popOpr;	//从栈顶弹出内容

			//比较栈顶操作符和当前操作符的优先级
			prioOpr = prio_operator(expression[i], c_top(cStack));
			if (prioOpr == 'e')		//如果当前操作符优先级与栈顶操作符相等则入栈
			{
				c_push(expression[i], cStack);
				continue;
			}

			if (prioOpr == expression[i] && ')' != expression[i])		//如果当前操作符优先级高则进栈
			{
				c_push(expression[i], cStack);
				continue;
			}

			if (prioOpr == expression[i] && ')' == expression[i])		//如果当前操作符优先级高且为‘）’则弹栈至‘（’内容到后缀表达式
			{
				while ('(' != c_top(cStack))
				{
					popOpr = c_top_pop(cStack);
					*postExp++ = popOpr;
					*postExp++ = ',';
				}
				//将‘（’弹出
				c_pop(cStack);
				continue;
			}

			if (prioOpr == c_top(cStack) && opr_in_cstack('(', cStack))	//如果当前操作符优先级低且栈之前有‘（’符号，则继续入栈
			{
				c_push(expression[i], cStack);
				continue;
			}

			if (prioOpr == c_top(cStack))	//如果当前操作符优先级低则将弹栈操做符至后缀表达式,直至当前操作符优先级大于等于栈顶
			{
				while ('0' != c_top(cStack) && c_top(cStack) == prio_operator(expression[i], c_top(cStack)))//有问题!!!!!!!!!
				{
					popOpr = c_top_pop(cStack);
					*postExp++ = popOpr;
					*postExp++ = ',';
				}
				c_push(expression[i], cStack);
				continue;
			}
		}
		else	//如果操作符栈为空，直接进栈
		{
			c_push(expression[i], cStack);
			continue;
		}
	}

	//如果栈不为空将栈中字符存入postExp中
	//设置字符串结尾
	while (!is_cstack_empty(cStack))
	{
		*postExp++ = c_top_pop(cStack);
		*postExp++ = ',';
	}
	*postExp++ = '\0';

	printf("postfix is:%s\n", postExpression);
	float result = postfix(postExpression);

	return result;
}







void main()
{
	char exp[100];
	float result;

	//后缀表达式
	//printf("请输入连续的不含有括号的后缀表达式(操作数之间逗号分隔)：\n");
	//scanf("%s", &exp);
	//printf("你输入的表达式为：%s\n", exp);
	//result = postfix(exp);
	//printf("后缀表达式运算结果为%f\n", result);
	
	//中缀（标准）表达式
	printf("请输入要计算的表达式\n");
	scanf("%s", &exp);
	printf("你输入的表达式为：%s\n", exp);
	result = evalute_expression(exp);
	printf("后缀表达式运算结果为%f\n", result);

	//测试
	//printf("请输入要计算的表达式\n");
	//scanf("%s", &exp);
	//printf("你输入的表达式为：%s\n", exp);
	//evalute_expression(exp);
}
