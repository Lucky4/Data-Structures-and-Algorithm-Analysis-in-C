/****************************************************************
二叉查找树的基本操作，程序还有一个问题，如果使用一个SearchTree
变量传递参数时会报错使用为初始化的变量，如果使用一个初始化的
SearchTree时则当删除初始化的element时会出现错误值。

问题已解决一个：
在兰亭风雨的代码仓库中看到了作者的BST树实现知道了上面一个问题
因为delete返回的是根节点，删除根节点后返回值肯定会有问题。
1.传递参数问题原因是因为create函数中调用insert时没有接受insert
函数的返回结果，导致循环在NULL == T情况。

注：本程序思路来源于《数据结构与算法分析—C语言描述》
    在此感谢兰亭风雨大大代码的思路
****************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


//二叉查找树结构
typedef struct TreeNode
{
	int element;
	struct TreeNode *left;
	struct TreeNode *right;
}*SearchTree, *Position;


SearchTree make_empty(SearchTree T);
Position find(int x, SearchTree T);
Position find_min(SearchTree T);
Position find_max(SearchTree T);
SearchTree insert(int x, SearchTree T);
SearchTree delete_tree(int x, SearchTree T);


/*
创建一颗空树
使用递归的方式由下到上将树中的每一个点释放空间，
返回NULL。可以初始化一个单节点，这里使用递归更遵循树的定义。
*/
SearchTree make_empty(SearchTree T)
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
二叉查找树的find操作
使用递归的方式查找元素x，若树T为空，则返回NULL，
若元素x比当前元素小，则递归向该元素节点的左子树查找，
若元素x比当前元素大，则递归向该元素节点的右子树查找，
最后返回查找到的元素x。
*/
Position find(int x, SearchTree T)
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
二叉查找树的find_min操作
因为二叉排序树是有序的，所以只需要递归的查找左子树，
如果树为空，返回NULL，如果树根不为空，根的左子树为空，返回根T，
否则递归的在根的左子树中查找，返回递归到最后的根元素。
*/
Position find_min(SearchTree T)
{
	if (NULL == T)
		return NULL;
	if (NULL == T->left)
		return T;
	else
		return find_min(T->left);
}

/*
二叉查找树的find_max操作，
使用非递归的方式进行查找。
*/
Position find_max(SearchTree T)
{
	if (NULL != T)
	{
		while (NULL != T->right)
			T = T->right;
	}

	return T;
}

/*
插入元素到二叉查找树中
返回为根节点，因为如果树根为空的话需要插入创建一个节点并返回，
可以把插入想象为find操作，发现不做或做些更新，否则插入路径上最后一点。
*/
SearchTree insert(int x, SearchTree T)
{
	if (NULL == T)		//若树为空树，需要分配节点空间并初始化
	{
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		if (NULL == T)
		{
			printf("Out of space.\n");
			exit(-1);
		}
		T->element = x;
		T->left = T->right = NULL;
	}
	else if (x < T->element)			//若插入元素x比当前节点小，则递归的在其左子树查找
		T->left = insert(x, T->left);
	else if (x > T->element)			//若插入元素x比当前节点大，则递归的在其右子树查找
		T->right = insert(x, T->right);

	return T;
}

/*
二叉查找树的删除例程,查找到元素x的节点
若要删除节点是一片树叶，则立即删除，若要删除节点有一个儿子可以在其父节点调整指针删除，
若要删除有两个二个儿子，则用其右子树最小的节点代替该节点并将右子树删除。
*/
SearchTree delete_tree(int x, SearchTree T)
{
	if (NULL == T)
	{	//若该树为空没有节点可以删除，提示错误退出程序
		printf("Element not found.\n");
		exit(-1);
	}
	else if (x < T->element)
	{	//若该树不为空且当前节点元素比元素x大
		//则递归到该节点的左子树中进行删除
		T->left = delete_tree(x, T->left);
	}
	else if (x > T->element)
	{	//若该树不为空且当前节点元素比元素x小
		//则递归到该节点的右子树中进行删除
		T->right = delete_tree(x, T->right);
	}
	else if (T->left && T->right)
	{	//若找到要删除的节点且该节点有两个孩子
		//则将该节点右子树元素值最小的节点赋值给该节点
		//同时将右子树最小的节点删除释放空间
		SearchTree tempCell = find_min(T->right);
		T->element = tempCell->element;
		T->right = delete_tree(T->element, T->right);
	}
	else
	{	//若找到要删除的节点且该节点有一个个孩子或者没有孩子
		//则移动该节点指针到左右节点相当于父节点指向了该节点,释放该节点空间
		SearchTree tempCell = T;
		if (NULL == T->left)
			T = T->right;
		else if (NULL == T->right)
			T = T->left;
		free(tempCell);
	}

	return T;
}

/*
根据所给长为len的arr数组，按数组中元素构造一棵二叉排序树
*/
SearchTree create_searchTree(int *arr, int len)
{
	SearchTree T = NULL;
	int i;
	//按顺序逐个节点插入到二叉排序树中
	for (i = 0; i < len; i++)
		T = insert(arr[i], T);		//注意此处不要忘了接受返回值否则会循环在T == NULL
	return T;
}

/*
中序遍历
*/
void in_order_traverse(SearchTree T)
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
void pre_order_traverse(SearchTree T)
{
	if (NULL != T)
	{
		printf("%d->", T->element);
		pre_order_traverse(T->left);
		pre_order_traverse(T->right);
	}
}




/*
使用数组初始化构造一棵树，利用中序遍历和先序遍历验证是否是二叉排序树
*/
void main()
{
	int i;
	int num;
	printf("请输入节点个数：\n");
	scanf("%d", &num);

	//输入num个整数
	int *arr = (int *)malloc(num * sizeof(int));
	printf("请依次输入这%d个整数（必须互不相等）：\n", num);
	for (i = 0; i<num; i++)
		scanf("%d", arr + i);

	//创建二叉排序树
	SearchTree T = create_searchTree(arr, num);
	printf("中序遍历该二叉排序树的结果：\n");
	in_order_traverse(T);
	printf("\n");

	//查找给定整数
	int key;
	printf("请输入要查找的整数：\n");
	scanf("%d", &key);
	Position p = find(key, T);
	if (p)
		printf("查找成功！\n");
	else
		printf("查找失败。。\n");

	//插入给定的整数
	printf("请输入要插入的整数：");
	scanf("%d", &key);
	if (insert(key, T))
	{
		printf("插入成功，插入后的中序遍历结果：");
		in_order_traverse(T);
		printf("\n");
	}
	else
		printf("插入失败，该二叉排序树中已经存在整数%d\n", key);

	//删除给定的整数
	printf("请输入要删除的整数：");
	scanf("%d", &key);
	if (delete_tree(key, T))
	{
		printf("删除成功，插入后的中序遍历结果：");
		in_order_traverse(T);
		printf("\n");
	}
	else
		printf("删除失败，该二叉排序树中不存在整数%d\n", key);

}