/*
打印输出一个排列 
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
交换连个元素
*/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
全排列函数
*/
void permute(int *array, int i, int length) 
{	//递归的出口：没有元素可以交换
	if (length == i) 
	{	
		printArray(array, length);
		return;
	}

	int j;
	for (j = i; j < length; j++) 
	{
		swap(array + i, array + j);	//第一个位置的元素分别和其他位置上的元素交换
		permute(array, i + 1, length);	//递归的在下一个位置分别和其他位置上的元素交换
		swap(array + i, array + j);	//返回数组初状态
	}
	return;
}



int main()
{
    int A[4] = { 1, 2, 3, 4 };
    permute(A, 0, 4);
    return 0;
}
