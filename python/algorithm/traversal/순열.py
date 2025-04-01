from collections.abc import Generator
from typing import List


def solve(n: int, k: int) -> Generator[List[int], None, None]:
    visited: List[bool] = [False for _ in range(n)]
    selected: List[int] = []

    def traverse() -> Generator[List[int], None, None]:
        if len(selected) == k:
            yield selected

        for i in range(n):
            if visited[i]:
                continue
            selected.append(i + 1)
            visited[i] = True
            yield from traverse()
            visited[i] = False
            selected.pop()

    yield from traverse()
