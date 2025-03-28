from __future__ import annotations
from typing import Generic, TypeVar
from dataclasses import dataclass

import random

T = TypeVar("T")


@dataclass
class Node(Generic[T]):
    left: Node[T] = None
    right: Node[T] = None
    value: T = None


class MyCircularDequeue(Generic[T]):
    def __init__(self, n: int):
        self.n, self.len = n, 0
        self.head, self.tail = Node(), Node()
        self.head.right, self.tail.left = self.tail, self.head

    def _add(self, node: Node[T], new: Node[T]):
        right, node.right = node.right, new
        new.left, new.right, right.left = node, right, new

    def _del(self, node: Node[T]):
        left, right = node.left, node.right
        left.right, right.left = right, left

    def insertFront(self, val: T) -> bool:
        if self.len == self.n:
            return False
        self._add(self.head, Node(None, None, val))
        self.len += 1
        return True

    def insertLast(self, val: T) -> bool:
        if self.len == self.n:
            return False
        self._add(self.tail.left, Node(None, None, val))
        self.len += 1
        return True

    def deleteFront(self) -> bool:
        if self.len == 0:
            return False
        self._del(self.head.right)
        self.len -= 1
        return True

    def deleteLast(self) -> bool:
        if self.len == 0:
            return False
        self._del(self.tail.left)
        self.len -= 1
        return True

    def front(self) -> T:
        return self.head.right.value

    def last(self) -> T:
        return self.tail.left.value

    def empty(self) -> T:
        return self.len == 0

    def full(self) -> T:
        return self.len == self.n

    def __iter__(self):
        node = self.head.right

        while node != self.tail:
            yield node.value
            node = node.right

    def __repr__(self):
        return str([*self])


if __name__ == "__main__":

    deque = MyCircularDequeue[int](5)

    for val in range(10, 50, 10):
        assert deque.insertLast(val)

    assert deque.deleteFront()
    assert deque.deleteLast()

    assert not (deque.empty())

    for val in range(40, 70, 10):
        assert deque.insertFront(val)

    assert deque.full()

    print(deque)
