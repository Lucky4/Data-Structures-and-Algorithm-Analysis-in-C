/*
输出函数
*/
void printArray(int *array, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}

/*
交换函数
*/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
全排列函数递归实现（未处理重复元素情况）
*/
void permute(int *array, int i, int length) 
{
	//递归的出口：没有元素可以交换
	if (length == i)
	{	
		printArray(array, length);
		return;
	}

	//递归交换
	int j;
	for (j = i; j < length; j++) 
	{
		swap(array + i, array + j);		//第一个位置的元素分别和其他位置上的元素交换
		permute(array, i + 1, length);	//递归的在下一个位置分别和其他位置上的元素交换
		swap(array + i, array + j);		//返回数组初状态
	}
	return;
}

/*
判断后面是否重复出现的数字
*/
int is_swap(int start, int *array, int end)
{
	int i;
	for (i = start; i < end; i++)
		if (array[i] == array[end])
			return 0;
	return 1;
}

/*
全排列函数递归实现
去掉重复规则：去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换
*/
void permute2(int *array, int i, int length)
{
	//递归的出口：没有元素可以交换
	if (length == i)
	{
		printArray(array, length);
		return;
	}
	//递归交换
	int j;
	for (j = i; j < length; j++)
	{
		if (is_swap(i, array, j))
		{
			swap(array + i, array + j);		//第一个位置的元素分别和其他位置上的元素交换
			permute2(array, i + 1, length);	//递归的在下一个位置分别和其他位置上的元素交换
			swap(array + i, array + j);		//返回数组初状态
		}
	}
}




//数组大小
#define MAX_NUM 20
//存储组合，位置0保存的要选出的个位数
int comb[MAX_NUM];

/*
组合算法的递归实现

思路：
先确定递归的规模，比如C（5，3）我们从5开始，第一个数为5，第二个数就要从1，2，3，4中选出即C（4，2），
假入第二个数为4，那么第三个数就要从1，2，3中选取即C（3，1），
假如第二个数为3，那么第三个数就要从1，2，4中选取即C（2，1），
假如第二个数为2，那么第三个数就要从1中选取即C（1，1），
之后就从4开始重复上述过程，直到3结束后。2和1就不需要执行了。所以外层递归的次数就是从5到3。

总结：开始的时候就要想到组合和排列的不同，由于组合的位数不同我们不能同排列的那样通过交换来获得结果，而是需要新的存储空间。
*/
void combination(int m, int n)//从n个数中选出m个
{
	int i, j;

	//外层递归次数
	for (int i = n; i >= m; i--)
	{
		//用存储的数据结构保存本次排列的一个位数
		comb[m] = i;
		//缩小规模
		if (m > 1)
			combination(m - 1, i - 1);
		else
		{
			//探测到一个组合，输出一个组合
			for (j = comb[0]; j > 0; j--)
				printf("%d", comb[j]);

			printf("\n");
		}
	}

	return;
}






int main()
{
    comb[0] = 3;
    combination(comb[0], 8);
    return 0;
}
