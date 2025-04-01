from collections.abc import Generator
from typing import FrozenSet, Set


def solve(n: int, k: int) -> Generator[FrozenSet[int], None, None]:
    selected: Set[int] = set()

    def traverse(cur: int) -> Generator[FrozenSet[int], None, None]:
        if len(selected) == k:
            yield frozenset(selected)

        if cur > n:
            return

        for i in range(cur, n + 1):
            selected.add(i)
            yield from traverse(i + 1)
            selected.remove(i)

        return

    yield from traverse(1)
