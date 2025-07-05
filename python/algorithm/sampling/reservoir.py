import random


def solve(items: list[int], k: int):
    n = len(items)
    reservoir = [items[i] for i in range(k)]

    for i in range(k, n):
        j = random.randrange(i + 1)
        if j < k:
            reservoir[j] = items[i]

    return reservoir
