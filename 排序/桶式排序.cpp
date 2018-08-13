/**
 * 复杂度：
 *        O(M+N)
 *
 * 思想：
 *        输入数据A1, A2, ... , An必须由小于M的整数组成，使用一个大小为M的Count数组，它被全部初始化为0，当读入Ai时Count[Ai]增1，最后扫描数组Count打印排序后的表。
 */
# define M 100
void BucketSort(int A[], int N)
{
    int i, j;
    int Count[M];
    for(j = 0; j < N; j++)
    {
        Count[j] += 1;
    }
    for(i = 1; i < N; i ++)//没有对0排序
        for(j = 0; j < A[i]; j ++)
            if (i > 0)
                printf("%d ", i);
    }
}