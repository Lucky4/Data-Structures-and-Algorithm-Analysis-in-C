/*
希尔排序（缩小增量排序）

思路：通过比较相距一定间隔的元素来完成工作，突破了亚2次方时间界。

方法：使用一个序列，h1，h2，...ht，只要h1等于1，在使用hk的一趟排序后，对于每一个i我们有A[i]<=A[i+hk]，所有间隔hk的元素都
      被排序。排序的方式参照直接插入排序。ht=N/2

总结：希尔排序的时间复杂度依赖于增量序列，最坏为O（N2），最好为O（N）
*/

//hk排序的一般做法是，对于hk，hk-1，...N-1中的每一个位置i，把其上的元素放到i,i-hk,i-2hk...中间的正确位置上
void ShellSort(ElementType A[], int N)
{
	int i, j, increment;
	ElementType tmp;

	for(increment = N/2; increment > 0; increment /= 2)//外循环次数为缩小增量的个数
		for (i = increment; i < N; i++)
		{	//从增量位置i开始逐渐增加移动位置，
			//由后向前以增量间隔缩小倍数的位置为要排序的数据，
			//按照直接插入排序的思想进行排序。
			tmp = A[i];
			for (j = i; j >= increment; j -= increment)
				if (A[j - increment] > tmp)
					A[j] = A[j - increment];
				else
					break;
			A[j] = tmp;
		}
}














int main()
{
	int i;
	int a[10] = { 2, 4, 67, 12, 43, 78, 5, 3, 8, 65 };

	ShellSort(a, 10);
	for (i = 0; i < 10; i++)
		printf("%d,", a[i]);

    return 0;
}

