from __future__ import annotations
from typing import Generic, TypeVar
from collections import deque
import random

TEST_CASES = 10
MAX_DEPTH = 20
MAX_VALUE = 100

T = TypeVar("T")


class Node(Generic[T]):

    def __init__(self, value: T, left: Node[T] = None, right: Node[T] = None):
        self.value = value
        self.left = left
        self.right = right

    def __iter__(self):
        queue = deque([self])

        while queue:
            node = queue.popleft()

            if node:
                yield node.value
                queue.append(node.left)
                queue.append(node.right)
            else:
                yield None

        return

    def __str__(self):
        return str([*self])


def solve(node1: Node[T], node2: Node[T]) -> Node[T]:
    if node1 and node2:
        left = solve(node1.left, node2.left)
        right = solve(node1.right, node2.right)
        return Node(node1.value + node2.value, left, right)
    else:
        return node1 or node2


def initialize(depth: int = 0) -> Node[T]:

    if depth >= MAX_DEPTH:
        return None

    if depth > 0 and random.random() / depth < 1 / MAX_DEPTH:
        return None

    left = initialize(depth + 1)
    right = initialize(depth + 1)

    return Node(random.randrange(MAX_VALUE), left, right)


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        node1, node2 = initialize(), initialize()
        print(node1, node2)
        print(solve(node1, node2))
