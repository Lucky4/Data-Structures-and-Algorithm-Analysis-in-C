/**
 * 复杂度：
 *        O（N2）
 * 
 * 优化：
 *        使用flag标记上次是否发生交换，未发生说明后面已经是有序的了，不需要再将程序进行下去了。
 */
 void BubbleSort(int A[], int N)
 {
     int tmp, flag = 1;
     
     for (int i = N; i > 0 && flag; i--) {
        flag = 0;
        for (int j = 0; j < N - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;

                flag = 1;
            }
        }
     }
 }