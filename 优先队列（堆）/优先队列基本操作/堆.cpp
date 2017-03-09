#include "stdafx.h"


/*
创建初始化优先队列
小顶堆，最小元在根节点
*/
PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	//申请优先队列结构空间
	H = (PriorityQueue)malloc(sizeof(struct HeapStrcut));
	if(NULL == H)
	{ 
		printf("Out of space.\n");
		exit(-1);
	}
	//申请存储数据数组Elements空间
	H->Elements = (ElementType *)malloc(sizeof(ElementType)*MaxElements);
	if (H->Elements == NULL)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	//初始化优先队列
	H->Capcity = MaxElements;
	H->Size = 0;
}

/*
插入，交换而实施的赋值语句为d+1
*/
void Insert(ElementType X, PriorityQueue H)
{
	int i;

	if(IsFull(H))
	{ 
		printf("The PriorityQueue is full.\n");
		exit(-1);
	}
	
	for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = X;
}
//我的插入写法，交换而实施的赋值语句为3d
void Insert2(ElementType X, PriorityQueue H)
{
	int i, tmp;

	if (IsFull(H))
	{
		printf("The PriorityQueue is full.\n");
		exit(-1);
	}

	H->Elements[++H->Size] = X;
	tmp = H->Elements[H->Size];
	for (i = H->Size; i / 2 > 0; i /= 2)
		if (H->Elements[i / 2] > H->Elements[i])
			H->Elements[i] = H->Elements[i / 2];
		else
			break;
	H->Elements[i] = tmp;
}

/*
删除最小节点
*/
ElementType DeleteMin(PriorityQueue H)
{
	int i, child;
	ElementType MinElement, LastElement;

	if (IsEmpty(H))
	{
		printf("The PriorityQueue is empty.\n");
		exit(-1);
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for (i = 1; i * 2 <= H->Size; i = child)
	{
		//查找较小的子节点
		child = i * 2;
		if (child != H->Size && H->Elements[child + 1] < H->Elements[child])
			child++;

		//下滤操作
		if (LastElement > H->Elements[child])
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

/*
判断优先队列是否为空
*/
int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

/*
判断优先队列是否已满
*/
int IsFull(PriorityQueue H)
{
	return H->Size == H->Capcity;
}

/*
显示优先队列元素
*/
void show(PriorityQueue H)
{
	int i;
	for (i = 1; i <= H->Size; i++)
		printf("%d\t", H->Elements[i]);
	printf("\n");
}







int main()
{
	int max_elements, flag=1, choose, value;

	//构建优先队列
	printf("开始构建优先队列\n");
	printf("请输入优先队列大小：\n");
	scanf("%d", &max_elements);
	PriorityQueue H = Initialize(max_elements);
	
	//优先队列操作
	while (flag)
	{
		printf("请输入操作，1.插入 2.删除最小元 3.显示优先队列元素.\n");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printf("请输入插入元素\n");
			scanf("%d", &value);
			Insert(value, H);
			break;

		case 2:
			DeleteMin(H);
			show(H);
			break;

		case 3:
			show(H);
			break;

		default:
			flag = 0;
			break;
		}
	}




    return 0;
}

