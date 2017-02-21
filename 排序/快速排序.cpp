/*
 * 交换元素·
 */
void Swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*
返回枢纽元素
*/
ElementType Median(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Left], &A[Right]);

	Swap(&A[Center], &A[Right]);
	return A[Right];
}

/*
快速排序
*/
void Qsort(ElementType A[], int Left, int Right)
{
	int i, j;
	ElementType pivot;

	//之前此处如果没有if判断，导致程序崩溃无法运行，
	//因为递归的程序没有出口,无限循环调用自己。
	if (Left + Cutoff >= Right)
	{	//当要排序的数据个数多余3个时使用快速排序
		//外层循环直至i<j时，跳出循环，交换i位置元素与枢纽元素
		//否则，比i位置大的元素与比j位置小的元素进行交换
		pivot = Median(A, Left, Right);
		i = Left;
		j = Right - 1;
		for (; ; )
		{
			while (A[++i] < pivot) {}
			while (A[++j] > pivot) {}
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]);

		//递归的对比枢纽元素小和比枢纽元素大数据进行快速排序
		Qsort(A, Left, i - 1);
		Qsort(A, i + 1, Right);
	}
	else
		//当要排序的数据个数多余3个时使用直接插入排序，效率高于快速排序
		InsertionSort(A + Left, Right - Left + 1);
}



int main()
{
	int b[10];
	int i;
	int a[10] = { 2, 4, 67, 12, 43, 78, 5, 3, 8, 87};

	Qsort(a, 0, 9);
	for (i = 0; i < 10; i++)
		printf("%d,", a[i]);

    return 0;
}

