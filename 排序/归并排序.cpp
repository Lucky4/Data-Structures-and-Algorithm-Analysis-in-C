/*
归并排序

思路：分治思想

方法：先将数组递归的按照对半分的方式分解为一个元素，此时数组为前后一半各位排序的数组，然后通过merge方法将两个数组合并。

总结：时间复杂度O（N*logN），缺点需要附加内存。
*/
//看书和网上的帖子后自己的写法
//Lpos,Rpos, RightEnd均为下标
void Merge(ElementType A[], int Lpos, int Rpos, int RightEnd)
{
	int start = Lpos;			//最后用于将数组TempArray赋值数组A的其起始下标
	int LeftEnd = Rpos - 1;			//左侧结束下标
	int NumElements = RightEnd - Lpos + 1;					//要归并的所有元素个数
	int *TempArray = (int *)malloc(sizeof(int)*(RightEnd - Lpos + 1));	//存放结果数组

	//TempArray从下标0开始存储归并排序好的元素
	int i = 0;
	while(Lpos <= LeftEnd && Rpos <= RightEnd)
	{
		if (A[Lpos] <= A[Rpos])
			TempArray[i++] = A[Lpos++];
		else
			TempArray[i++] = A[Rpos++];
	}

	//右侧已归并结束
	while (Lpos <= LeftEnd)
		TempArray[i++] = A[Lpos++];
	//左侧已归并结束
	while (Rpos <= RightEnd)
		TempArray[i++] = A[Rpos++];

	//将TempArray中排序好的元素赋值A,是的A中的这一段元素处于排序状态
	int j;
	for (j = 0; j < NumElements; j++)
		A[j + start] = TempArray[j];

	free(TempArray);
}

//排序例程
void MSort(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (Left < Right)
	{
		MSort(A, Left, Center);
		MSort(A, Center + 1, Right);
		Merge(A, Left, Center + 1, Right);
	}
}

//书上写法
void Merge1(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;	//此处与上面函数实现不同，使得TempArray的起点与A同步,避免了重复使用TempArray的部分
	NumElements = RightEnd - Lpos + 1;

	while (Lpos <= LeftEnd && Rpos <= RightEnd)
	{
		if (A[Lpos] < A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];
	}

	while (Lpos <= LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];
	while (Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];

	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];

}

//书上写法
void MSort1(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
	int Center;

	if (Left < Right)
	{
		Center = (Left + Right) / 2;
		MSort1(A, TmpArray, Left, Center);
		MSort1(A, TmpArray, Center + 1, Right);
		Merge1(A, TmpArray, Left, Center + 1, Right);
	}
}







int main()
{
	int b[10];
	int i;
	int a[10] = { 2, 4, 67, 12, 43, 78, 5, 3, 8, 87};

	MSort(a, 0, 9);
	for (i = 0; i < 10; i++)
		printf("%d,", a[i]);

    return 0;
}

