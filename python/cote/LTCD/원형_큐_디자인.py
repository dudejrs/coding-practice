from __future__ import annotations
from typing import Generic, TypeVar

T = TypeVar("T")


class MyCircularQueue(Generic[T]):
    def __init__(self, n: int):
        self.q = [None] * n
        self.n = n
        self.start = 0
        self.end = 0

    def enqueue(self, val: T) -> bool:
        if self.q[self.end] is None:
            self.q[self.end] = val
            self.end = (self.end + 1) % self.n
            return True

        return False

    def dequeue(self) -> bool:
        if self.q[self.start] is None:
            return False
        self.q[self.start] = None
        self.start = (self.start + 1) % self.n

        return True

    def back(self) -> T:
        return self.q[self.end - 1]

    def front(self) -> T:
        return self.q[self.start]

    def isfull(self) -> bool:
        return self.start == self.end

    def __repr__(self):
        return str(self.q)


if __name__ == "__main__":

    myqueue = MyCircularQueue(5)

    for val in range(10, 50, 10):
        assert myqueue.enqueue(val)

    assert myqueue.back() == 40
    assert not myqueue.isfull()

    for _ in range(2):
        assert myqueue.dequeue()

    for val in range(50, 80, 10):
        assert myqueue.enqueue(val)

    assert myqueue.front() == 30
    assert myqueue.back() == 70
    assert myqueue.isfull()
    print(myqueue)
