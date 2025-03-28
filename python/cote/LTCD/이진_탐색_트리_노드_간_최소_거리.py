from __future__ import annotations
from typing import Generic, TypeVar
from collections import deque
import random
import sys

TEST_CASES = 10
MAX_DEPTH = 20
MAX_VALUE = sys.maxsize // 1000000000

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


def initialize(depth: int, left: int, right: int) -> Node[int]:

    if left + 1 >= right:
        return None
    if depth >= MAX_DEPTH:
        return None
    if depth > 0 and random.random() / depth < 1 / MAX_DEPTH:
        return None

    mid = random.randrange(left + 1, right)

    left_node = initialize(depth + 1, left, mid)
    right_node = initialize(depth + 1, mid + 1, right)

    return Node(mid, left_node, right_node)


def solve(node: Node[int]) -> int:
    prev, ret = -sys.maxsize, sys.maxsize

    def inorder_traverse(cur: Node[int]):
        nonlocal prev, ret

        if cur.left:
            inorder_traverse(cur.left)

        ret = min(ret, cur.value - prev)
        prev = cur.value

        if cur.right:
            inorder_traverse(cur.right)
        return

    inorder_traverse(node)
    return ret


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        node = initialize(0, 0, MAX_VALUE)
        print(solve(node))
