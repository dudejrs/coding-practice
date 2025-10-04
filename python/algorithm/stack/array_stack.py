from typing import Generic, Sequence, Any, Union, Optional, overload
from .stack import T, Stack


class FixedArray(Sequence[Optional[T]]):
    def __init__(self, size: int):
        self.items: list[Optional[T]] = [None] * size
        self.size = size

    @overload
    def __getitem__(self, index: int, /) -> Optional[T]: ...

    @overload
    def __getitem__(self, s: slice, /) -> Sequence[Optional[T]]: ...

    def __getitem__(self, key: Union[int, slice], /) -> Union[Optional[T], Sequence[Optional[T]]]:
        if isinstance(key, slice) and key.stop >= self.size:
            raise IndexError()

        if isinstance(key, int) and key >= self.size:
            raise IndexError()

        if val := self.items[key]:
            return val

        raise Exception()

    def __setitem__(self, index: int, item: T):
        self.items[index] = item

    def __delitem__(self, index: int) -> None:
        if index < 0 or index >= self.size:
            raise IndexError("index out of range")
        self.items[index] = None

    def __len__(self) -> int:
        return self.size

    def __contains__(self, item: object) -> bool:
        return item in self.items

    def empty(self) -> bool:
        return all(x is None for x in self.items)


class ArrayStack(Stack, Generic[T]):

    def __init__(self, size: int):
        self.items: FixedArray[T] = FixedArray(size)
        self.top = 0

    def push(self, item: T):
        self.items[self.top] = item
        self.top += 1

    def pop(self) -> T:
        if self.top == 0 or self.items.empty():
            raise Exception("stack is empty")

        self.top -= 1
        val = self.items[self.top]
        del self.items[self.top]

        assert val is not None
        return val

    def __contains__(self, item: T) -> bool:
        return item in self.items
