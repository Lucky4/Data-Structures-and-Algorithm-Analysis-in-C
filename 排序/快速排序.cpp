/*
 * 思想：基于分治递归的思想
 * 
 * 步骤：
 *   1. 如果S中元素是0或1，则返回。
 *   2. 取S中任一元素v，称为枢纽元（pivot）。
 *   3. 将S分为比v小的集合s1和比v大的集合s2。
 *   4. 在两个子集合中递归执行上述操作。
 *
 * 复杂度：
 *      平均运行时间是O（N*logN），最坏情形为O（N2），算法之所以快是由于非常精炼和高度优化的内部循环。
 *
 * 细节：
 * 1. 选择枢纽元：
 *      错误的选择方法如：将第一个作为枢纽元，如果输入是预排序的或者是反序的，所有元素不是被划入s1就是划入s2，花费时间是二次的。
 *      安全的选择如：   随机选择一个枢纽元，随机数的生成是昂贵的。减少不了其余部分的运行时间。
 *      三数值分割法：   枢纽元选择中值，消除了预排序输入的坏情形。
 *
 * 2. 与枢纽元素相同的元素要选择交换i和j：
 *      如果与枢纽元素相同，i和j不交换元素可能会产生不均衡的子数组，如数组中的数字都相同的情况。
 *
 * 3. 对小数组不递归的使用快速排序，当数组中的元素小于等于20时，快排不如插入排序好。
 *
 * 参考：《数据机构与算法分析——C语言描述》
 */

# define Cutoff (3)


/*
 * 交换元素，由于变量的作用域问题，这里要使用引用类型传递
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
		Swap(&A[Center], &A[Right]);

	Swap(&A[Center], &A[Right]);
	return A[Right];    //返回的是中间元素
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
	if (Left + Cutoff <= Right)
	{	//当要排序的数据个数多余3个时使用快速排序
		//外层循环直至i<j时，跳出循环，交换i位置元素与枢纽元素
		//否则，比i位置大的元素与比j位置小的元素进行交换
		pivot = Median(A, Left, Right);
		i = Left;
        j = Right - 1;
        
		for (; ; )
		{
			while (A[++i] < pivot) {}
			while (A[--j] > pivot) {}
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
        }
        
        //i与枢纽元素交换
		Swap(&A[i], &A[Right]);

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

