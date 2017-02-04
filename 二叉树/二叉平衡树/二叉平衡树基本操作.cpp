#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


//二叉平衡树结构声明
typedef struct AvlNode
{
	int element;
	struct AvlNode *left;
	struct AvlNode *right;
	int height;
}*Position, *AvlTree;


//基本函数例程
AvlTree MakeEmpty(AvlTree T);
Position find(int x, AvlTree T);
Position find_min(AvlTree T);
Position find_max(AvlTree T);
AvlTree insert(int x, AvlTree T);
AvlTree delete_avl(int x, AvlTree T);


/*
返回二叉平衡树节点平衡因子高度
*/
static int height(Position P)
{
	if (NULL == P)
		return -1;
	else
		return P->height;
}

/*
返回最大值函数
*/
int max(int h1, int h2)
{
	if (h1 > h2)
		return h1;
	return h2;
}

/*
创建一颗空树
使用递归的方式由下到上将树中的每一个点释放空间，
返回NULL。可以初始化一个单节点，这里使用递归更遵循树的定义。
*/
AvlTree make_empty(AvlTree T)
{
	if (NULL != T)
	{
		make_empty(T->left);
		make_empty(T->right);
		free(T);
	}
	return NULL;
}

/*
二叉平衡树的find操作
使用递归的方式查找元素x，若树T为空，则返回NULL，
若元素x比当前元素小，则递归向该元素节点的左子树查找，
若元素x比当前元素大，则递归向该元素节点的右子树查找，
最后返回查找到的元素x。
*/
Position find(int x, AvlTree T)
{
	if (NULL == T)
		return NULL;
	if (x < T->element)
		return find(x, T->left);
	else if (x > T->element)
		return find(x, T->right);
	else
		return T;
}

/*
二叉平衡树的find_min操作
因为二叉排序树是有序的，所以只需要递归的查找左子树，
如果树为空，返回NULL，如果树根不为空，根的左子树为空，返回根T，
否则递归的在根的左子树中查找，返回递归到最后的根元素。
*/
Position find_min(AvlTree T)
{
	if (NULL == T)
		return NULL;
	if (NULL == T->left)
		return T;
	else
		return find_min(T->left);
}

/*
二叉平衡树的find_max操作，
使用非递归的方式进行查找。
*/
Position find_max(AvlTree T)
{
	if (NULL != T)
	{
		while (NULL != T->right)
			T = T->right;
	}

	return T;
}

/*
单旋转，根为K2，K2有一个左孩子K1，K2和其K1进行旋转，
旋转后K1变为K2的根节点，K2变为K1的右孩子，K1的右孩子变为K2的左孩子，
更新K2和K1的高度，返回新的根节点。
*/
static Position single_rotate_withleft(Position K2)
{
	//单旋转的根
	Position K1;
	K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(height(K2->left), height(K2->right)) + 1;
	K1->height = max(height(K1->left), height(K1->right)) + 1;
	return K1;
}

/*
单旋转，根为K1，K1有一个右孩子K2，K1和K2进行旋转，
旋转后K2变为K1的根节点，K1变为K2的左孩子，K2的左孩子变为K1的右孩子，
更新K1和K2的高度，返回新的根节点。
*/
static Position single_rotate_withright(Position K1)
{
	//单旋转的根
	Position K2;
	K2 = K1->right;
	K1->right = K2->left;
	K2->left = K1;
	K1->height = max(height(K1->left), height(K1->right)) + 1;
	K2->height = max(height(K2->left), height(K2->right)) + 1;
	return K2;
}

/*
双旋转，根为K3，K3有一个左孩子K1，K1有一个右孩子K2，
旋转过程为先K1和K2进行以K2为根的单旋转，令K3左孩子指针指向旋转后的K2，
然后K3和K2在进行一次以K2为根的单旋转，返回K2。
*/
static Position double_rotate_withleft(Position K3)
{
	K3->left = single_rotate_withright(K3->left);
	return single_rotate_withleft(K3);
}

/*
双旋转，根为K3，K3有一个右孩子K1，K1有一个左孩子K2，
旋转过程为先K1和K2进行以K2为根的单旋转，令K3的右孩子指向旋转后的K2，
然后K3和K2在进行一次以K2为根的单旋转，返回K2。
*/
static Position double_rotate_withright(Position K3)
{
	K3->right = single_rotate_withleft(K3->right);
	return single_rotate_withright(K3);
}

/*
二叉平衡树的插入操作,基本思路同二叉查找树一样，在孩子递归查找插入中有一些补充，
插入成功后，从下到上递归的判断每个节点的高度，判断其是否满足平衡原则，如果不满
足需要进行相应的旋转操作。重新定义树平衡高度，返回树根。
*/
AvlTree insert(int x, AvlTree T)
{
	if (NULL == T)		//若树为空树，需要分配节点空间并初始化
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		if (NULL == T)
		{
			printf("Out of space.\n");
			exit(-1);
		}
		else
		{
			T->element = x;
			T->height = 0;
			T->left = T->right = NULL;
		}
	}
	else if (x < T->element)
	{	//若插入元素x比当前节点小，则递归的在其左子树查找
		//若递归返回到某节点后该节点平衡因子高度超过2，则
		//需调整该节点及其孩子位置，通过旋转降低平衡因子高度
		T->left = insert(x, T->left);
		if (2 == height(T->left) - height(T->right))
		{
			if (x < T->left->element)
				T = single_rotate_withleft(T);
			else
				T = double_rotate_withleft(T);
		}
	}
	else if (x > T->element)
	{	//若插入元素x比当前节点大，则递归的在其右子树查找
		//若递归返回到某节点后该节点平衡因子高度超过2，则
		//需调整该节点及其孩子位置，通过旋转降低平衡因子高度
		T->right = insert(x, T->right);
		if (2 == height(T->right) - height(T->left))
		{
			if (x > T->right->element)
				T = single_rotate_withright(T);
			else
				T = double_rotate_withright(T);
		}
	}

	//设置树根的平衡因子高度
	T->height = max(height(T->left), height(T->right)) + 1;

	return T;
}

/*
二叉平衡树的删除
*/
AvlTree delete_avl(int x, AvlTree T)
{
	//printf("开始删除元素\n");
	if (NULL == T)
	{	//若该树为空没有节点可以删除，则返回树根
		printf("Element not found.\n");
		exit(-1);
	}
	else if (x < T->element)
	{	//若该树不为空且当前节点元素比元素x大
		//则递归到该节点的左子树中进行删除
		//若递归返回到某节点后该节点平衡因子高度超过2，则
		//需调整该节点及其孩子位置，通过旋转降低平衡因子高度
		T->left = delete_avl(x, T->left);
		if (2 == height(T->left) - height(T->right))
		{
			if (x < T->left->element)
				T = single_rotate_withleft(T);
			else
				T = double_rotate_withleft(T);
		}
	}
	else if (x > T->element)
	{	//若该树不为空且当前节点元素比元素x小
		//则递归到该节点的右子树中进行删除
		//若递归返回到某节点后该节点平衡因子高度超过2，则
		//需调整该节点及其孩子位置，通过旋转降低平衡因子高度
		T->right = delete_avl(x, T->right);
		if (2 == height(T->right) - height(T->left))
		{
			if (x > T->right->element)
				T = single_rotate_withright(T);
			else
				T = double_rotate_withright(T);
		}
	}
	else if (T->left && T->right)
	{	//若找到要删除的节点且该节点有两个孩子
		//则将该节点右子树元素值最小的节点赋值给该节点
		//同时将右子树最小的节点删除释放空间
		AvlTree tempCell = find_min(T->right);
		T->element = tempCell->element;
		T->right = delete_avl(T->element, T->right);
	}
	else
	{	//若找到要删除的节点且该节点有一个个孩子或者没有孩子
		//则移动该节点指针到左右节点相当于父节点指向了该节点,释放该节点空间
		//printf("删除成功\n");
		AvlTree tempCell = T;
		if (NULL == T->left)
			T = T->right;
		else if (NULL == T->right)
			T = T->left;
		free(tempCell);
	}

	return T;
}

/*
中序遍历
*/
void in_order_traverse(AvlTree T)
{
	if (NULL != T)
	{
		in_order_traverse(T->left);
		printf("%d->", T->element);
		in_order_traverse(T->right);
	}
}

/*
先序遍历
*/
void pre_order_traverse(AvlTree T)
{
	if (NULL != T)
	{
		printf("%d->", T->element);
		pre_order_traverse(T->left);
		pre_order_traverse(T->right);
	}
}




void main()
{
	//创建平衡二叉树
	AvlTree T = NULL;
	T = insert(13, T);
	T = insert(7, T);
	T = insert(5, T);
	T = insert(4, T);
	T = insert(6, T);
	T = insert(10, T);
	T = insert(9, T);
	T = insert(8, T);
	T = insert(12, T);
	T = insert(17, T);
	T = insert(15, T); 
	T = insert(14, T);
	T = insert(19, T);
	/* The constructed AVL Tree would be
	      10
	     /  \
	    7    15
	   / \   / \
	  5   9 13 17
	 /\  /  /\  \
	4  6 8 12 14 19 
	*/

	//先序遍历平衡二叉树
	pre_order_traverse(T);
	printf("\n");

	//删除二叉平衡树元素
	delete_avl(10, T);
	/* The AVL Tree after deletion of 10
	       12
	       / \
	      7  15
	     / \ / \
	    5  9 13 17
	   /\  /  \   \
	  4  6 8  14  19
	*/
	pre_order_traverse(T);

	return;
}


/*
对该程序的其他写法见http://www.geeksforgeeks.org/avl-tree-set-2-deletion/
*/
