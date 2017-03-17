// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
网上的思路，利用将每个集合子集与二进制位相联系
http://www.geeksforgeeks.org/power-set/
*/
void printPowerSet(char *set, int set_size)
{
	/*set_size of power set of a set with set_size
	n is (2**n -1)*/
	int pow_set_size = pow(2, set_size);
	int counter, j;

	/*Run from counter 000..0 to 111..1*/
	for (counter = 0; counter < pow_set_size; counter++)
	{
		for (j = 0; j < set_size; j++)
		{
			/* Check if jth bit in the counter is set
			If set then pront jth element from set */
			if (counter & (1 << j))
				printf("%c", set[j]);
		}
		printf("\n");
	}
}

/*
思路链接：http://www.linuxidc.com/Linux/2014-02/96222.htm
*/
int SIZE = 5;
void printPowerSet2(char *set, int set_size)
{
	//递归出口，当当前集合不能够在分解为下一个子集的时候输出所有集合元素
	if (set_size == 0)
	{
		printf("{");
		for (int i = 0; i < SIZE; i++)
			if (set[i] != ' ')
				printf("%c", set[i]);
		printf("}");
		printf("\n");
	}
	else
	{
		//直接递归，递归生成当前集合的所有下一个状态
		printPowerSet2(set, set_size - 1);

		//动态生成子集合存储空间，通过使用空白字符替换每个位置的方式生成当前元素个数的每个子集
		//递归的在生成子集中继续查找子集
		if (set_size > 0)
		{
			char *sub_set = (char *)malloc(sizeof(char)*set_size);
			strcpy(sub_set, set);
			sub_set[set_size - 1] = ' ';
			printPowerSet2(sub_set, set_size - 1);
		}
	}
}






int main()
{
	char set[] = { 'a','b','c' };
	printPowerSet(set, 3);
	char *set2 = "abcd";
	printPowerSet2(set2, 4);


	getchar();
	return 0;
}