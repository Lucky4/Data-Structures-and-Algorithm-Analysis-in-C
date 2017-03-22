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
void insertSort(PNODE pHead);			 //单链表的直接插入排序


/*
单链表的直接插入排序
*/
void insertSort(PNODE pHead)
{
	int value;
	PNODE pCom, pPre, pTmp;

	//由于链表不能够顺序访问，故这里定义个两个指针用来跟踪，
	//要比较元素pTmp和当前比较元素的前驱pCom
	for (pTmp = pHead->next->next; pTmp != NULL; pTmp = pTmp->next)
	{
		//寻找pPre
		pPre = pHead;
		while (pPre->next != pTmp)
			pPre = pPre->next;

		//只要pCom所指的节点的下一个节点不是pTmp，就向后遍历
		//若pCom所指的节点的数据大于pTmp所指节点数据，则交换这连个节点的位置
		for (pCom = pHead; pCom->next != pTmp; pCom = pCom->next)
		{
			if (pCom->next->data > pTmp->data)
			{
				pPre->next = pTmp->next;
				pTmp->next = pCom->next;
				pCom->next = pTmp;
				break;
			}
		}
	}
}

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
	while (1)
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
	printf("输入-1结束输入\n");
	pHead = create_list();

	//插入排序
	insertSort(pHead);
	traverse(pHead);

	return 0;
}