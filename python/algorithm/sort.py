import random

N = 10


def initialize():
    return [random.randrange(0, 1.5 * N) for _ in range(0, N)]


def test_sort(sort):
    def f(*args, **kwargs):
        random.seed(43)
        l = initialize()
        sort(l)
        print(l)
        return

    return f


@test_sort
def insertion_sort(l):
    for i in range(len(l)):
        cur = i
        while 0 < cur and l[cur - 1] > l[cur]:
            l[cur], l[cur - 1] = l[cur - 1], l[cur]
            cur -= 1
    return


@test_sort
def bubble_sort(l):
    for i in range(len(l)):
        for j in range(i):
            if l[j] > l[j + 1]:
                l[j], l[j + 1] = l[j + 1], l[j]
    return


@test_sort
def selection_sort(l):
    for i in range(len(l)):
        cur = len(l) - i - 1
        target = cur
        for j in range(len(l) - i):
            if l[target] < l[j]:
                target = j
        l[target], l[cur] = l[cur], l[target]
    return


def heapify(k, n, l):

    left = 2 * k + 1
    right = 2 * k + 2
    target = k
    if left < n and right < n:
        target = right if (l[left] < l[right]) else left
    elif left < n:
        target = left

    if l[k] < l[target]:
        l[k], l[target] = l[target], l[k]
        heapify(target, n, l)
    return


def make_heap(l):
    n = len(l)
    k = n // 2 - 1
    while k >= 0:
        heapify(k, n, l)
        k -= 1
    return


@test_sort
def heap_sort(l):

    make_heap(l)
    for i in range(len(l) - 1, -1, -1):
        l[0], l[i] = l[i], l[0]
        heapify(0, i, l)

    return


def merge(v1, v2, l):

    i, j = 0, 0
    h, m = len(v1), len(v2)

    tmp = []
    while i < h and j < m:
        if v1[i] < v2[j]:
            tmp.append(v1[i])
            i += 1
        else:
            tmp.append(v2[j])
            j += 1

    if i < h:
        tmp.extend(v1[i:])
    else:
        tmp.extend(v2[j:])

    return tmp


def _merge_sort(l):
    if len(l) <= 1:
        return l

    mid = len(l) // 2

    v1 = l[:mid]
    v2 = l[mid:]

    v1 = _merge_sort(v1)
    v2 = _merge_sort(v2)

    l = merge(v1, v2, l)

    return l


@test_sort
def merge_sort(l):
    l[:] = _merge_sort(l)

    return


def inplace_merge(low, mid, high, l):
    i, j = low, mid
    h, m = mid, high

    tmp = []

    while i < h and j < high:
        if l[i] < l[j]:
            tmp.append(l[i])
            i += 1
        else:
            tmp.append(l[j])
            j += 1

    if i < h:
        tmp.extend(l[i:h])
    else:
        tmp.extend(l[j:m])

    l[low:high] = tmp

    return


def _inplace_merge_sort(low, high, l):

    if low + 1 >= high:
        return

    n = high - low
    mid = low + n // 2

    _inplace_merge_sort(low, mid, l)
    _inplace_merge_sort(mid, high, l)

    inplace_merge(low, mid, high, l)

    return


@test_sort
def inplace_merge_sort(l):
    _inplace_merge_sort(0, len(l), l)
    return


def partition(low, high, l):
    target, j = l[low], low
    for i in range(low + 1, high):
        if l[i] < target:
            j += 1
            l[i], l[j] = l[j], l[i]

    l[low], l[j] = l[j], l[low]

    return j


def _quick_sort(low, high, l):
    if low < high:
        target = partition(low, high, l)
        _quick_sort(low, target, l)
        _quick_sort(target + 1, high, l)

    return


@test_sort
def quick_sort(l):
    _quick_sort(0, len(l), l)
    return


if __name__ == "__main__":
    insertion_sort()
    bubble_sort()
    selection_sort()
    heap_sort()
    merge_sort()
    inplace_merge_sort()
    quick_sort()
