from typing import List
import itertools
import random

TEST_CASES = 10
N = 5


def solve(nums: List[int]) -> List[List[int]]:
    ret = []
    prev = []

    def dfs(elements: List[int]):

        if len(elements) == 0:
            ret.append(prev[:])

        for e in elements:
            next = elements[:]
            next.remove(e)

            prev.append(e)
            dfs(next)
            prev.pop()

    dfs(nums)
    return ret


def solve2(nums: List[int]) -> List[List[int]]:
    return list(itertools.permutations(nums))


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        nums = random.sample(range(1, 3 * N), N)
        print(solve(nums), solve2(nums))
