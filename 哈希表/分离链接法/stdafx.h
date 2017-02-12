#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
//#define MinTableSize 10		//哈希表最小范围
typedef int ElementType;


/*
采用分离链接法实现的哈希表
*/
typedef struct ListNode		//链接节点结构带头节点
{
	ElementType data;	//关键字信息
	struct ListNode *next;
}*Position, *List;

typedef struct HashTb		//哈希表结构
{
	int TableSize;	//哈希表大小
	List *TheLists;	//指向表头指针
}*HashTable;


//创建哈希表初始化头结点
HashTable InitializeTable(int);

//哈希表中根据关键字查找例程
Position Find(ElementType, HashTable);

//散列函数
int Hash(ElementType, ElementType);

//哈希表插入关键字例程
void Insert(ElementType, HashTable);

//在哈希表中删除关键字例程
int Delete(ElementType, HashTable);

//销毁哈希表
void Destroy(HashTable);