from __future__ import annotations
from typing import Generic, TypeVar
import random

TEST_CASES = 10
N = 100
MAX_VALUE = 1000

T = TypeVar("T")


class Node(Generic[T]):

    def __init__(self, value: T, next: Node[T] = None):
        self.value = value
        self.next = next

    def __iter__(self):
        node = self

        while node:
            yield node.value
            node = node.next

    def __str__(self):
        return str([*self])


def initialize() -> Node[T]:
    n = random.randrange(N - 1) + 1
    count = 0

    node = Node(random.randrange(MAX_VALUE))
    root = node

    while count < n:
        node.next = Node(random.randrange(MAX_VALUE))
        node = node.next
        count += 1

    return root


def merge(l1: Node[T], l2: Node[T]):
    if l1 and l2:
        if l1.value > l2.value:
            l1, l2 = l2, l1
        l1.next = merge(l1.next, l2)

    return l1 or l2


def solve1(node: Node[T]) -> Node[T]:

    if not (node and node.next):
        return node

    half, slow, fast = None, node, node

    while fast and fast.next:
        half, slow, fast = slow, slow.next, fast.next.next

    half.next = None

    l1 = solve1(node)
    l2 = solve1(slow)

    return merge(l1, l2)


def solve2(node: Node[T]) -> Node[T]:

    def partition(node: Node[T]) -> Node[T]:
        pivot = node.value
        slow, left, right = node, node.next, node.next

        while right:
            if right.value < pivot:
                left.value, right.value = right.value, left.value
                slow, left = left, left.next
            right = right.next

        node.value, slow.value = slow.value, node.value

        hi, slow.next = left, None

        return node, hi

    def quicksort(node: Node[T]) -> Node[T]:
        if not (node and node.next):
            return node

        lo, hi = partition(node)
        lo = quicksort(lo)
        hi = quicksort(hi)

        cur = lo
        while cur.next:
            cur = cur.next

        cur.next = hi

        return node

    return quicksort(node)


def solve3(node: Node[T]) -> Node[T]:
    l = sorted([*node])
    cur = node

    for i in l:
        cur.value = i
        cur = cur.next

    return node


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        node = initialize()
        print(solve1(node))
