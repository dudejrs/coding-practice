from typing import List
from functools import reduce
from collections import defaultdict, Counter
import heapq
import random

N = 20
MAX_COST = 100
TEST_CASES = 10


def initialize(n: int) -> List[int]:
    ret = []

    for i in range(n):
        for j in range(i + 1, n):
            if random.random() < 0.25:
                continue
            ret.append([i, j, random.randrange(1, MAX_COST)])

    counter = Counter(reduce(list.__add__, map(lambda l: [l[0], l[1]], ret)))
    src = counter.most_common(1)[0][0]
    dst = counter.most_common(2)[1][0]

    return ret, src, dst


def solve(edges: List[int], src: int, dst: int, k: int) -> int:

    graph = defaultdict(list)

    for a, b, w in edges:
        graph[a].append((b, w))
        graph[b].append((a, w))

    Q = [(0, src, k)]

    while Q:
        price, node, k = heapq.heappop(Q)

        if node == dst:
            return price

        if k >= 0:
            for v, w in graph[node]:
                heapq.heappush(Q, (price + w, v, k - 1))

    return -1


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(3, N)
        k = random.randrange(1, n)
        edges, src, dst = initialize(n)
        print(solve(edges, src, dst, k))
