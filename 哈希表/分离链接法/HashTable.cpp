#include "stdafx.h"


/*
创建哈希表初始化头结点
*/
HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	//此处应该为判断哈希表长度大小，并将其设置为素数
	//先采取输入素数的方式，之后再完善
	//if (TableSize < MinTableSize)
	//{
	//	printf("Table size too smal.\n");
	//	return NULL;
	//}

	//给哈希表结构分配空间
	H = (HashTable)malloc(sizeof(struct HashTb));
	if (NULL == H)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	H->TableSize = TableSize;

	//给哈希表TheLists分配空间
	H->TheLists = (List*)malloc(sizeof(List) * H->TableSize);
	if (NULL == H->TheLists)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	//给TheLists的每个List分陪空间并设置头结点
	for (i = 0; i < H->TableSize; i++)
	{
		H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
		if (NULL == H->TheLists[i])
		{
			printf("Out of space.\n");
			exit(-1);
		}
		else
			H->TheLists[i]->next = NULL;
	}

	return H;
}

/*
散列函数
*/
int Hash(ElementType key, ElementType TableSize)
{
	return key % TableSize;
}

/*
哈希表中根据关键字查找例程
返回指针，该指针指向包含key的那个单元
*/
Position Find(ElementType key, HashTable H)
{
	Position P;
	List L;

	//通过散列函数找到关键字所在的散列表，遍历该表查找关键字所在位置
	L = H->TheLists[Hash(key, H->TableSize)];
	P = L->next;
	while (NULL != P && key != P->data)
		P = P->next;
	return P;
}

/*
哈希表插入关键字例程
*/
void Insert(ElementType key, HashTable H)
{
	Position pos, newCell;
	List L;

	//插入之前先查找关键字，若未能发现关键字，
	//创建节点，将其插入到关键字所散列到的散列表头结点之后。
	pos = Find(key, H);
	if (NULL == pos)
	{
		newCell = (Position)malloc(sizeof(struct ListNode));
		if (NULL == newCell)
		{
			printf("Out of space.\n");
			exit(-1);
		}
		else
		{
			L = H->TheLists[Hash(key, H->TableSize)];
			newCell->next = L->next;
			newCell->data = key;
			L->next = newCell;
		}
	}
	else
		printf("The key element is exists.\n");
}

/*
在哈希表中删除关键字例程
*/
int Delete(ElementType key, HashTable H)
{
	Position pos, pre;
	List L;

	//删除之前先查找关键字
	pos = Find(key, H);
	if (NULL != pos)		//若查找关键字成功删除关键字节点
	{
		L = H->TheLists[Hash(key, H->TableSize)];
		pre = L;			//前驱
		while (pos != pre->next)
		{
			pre = pre->next;
		}
		pre->next = pos->next;
		free(pos);
		return 1;
	}

	return 0;
}

/*
销毁哈希表
*/
void Destroy(HashTable H)
{
	Position pos, temp;
	List L;
	int i;

	//跟哈希表的大小销毁空间
	for (i = 0; i < H->TableSize; i++)
	{
		L = H->TheLists[i];
		pos = L->next;
		L->next = NULL;
		while (pos)	//若散列表不为空，释放散列表空间
		{
			temp = pos;
			pos = pos->next;
			free(temp);
		}
		free(L);	//销毁散列表头结点
	}

	free(H);
}









int main()
{
	int flag=1, c, size, key;
	HashTable H=NULL;
	Position pos;

	while(flag)
	{
		if (NULL == H)
			printf("HashTable is NULL, please create a hashtable.\n");

		printf("|-------------------Choices-------------------|\n");
		printf("|           1.Create Hashtable                |\n");
		printf("|           2.Find element in Hashtable       |\n");
		printf("|           3.Insert element in Hashtable     |\n");
		printf("|           4.Delete element in Hashtable     |\n");
		printf("|           5.Destroy Hashtable               |\n");
		printf("|---------------------------------------------|\n");

		printf("Please input the choice.\n");
		scanf("%d", &c);
		switch (c)
		{
		case 1:
			printf("Please input the hashtable size.\n");
			scanf("%d", &size);
			H = InitializeTable(size);
			break;

		case 2:
			if (H)
			{
				printf("Please input the want find key.\n");
				scanf("%d", &key);
				pos = Find(key, H);
				if (pos)
					printf("Key %d is in the hashtable.\n", key);
				else
					printf("Key %d is not in the hashtable.\n", key);
				break;
			}
			else
				printf("Hashtable is not create.\n");

		case 3:
			if (H)
			{
				printf("Please input the want insert key.\n");
				scanf("%d", &key);
				Insert(key, H);
				printf("Insert success.\n");
				break;
			}
			else
				printf("Hashtable is not create.\n");

		case 4:
			if (H)
			{
				printf("Please input the want delete key.\n");
				scanf("%d", &key);
				if (Delete(key, H))
					printf("Delete success.\n");
				break;
			}
			else
				printf("Hashtable is not create.\n");

		case 5:
			if (H)
			{
				Destroy(H);
				printf("Destroy hashtable success.\n");
				break;
			}
			else
				printf("Hashtable is not create.\n");

		default:
			flag = 0;
			printf("程序运行结束，按任意键退出！\n");
		}
	}

    return 0;
}

