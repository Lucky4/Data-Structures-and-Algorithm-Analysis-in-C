#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


//二叉树节点声明
typedef struct BTNode
{
	int data;
	struct BTNode *pLeft;
	struct BTNode *pRight;
}BTNode, *BTree;

//创建一棵二叉树
BTree create_tree();
//二叉树的前序非递归遍历
void pre_nonrecursive(BTree);
//二叉树的前序非递归遍历1
void pre_nonrecursive1(BTree);
//二叉树的前序非递归遍历2
void pre_nonrecursive2(BTree);
//二叉树的中序非递归遍历
void in_nonrecursive(BTree);
//二叉树的中序非递归遍历1
void in_nonrecursive1(BTree);
//二叉树的后序非递归遍历
void post_nonrecursive(BTree);
//二叉树的后序非递归遍历1
void post_nonrecursive1(BTree);
//二叉树深度
int depth(BTree);


//保存二叉树节点的栈声明
typedef struct TSNode		//TreeStackNode
{
	BTree data;
	struct TSNode *next;
}*PNODE, *PSTACK;

//清空栈
void make_empty(PSTACK);
//判断栈是否为空
int is_empty(PSTACK);
//创建栈
PSTACK create_stack();
//进栈
void push(BTree, PSTACK);
//返回栈顶元素
BTree top(PSTACK);
//出栈
void pop(PSTACK);