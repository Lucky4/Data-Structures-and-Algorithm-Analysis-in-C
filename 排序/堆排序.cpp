/*
堆排序

思路：堆排序分为构建堆、删除最值、调整堆即下滤操作。

方法：使用数组代替ADT（抽象数据类型）的方式实现初始堆数组下标从零开始。

总结：时间复杂度为O(N*logN)。
*/

//下滤操作
void PercDown(ElementType A[], int i, int N)	//i为父节点下标
{
	int replChild;		//下滤操作时用来与根节点交换的孩子节点下标
	ElementType tmp;	//一般利用交换进行的排序都要有一个tmp变量

	//每次开始都要取出最顶点下标，所以可以写在for语句头中作为初始条件
	//遍历的条件就是父节点还有孩子
	//执行完此次下滤操作后需要找到下次下滤操作的父节点，所以我们也可以写到for语句头
	for (tmp = A[i]; 2*i+1 < N; i = replChild)	//i = replChild是在语句体执行之后执行的
	{
		if (2 * i + 1 != N - 1 && A[2 * i + 1] < A[2 * i + 1 + 1])//若右孩子存在且右孩子大则将右孩子下滤
			replChild = 2 * i + 1 + 1;
		if (2 * i + 1 != N - 1 && A[2 * i + 1] > A[2 * i + 1 + 1])//若右孩子存在且右孩子小则将左孩子下滤
			replChild = 2 * i + 1;
		if(2 * i + 1 == N - 1)		//若右孩子不存在则将左孩子下滤
				replChild = 2 * i + 1;

		//书上方法
		//replChild = 2*i+1;
		//if (replChild != N - 1 && A[replChild + 1] > A[replChild])
		//	replChild++;

		//满足孩子比父亲数据大,将孩子数据赋值父亲数据,
		//否则，不满足堆结构，不需要下滤跳出循环
		if (tmp < A[replChild])
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

