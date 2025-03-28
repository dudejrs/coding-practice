from typing import Set


def solve(n: int, k: int) -> Set[Set[int]]:
    ret = set()
    selected = set()

    def traverse(cur: int):
        if len(selected) == k:
            ret.add(frozenset(selected))
            return

        if cur > n:
            return

        for i in range(cur, n + 1):
            selected.add(i)
            traverse(i + 1)
            selected.remove(i)

        return

    traverse(1)
    return ret
