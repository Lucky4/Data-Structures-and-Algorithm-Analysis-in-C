/*
堆排序

思路：堆排序分为构建堆、删除最值、调整堆即下滤操作。

方法：使用数组代替ADT（抽象数据类型）的方式实现初始堆数组下标从零开始。

总结：时间复杂度为O(N*logN)。
*/

//下滤操作
void PercDown(ElementType A[], int i, int N)	//i为父节点下标
{
	int replChild;
	ElementType tmp;

	for (tmp = A[i]; 2*i+1 < N; i = replChild)	//i = replChild是在语句体执行之后执行的
	{
		replChild = 2*i;
		if (replChild != N - 1 && A[replChild + 1] < A[replChild])
			replChild++;

		if (tmp > A[replChild])
			A[i] = A[replChild];
		else
			break;
	}
	A[i] = tmp;
}

//堆排序
void HeapSort(ElementType A[], int N)
{
	int i, temp;;

        //根据数组构建堆
	for (i = N / 2; i >= 0; i--)
        PercDown(A, i, N);
        
	for (i = N - 1; i > 0; i--)
	{	//交换根与最后的节点数据
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;

		PercDown(A, 0, i);
	}
}







int main()
{
	int i;
	int a[10] = { 2, 4, 67, 12, 43, 78, 5, 3, 8, 65 };

    HeapSort(a, 10);
    
	for (i = 0; i < 10; i++)
		printf("%d,", a[i]);

    return 0;
}

