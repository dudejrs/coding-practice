from __future__ import annotations
from typing import Generic, TypeVar
from collections import deque
import random

TEST_CASES = 10
MAX_VALUE = 100
MAX_DEPTH = 20

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

    def __str__(self):
        return str([*self])


def solve(node: Node[int], left: int, right: int) -> int:

    def dfs(cur: Node[int]) -> int:
        if not cur:
            return 0
        if cur.value < left:
            return dfs(cur.right)
        if cur.value >= right:
            return dfs(cur.left)

        return cur.value + dfs(cur.left) + dfs(cur.right)

    return dfs(node)


def solve2(node: Node[int], left: int, right: int) -> int:
    queue = deque([node])
    acc = 0

    while queue:
        cur = queue.popleft()
        if not cur:
            continue
        if cur.value > left:
            queue.append(cur.left)
        if cur.value < right:
            queue.append(cur.right)
        if left <= cur.value < right:
            acc += cur.value

    return acc


def initialize(depth: int, left: int, right: int):
    if left + 1 >= right:
        return

    if depth >= MAX_DEPTH:
        return None

    if depth > 0 and random.random() / depth < 1 / MAX_DEPTH:
        return None

    mid = random.randrange(left + 1, right)

    left_node = initialize(depth + 1, left, mid)
    right_node = initialize(depth + 1, mid, right)

    return Node(mid, left_node, right_node)


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        node = initialize(0, 0, MAX_VALUE)
        right = random.randrange(1, MAX_VALUE)
        left = random.randrange(right)
        print(solve(node, left, right), solve2(node, left, right))
