#include "stdafx.h"


/*
创建哈希表
*/
HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	//申请哈希表结构存储空间并设置表大小
	H = (HashTable)malloc(sizeof(struct HashTb));
	if (NULL == H)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	H->TableSize = TableSize;

	//申请哈希表存储单元存储空间
	H->TheCells = (Cell*)malloc(sizeof(struct HashEntry) * H->TableSize);
	if (NULL == H->TheCells)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	//将每个存储单元的初始状态设置为空
	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;

	return H;
}

/*
哈希函数
*/
Position Hash(ElementType key, int TableSize)
{
	return key % TableSize;
}

/*
使用平方探测散列法查找例程
*/
Position Find(ElementType key, HashTable H)
{
	Position currentPos;	//关键字散列表位置
	int collisionNum=0;		//冲突次数计数变量

	currentPos = Hash(key, H->TableSize);	//计算散列表位置
	while (H->TheCells[currentPos].Info != Empty && H->TheCells[currentPos].Element != key)
	{	
		//进行一位二进制左移并减一，F(i)=F(i-1)+2*i-1
		//若定位超过数组，将散列表位置拉回到范围内
		currentPos += 2 * ++collisionNum - 1;
		if (currentPos >= H->TableSize)
			currentPos -= H->TableSize;
	}
	return currentPos;
}

/*
使用平方探测散列表的插入例程
*/
void Insert(ElementType key, HashTable H)
{
	Position Pos;

	//通过Find操作查找哈希表中key关键字是否在表中
	//若存在则不做其他操作，否则在Find查找到的空位置上插入该关键字
	Pos = Find(key, H);
	if (H->TheCells[Pos].Info != Legitimate)
	{
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Element = key;
	}
}

/*
使用平方探测散列表的删除例程
*/
int Delete(ElementType key, HashTable H)
{
	Position Pos;

	Pos = Find(key, H);
	if (H->TheCells[Pos].Info == Legitimate)
	{
		H->TheCells[Pos].Info = Deleted;
		return 1;
	}

	return 0;
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
		printf("|           5.Exit.                           |\n");
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
				if (H->TheCells[pos].Info == Legitimate)
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
				else
					printf("Delete failed.\n");
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

