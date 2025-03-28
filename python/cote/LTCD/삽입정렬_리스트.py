from __future__ import annotations
from typing import Generic, TypeVar
import random

TEST_CASES = 10
N = 10
MAX_VALUE = N * 2

T = TypeVar("T")


class Node(Generic[T]):

    def __init__(self, value: T, next_: Node[T] = None):
        self.value = value
        self.next = next_

    def __iter__(self):
        node = self
        while node:
            yield node.value
            node = node.next

    def __str__(self):
        return str([*self])


def initialize() -> Node[int]:
    node = Node(random.randrange(MAX_VALUE))

    for _ in range(random.randrange(1, N)):
        node = Node(random.randrange(MAX_VALUE), node)

    return node


def solve(node: Node[int]) -> Node[int]:
    cur = parent = Node(-1)

    while node:
        while cur.next and cur.next.value < node.value:
            cur = cur.next

        cur.next, node.next, node = node, cur.next, node.next

        if node and node.value < cur.value:
            cur = parent

    return cur.next


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        node = initialize()
        print(solve(node))
