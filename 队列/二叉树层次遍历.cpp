#include "stdafx.h"

/*
创建一棵二叉树,定义树的一种自然的方式是递归的方法,
每条边都将某个节点连接到它的父亲，除去根节点之外每个节点都有一个父亲。
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
	root->Left = create_tree();
	printf("请输入%d的右孩子：", val);
	root->Right = create_tree();

	return root;
}

/*
二叉树的层次遍历
由于我写的队列使用数组实现front初始化为0,rear初始化为1，当入队后出队时就会发生地址取不到值得问题,
所以，这个层次遍历采用自己实现的队列，要是想使用标准的队列ADT的话最好使用链表实现队列。
*/
void levelTraverse(BTree T)
{
	if (NULL == T)
		return;
	
	BTNode *Q[10];
	int front, rear;
	front = rear = 0;
	Q[rear++] = T;
	while (front != rear)
	{
		printf("%d ", Q[front]->data);
		if (NULL != Q[front]->Left)
		{
			Q[rear] = Q[front]->Left;
			rear++;
		}
		if (NULL != Q[front]->Right)
		{
			Q[rear] = Q[front]->Right;
			rear++;
		}
		front++;
		//printf("\n");
	}
}

/*
二叉树的层次遍历（书上的递归并不好用）
*/
//int levelTraverse(BTree T, int level)
//{
//	if (!T || level < 0)
//		return 0;
//	if (level == 0)
//	{
//		printf("%d", T->data);
//		return 1;
//	}
//	//printf("%d", T->data);
//	return levelTraverse(T->Left, level - 1) + levelTraverse(T->Right, level - 1);
//}










int main()
{
	BTree T;

	printf("创建树，请输入树的节点信息，-1代表空\n");
	T = create_tree();
	levelTraverse(T);
	
    return 0;
}

