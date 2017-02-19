/*
插入排序

思路：插入排序由N-1趟排序组成，对于P=1趟到P=N-1趟，插入排序保证位置0到位置P为已排序状态，位置0到位置P-1是已排过序的。

实现：在第P趟，将位置P上的元素移动到前P+1个元素正确的位置上。

定理：通过交换相邻元素进行排序的任何算法平均需要Ω（N2）时间
*/

//我最初的思路，复杂度为O（N2），即使是在都是顺序的情况下。
void MyInsertionSort(ElementType A[], int N)
{
	int j, P;

	ElementType tmp, exc;
	for (P = 1; P < N; P++)
	{
		tmp = A[P];
		for (j = P; j > 0; j--)
		{
			if (A[j-1] > tmp)
			{
				exc = A[j-1];
				A[j-1] = A[j];
				A[j] = exc;
			}
			tmp = A[j - 1];
		}
	}
}

//书上的算法，该算法在顺序的情况下比我的快，因为内层for循环检测总是立即判定不成立而终止
void InsertionSort(ElementType A[], int N)
{
	int j, P;

	ElementType tmp;
	for (P = 1; P < N; P++)
	{
		tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > tmp; j--)//若条件已满足，此时j的值已减一
			A[j] = A[j - 1];
		A[j] = tmp;
	}
}







int main()
{
	int i;
	int a[10] = { 2, 4, 67, 12, 43, 78, 5, 3, 8, 65 };

	MyInsertionSort(a, 10);
	for (i = 0; i < 10; i++)
		printf("%d,", a[i]);

    return 0;
}

