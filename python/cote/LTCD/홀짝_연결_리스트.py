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
        cur = self

        while cur:
            yield cur.value
            cur = cur.next


def solve(node: Node[T]) -> Node[T]:

    if node is None:
        return None

    odd = node
    even = node.next
    evenhead = even

    while even and even.next:
        odd.next, even.next = even.next, even.next.next
        odd, even = odd.next, even.next

    odd.next = evenhead

    return node


if __name__ == "__main__":

    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(1, N)

        cur = n
        prev = Node(cur)
        cur -= 1

        while cur > 0:
            prev = Node(cur, prev)
            cur -= 1

        print([*solve(prev)], n)

    pass
