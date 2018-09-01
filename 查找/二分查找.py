# -*- coding: utf-8 -*-


# 二分查找
def binary_search(A, target):
    l = 0
    h = len(A) - 1
    m = -1

    while l <= h:
        if A[m] == target:
            return m

        if A[m] < target:
            l = m + 1
            continue

        if A[m] > target:
            h = m - 1
            continue

    return -1


# 查找第一次出现的位置，还可用于查找查找第一个等于或者大于Key的元素。
def search_first_equal(A, target):
    l = 0
    h = len(A) - 1
    m = -1
    while l < h:
        m = (l + h) / 2
        if A[m] >= target:
            h = m
        else:
            l = m + 1
    return l


# 查找最后一次出现的位置，还可用于查找最后一个等于或者小于key的元素。
def search_last_equal(A, target):
    l = 0
    h = len(A) - 1
    m = -1
    while l < h:
        m = (l + h) / 2
        if A[m] > target:
            h = m - 1
        else:
            l = m + 1
    return h


if __name__ == '__main__':
    A = [1, 2, 2, 2, 3, 5, 5, 5, 5, 5]
    print search_first_equal(A, 5)
    print search_last_equal(A, 5)