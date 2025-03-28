from typing import List
from collections import Counter
import heapq
import random

TEST_CASES = 10
N = 10000
MAX_LENGTH = 10 * N
K = 10


def solve(nums: List[int], k: int) -> List[int]:
    freq = Counter(nums)
    heap = []

    for f in freq:
        heapq.heappush(heap, (-freq[f], f))

    ret = []
    for _ in range(min(len(heap), k)):
        ret.append(heapq.heappop(heap)[1])

    return sorted(ret)


def solve2(nums: List[int], k: int) -> List[int]:
    return list(zip(*Counter(nums).most_common(k)))[0]


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):

        nums = [random.randrange(N) for _ in range(random.randrange(2, MAX_LENGTH))]
        k = random.randrange(2, min(K, len(nums)))

        print(solve(nums, k), solve2(nums, k))
