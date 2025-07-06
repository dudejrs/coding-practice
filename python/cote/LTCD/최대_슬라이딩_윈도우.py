from typing import List
from collections import deque
import sys
import random

TEST_CASES = 10
N = 100
K = 100


def solve(nums: List[int], k: int) -> List[int]:
    ret = []
    window = deque()

    curmax = float("-inf")

    for i, v in enumerate(nums):
        window.append(v)

        if i < k - 1:
            continue

        if curmax == float("-inf"):
            curmax = max(window)
        elif v > curmax:
            curmax = v

        ret.append(curmax)

        if curmax == window.popleft():
            curmax = float("-inf")

    return ret


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        k = random.randrange(2, K)
        n = random.randrange(k + 1, N)
        nums = [random.randrange(N) + i * N // 10 for i in range(n)]
        print(nums, solve(nums, k))
