/*
洗牌在生活中十分常见，现在需要写一个程序模拟洗牌的过程。 现在需要洗2n张牌，从上到下依次是第1张，第2张，第3张一直到第2n张。
首先，我们把这2n张牌分成两堆，左手拿着第1张到第n张（上半堆），右手拿着第n+1张到第2n张（下半堆）。接着就开始洗牌的过程，
先放下右手的最后一张牌，再放下左手的最后一张牌，接着放下右手的倒数第二张牌，再放下左手的倒数第二张牌，
直到最后放下左手的第一张牌。接着把牌合并起来就可以了。 例如有6张牌，最开始牌的序列是1,2,3,4,5,6。首先分成两组，
左手拿着1,2,3；右手拿着4,5,6。在洗牌过程中按顺序放下了6,3,5,2,4,1。把这六张牌再次合成一组牌之后，
我们按照从上往下的顺序看这组牌，就变成了序列1,4,2,5,3,6。 现在给出一个原始牌组，请输出这副牌洗牌k次之后从上往下的序列。
输入描述:
第一行一个数T(T ≤ 100)，表示数据组数。对于每组数据，第一行两个数n,k(1 ≤ n,k ≤ 100)，
接下来一行有2n个数a1,a2,...,a2n(1 ≤ ai ≤ 1000000000)。表示原始牌组从上到下的序列。


输出描述:
对于每组数据，输出一行，最终的序列。数字之间用空格隔开，不要在行末输出多余的空格。

输入例子:
3
3 1
1 2 3 4 5 6
3 2
1 2 3 4 5 6
2 2
1 1 1 1

输出例子:
1 4 2 5 3 6
1 5 4 3 2 6
1 1 1 1
*/

/**
 * 我最初的思路，按照归并排序的思想，但是在牛客网上不能通过，估计无论是在时间和空间上都没有达到要求。
 */
void Shuffle()
{
	//输入要进行洗牌的组数
	int groups;
	scanf("%d", &groups);

	int i, j, k;						//循环变量
	int g;							//定义了循环变量g，遍历每组数据
	int n;							//定义了一堆牌数量变量n，共2n张牌
	int times;						//定义了要进行洗牌的次数

	//动态分配结果输出数组的行
	int **row = (int**)malloc(sizeof(int*)*groups);
	for (g = 0; g < groups; g++)
	{
		scanf("%d", &n);	//输入要进行洗牌的n张牌，共2n张牌
		scanf("%d", &times);	//输入要进行洗牌的次数

		//动态分配结果输出数组的列
		row[g] = (int *)malloc(sizeof(int) * 2 * n);

		//为要洗的牌初始化
		int value;
		int *cards = (int *)malloc(sizeof(int) * 2 * n);
		for (i = 0; i < 2 * n; i++)
		{
			scanf("%d", &value);
			cards[i] = value;
		}

		int *tmp_array = (int *)malloc(sizeof(int) * 2 * n);	//临时存储结果数组

		//按照输入的洗牌次数进行洗牌
		for (j = 0; j < times; j++)
		{
			int LPos = 0, RPos = n;						//两堆牌的起始点
			int LeftEnd = n - 1, RightEnd = 2 * n - 1;			//两堆牌的终点

			k = 0;
			while (LPos <=LeftEnd && RPos<= RightEnd)
			{
				tmp_array[k++] = cards[LPos++];
				tmp_array[k++] = cards[RPos++];
			}

			//cards临时结果
			for (i = 0; i < 2 * n; i++)
				cards[i] = tmp_array[i];
		}

		//保存结果
		for (i = 0; i < 2 * n; i++)
			row[g][i] = tmp_array[i]; 

		//释放空间
		free(cards);
		free(tmp_array);
	}

	//输出结果
	for (i = 0; i < groups; i++)
	{
		j = 0;
		while (row[i][j]>0)				//这里是我处理内存溢出bug的方法，比较简陋
		{
			printf("%d ", row[i][j]);
			j++;
		}
		printf("\n");
	}
}

int main()
{
    Shuffle();
    return 0;
}
