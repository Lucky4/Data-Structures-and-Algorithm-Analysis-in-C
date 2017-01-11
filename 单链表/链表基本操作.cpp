#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


typedef struct Node
{
	int data;
	struct Node * next;
}NODE, *PNODE;

int is_empty(PNODE pHead);               //判断链表是否为空
int is_last(PNODE p, PNODE pHead);       //判断当前位置是否为末尾
PNODE create_list();                     //创建带头结点单链表，返回头指针
PNODE find(int x, PNODE pHead);          //查找例程
PNODE find_previous(int x, PNODE pHead); //查找x的前驱
void delete_node(int x, PNODE pHead);    //链表删除例程
void insert(int x, PNODE pHead, PNODE p);//插入例程
void delete_list(PNODE pHead);           //清空链表


/*
创建带头结点单链表，返回头指针
*/
PNODE create_list()
{
	int val;
	PNODE pHead = (PNODE)malloc(sizeof(NODE));
	PNODE pCurrent = pHead;
	pCurrent->next = NULL;
	if (NULL == pHead)
	{
		printf("pHead malloc failed.\n");
		exit(-1);
	}
	printf("Input data(q to quit):");
	while(1)
	{
		scanf("%d", &val);
		if (val == -1)//如果输入为-1，则跳出循环
			break;

		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if (NULL == pNew)
		{
			printf("pNew malloc failed.\n");
			exit(-1);
		}
		pNew->data = val;
		pNew->next = pCurrent->next;
		pCurrent->next = pNew;
		pCurrent = pCurrent->next;
		printf("Input data(q to quit):");
	}

	return pHead;
}

/*
判断链表是否为空
*/
int is_empty(PNODE pHead)
{
	return pHead->next == NULL;
}

/*
判断当前位置是否为末尾
*/
int is_last(PNODE p, PNODE pHead)
{
	return p->next == NULL;
}

/*
查找例程
*/
PNODE find(int x, PNODE pHead)
{
	PNODE p;
	p = pHead->next;

	while (NULL != p && p->data != x)
		p = p->next;

	return p;
}

/*
查找x的前驱
*/
PNODE find_previous(int x, PNODE pHead)
{
	PNODE p;
	p = pHead;
	
	while (NULL != p->next && p->next->data != x)
		p = p->next;

	return p;
}


/*
链表删除例程
通过前驱来删除要删除的节点
*/
void delete_node(int x, PNODE pHead)
{
	PNODE p, temp;
	p = find_previous(x, pHead);

	//如果该前驱p的后面还有节点
	if (!is_last(p, pHead))
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}

/*
插入例程
*/
void insert(int x, PNODE pHead, PNODE p)
{
	PNODE pNew;
	pNew = (PNODE)malloc(sizeof(NODE));
	if (NULL == pNew)
	{
		printf("pNew malloc failed.");
	}

	pNew->data = x;
	pNew->next = p->next;
	p->next = pNew;
}

/*
删除链表
*/
void delete_list(PNODE pHead)
{
	PNODE p, temp;
	p = pHead->next;
	pHead->next = NULL;

	while (p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
}

void traverse(PNODE pHead)
{
	PNODE p = pHead->next;

	while (NULL != p)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}



int main()
{
	int x;
	PNODE pHead, p;

	//创建链表
	pHead = create_list();

	//查找例程
	printf("Input want find data:\n");
	scanf("%d", &x);
	p = find(x, pHead);
	printf("%d\n", p->data);

	//插入例程
	printf("Input want insert data:\n");
	scanf("%d", &x);
	insert(x, pHead, p);
	traverse(pHead);

	//链表删除
	printf("Input want delete data:\n");
	scanf("%d", &x);
	delete_node(x, pHead);
	traverse(pHead);

	//清空链表
	delete_list(pHead);

    return 0;
}

