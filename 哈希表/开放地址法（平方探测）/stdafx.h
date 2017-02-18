#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
typedef int Position;
enum KindOfEntry {Legitimate, Empty, Deleted};

/*
开放地址法实现哈希表，平方探测法解决冲突
*/
typedef struct HashEntry	//存储单元
{
	ElementType Element;
	enum KindOfEntry Info;//状态
}Cell;

typedef struct HashTb
{
	int TableSize;
	Cell *TheCells;//存储单元数组
}*HashTable;


//创建哈希表
HashTable InitializeTable(int);

//哈希函数
Position Hash(ElementType, int);

//使用平方探测散列表的查找例程
Position Find(ElementType, HashTable);

//使用平方探测散列表的插入例程
void Insert(ElementType, HashTable);

//使用平方探测散列表的删除例程
int Delete(ElementType, HashTable);