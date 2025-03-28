from __future__ import annotations
from typing import TypeVar, Generic
import random

TEST_CASES = 10
N = 100

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


def solve(node: Node[T], n, m):

    root = start = Node(None, node)

    for _ in range(n - 1):
        start = start.next

    end = start.next

    for _ in range(m - n):
        tmp, start.next, end.next = start.next, end.next, end.next.next
        start.next.next = tmp

    return root.next


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(1, N)
        end = random.randrange(1, n)
        start = random.randrange(1, end)

        cur = n
        prev = Node(cur)
        cur -= 1

        while cur > 0:
            prev = Node(cur, prev)
            cur -= 1
        print(start, end)
        print([*solve(prev, start, end)])
