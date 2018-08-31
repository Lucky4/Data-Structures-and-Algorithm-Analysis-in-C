# 算法步骤：
# 前3步与快速排序一样，多一个第四步，
# 如果k <= S1，那么第k小元素必然在S1内。
# 如果k = 1 + |S1|，那么枢纽元就是第k小元素。
# 否则第k小元素在S2中。
#
# 时间复杂度：
# 快速选择节省了一次递归调用，最坏为O(N2)，平均为O(N)。


def QSort(A, k, Left, Right):
    if Left < Right:
        pivot = Median(A, Left, Right)
        i = Left
        j = Right - 1

        while True:
            while A[i] < pivot:
                i += 1

            while A[j] > pivot:
                j -= 1

            if i < j:
                tmp = A[i]
                A[i] = A[j]
                A[j] = tmp
            else:
                break

        tmp = A[i]
        A[i] = A[Right]
        A[Right] = tmp

        if k < i:
            QSort(A, k, Left, i-1)
        else:
            QSort(A, k, i+1, Right)


def Median(A, Left, Right):
    Center = (Left + Right) / 2

    if A[Left] > A[Center]:
        tmp = A[Left]
        A[Left] = A[Center]
        A[Center] = tmp
    
    if A[Left] > A[Right]:
        tmp = A[Left]
        A[Left] = A[Right]
        A[Right] = tmp

    if A[Center] > A[Right]:
        tmp = A[Center]
        A[Center] = A[Right]
        A[Right] = tmp

    tmp = A[Center]
    A[Center] = A[Right]
    A[Right] = tmp

    return A[Right]


if __name__ == '__main__':
    k = 2
    A = [3, 1, 6, 10, 2, 6]

    QSort(A, k, 0, 5)
    print A[k-1]