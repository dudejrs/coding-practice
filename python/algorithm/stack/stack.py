from abc import ABC, abstractmethod
from typing import TypeVar, Generic
from collections.abc import Hashable

T = TypeVar('T', bound=Hashable)


class Stack(ABC, Generic[T]):
    @abstractmethod
    def push(self, item: T):
        pass

    @abstractmethod
    def pop(self) -> T:
        pass

    @abstractmethod
    def __contains__(self, item: T) -> bool:
        pass
