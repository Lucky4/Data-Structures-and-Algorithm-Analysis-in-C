/*
本程序参考了兰亭风雨大大的源代码和Hackbuteer1的CSDN专栏,在此特别感谢。
还有层次遍历未完成。
*/
#include "stdafx.h"


/*
清空栈
*/
void make_empty(PSTACK S)
{
	if (NULL == S)
	{
		printf("Must use create stack first.\n");
		exit(-1);
	}
	else
		while (!is_empty(S))
			pop(S);
}

/*
判断栈是否为空
*/
int is_empty(PSTACK S)
{
	return S->next == NULL;
}

/*
创建栈
*/
PSTACK create_stack()
{
	PSTACK S = (PSTACK)malloc(sizeof(struct TSNode));
	if (NULL == S)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	S->next = NULL;
	make_empty(S);
	return S;
}

/*
进栈
*/
void push(BTree val, PSTACK S)
{
	PNODE pNew = (PNODE)malloc(sizeof(struct TSNode));
	if (NULL == pNew)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	pNew->data = val;
	pNew->next = S->next;
	S->next = pNew;
	return ;
}

/*
返回栈顶元素
*/
BTree top(PSTACK S)
{
	if (!is_empty(S))
		return S->next->data;
	
	printf("Empty stack.\n");
	return NULL;
}

/*
出栈
*/
void pop(PSTACK S)
{
	if (is_empty(S))
	{
		printf("Empty stack.\n");
		exit(-1);
	}
	PNODE p = S->next;
	S->next = p->next;
	free(p);
	return;
}

/*
创建一棵二叉树,定义树的一种自然的方式是递归的方法,
每条边都将某个节点连接到它的父亲，出去根节点之外每个节点都有一个父亲。
*/
BTree create_tree()
{
	int val;
	scanf("%d", &val);

	//若输入树的值关键字为-1则返回NULL
	if (val == -1)
		return NULL;

	//创建树根并根据输入初始化关键字
	BTree root = (BTree)malloc(sizeof(struct BTNode));
	if (NULL == root)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	root->data = val;

	//递归创建一棵树
	printf("请输入%d的左孩子：", val);
	root->pLeft = create_tree();
	printf("请输入%d的右孩子：", val);
	root->pRight = create_tree();

	return root;
}

/*
二叉树的前序非递归遍历
思路是用栈保存左子树，出栈访问右子树，循环执行遍历左子树操作
遍历时最重要的一点就是判断是否为空
*/
void pre_nonrecursive(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//创建一个保存数关键字的栈

	while (T)	//从根节点开始遍历左子树直到空,全部压入栈中
	{
		push(T, S);
		printf("%d\t", T->data);
		T = T->pLeft;
	}

	while (!is_empty(S))
	{
		BTree temp = top(S)->pRight;	//栈顶元素右子树
		pop(S);							//弹出栈顶元素
		while (temp)	//栈顶元素存在右子树，则对右子树同样遍历到最左下方，不存在则返回上一层做同样操作
		{
			printf("%d\t", temp->data);
			push(temp, S);
			temp = temp->pLeft;
		}
	}
}

/*
二叉树的前序非递归遍历
思路是只要当前指针不为空或者栈不为空就执行循环遍历操作
*/
void pre_nonrecursive1(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//创建一个保存数关键字的栈
	BTree pCur = T;				//定义用来指向当前访问节点的指针

	//直到当前节点pCur为NULL且栈空时，循环结束
	while (pCur || !is_empty(S))
	{
		//从根节点开始，输出当前节点，并将其入栈，
		//同时置其左孩子为当前节点，直至其没有左孩子，直到前节点为NULL
		push(pCur, S);
		printf("%d\t", pCur->data);
		pCur = pCur->pLeft;
		//如果当前节点pCur为NULL且栈不空，则将栈顶节点出栈，
		//同时置其右孩子为当前节点,循环判断，直至pCur不为空
		while (!pCur && !is_empty(S))
		{
			pCur = top(S);
			pop(S);
			pCur = pCur->pRight;
		}
	}
}

/*
二叉树的前序非递归遍历2,后序遍历双栈法的前身
*/
void pre_nonrecursive2(BTree T)
{
	if (!T)
		return ;

	PSTACK S = create_stack();
	push(T, S);

	while (!is_empty(S))
	{
		BTree temp = top(S);
		printf("%d\t", temp->data);
		pop(S);
		if (temp->pRight)
			push(temp->pRight, S);
		if (temp->pLeft)
			push(temp->pLeft, S);
	}
}

/*
二叉树的中序非递归遍历
这种方法不好，要是用这种方法写后序遍历很麻烦，有可能写不出来
*/
void in_nonrecursive(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//创建一个保存数关键字的栈
	BTree pCur = T;				//定义用来指向当前访问节点的指针

	//直到当前节点pCur为NULL且栈空时，循环结束
	while (pCur || !is_empty(S))
	{
		if (pCur->pLeft)
		{
			//当前节点的左子树不为空，则将其入栈，并将当前指针指向左子树
			push(pCur, S);
			pCur = pCur->pLeft;
		}
		else
		{
			//如果pCur的左孩子为空，则输出pCur节点，并将其右孩子设为当前节点，看其是否为空
			printf("%d\t", pCur->data);
			pCur = pCur->pRight;
			//如果为空，且栈不空，则将栈顶节点出栈，并输出该节点，
			//同时将它的右孩子设为当前节点，继续判断，直到当前节点不为空
			while (!pCur && !is_empty(S))
			{
				pCur = top(S);
				printf("%d\t", pCur->data);
				pop(S);
				pCur = pCur->pRight;
			}
		}
	}
}

/*
二叉树的中序非递归遍历1
*/
void in_nonrecursive1(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//创建一个保存数关键字的栈
	BTree pCur = T;				//定义用来指向当前访问节点的指针

	while (pCur != NULL || !is_empty(S))
	{
		while (pCur != NULL)
		{
			push(pCur, S);
			pCur = pCur->pLeft;
		}//while  
		if (!is_empty(S))
		{
			pCur = top(S);
			pop(S);
			printf("%d\t", pCur->data);
			pCur = pCur->pRight;
		}
	}
}

/*
叉树的后序非递归遍历
*/
void post_nonrecursive(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//创建一个保存数关键字的栈
	BTree pCur = T;				//定义用来指向当前访问节点的指针
	BTree pPre = NULL;			//指向前一个被访问的节点

	while (pCur != NULL || !is_empty(S))
	{
		while (pCur != NULL)	// 一直向左走直到为空 
		{
			push(pCur, S);
			pCur = pCur->pLeft;
		}
		pCur = top(S);
		// 当前节点的右孩子如果为空或者已经被访问，则访问当前节点   
		if (pCur->pRight == NULL || pCur->pRight == pPre)
		{
			printf("%d\t", pCur->data);
			pPre = pCur;
			pop(S);
			pCur = NULL;
		}
		else
			pCur = pCur->pRight; // 否则访问右孩子
	}
}

/*
叉树的后序非递归遍历,双栈法
*/
void post_nonrecursive1(BTree T)
{
	PSTACK S1= create_stack();
	PSTACK S2 = create_stack();
	BTree pCur;					// 指向当前要检查的节点
	push(T, S1);
	while (!is_empty(S1))		// 栈空时结束
	{
		pCur = top(S1);
		pop(S1);
		push(pCur, S2);
		if (pCur->pLeft)
			push(pCur->pLeft, S1);
		if (pCur->pRight)
			push(pCur->pRight, S1);
	}
	while (!is_empty(S2))
	{
		printf("%d\t", top(S2)->data);
		pop(S2);
	}
}

/*
二叉树深度
*/
int depth(BTree T)
{
	if (!T)
		return 0;

	int d1 = 1 + depth(T->pLeft);
	int d2 = 1 + depth(T->pRight);

	if (d1 > d2)
		return d1;
	return d2;
}








int main()
{
	printf("创建一棵二叉树，输入-1为空\n");
	BTree T = create_tree();
	int flag = 1, k;
	printf("                     本程序实现二叉树的基本操作。\n");
	while (flag)
	{
		printf("\n");
		printf("|--------------------------------------------------------------|\n");
		printf("|                    二叉树的基本操作如下:                     |\n");
		printf("|                        1.非递归先序遍历                      |\n");
		printf("|                        2.非递归中序遍历                      |\n");
		printf("|                        3.非递归后序遍历                      |\n");
		printf("|                        4.二叉树的深度                        |\n");
		printf("|                        5.退出程序                            |\n");
		printf("|--------------------------------------------------------------|\n");
		printf("                        请选择功能：");
		scanf("%d", &k);
		switch (k)
		{
		case 1:
			if (T)
			{
				printf("非递归先序遍历二叉树的结果为：");
				pre_nonrecursive(T);
				printf("\n");
			}
			else
				printf("          二叉树为空！\n");
			break;
		case 2:
			if (T)
			{
				printf("非递归中序遍历二叉树的结果为：");
				in_nonrecursive(T);
				printf("\n");
			}
			else
				printf("          二叉树为空！\n");
			break;
		case 3:
			if (T)
			{
				printf("非递归后序遍历二叉树的结果为：");
				post_nonrecursive(T);
				printf("\n");
			}
			else
				printf("          二叉树为空！\n");
			break;
		case 4:
			if (T)
			{
				printf("二叉树深度：");
				printf("depth is:%d", depth(T));
				printf("\n");
			}
			else
				printf("          二叉树为空！\n");
			break;
		default:
			flag = 0;
			printf("程序运行结束，按任意键退出！\n");
		}
	}
    return 0;
}

