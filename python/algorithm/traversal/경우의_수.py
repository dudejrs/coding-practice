from typing import List


def solve(n: int, k: int, r: int) -> int:
    selected: List[int] = []

    def traverse(cur: int) -> int:
        if len(selected) == k:
            return 1 if sum(selected) % r == 0 else 0
        count: int = 0

        for i in range(cur, n + 1):
            selected.append(i)
            count += traverse(i + 1)
            selected.pop()

        return count

    return traverse(1)
