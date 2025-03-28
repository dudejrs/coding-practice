from __future__ import annotations
from typing import TypeVar, Generic
from collections import deque
import random

T = TypeVar("T")


class Mystack(Generic[T]):
    def __init__(self):
        self.q = deque()

    def push(self, x: T):
        self.q.append(x)

        for _ in range(len(self.q) - 1):
            self.q.append(self.q.popleft())

    def pop(self):
        return self.q.popleft()

    def top(self):
        return self.q[0]

    def empty(self):
        return len(self.q) == 0


if __name__ == "__main__":

    stack = Mystack[int]()
    ret = []

    for _ in range(10):
        t = random.randrange(100)
        stack.push(t)
        ret.append(t)

    print(ret[::-1])
    print([stack.pop() for _ in range(10)])
