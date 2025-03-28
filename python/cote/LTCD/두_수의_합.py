from typing import *
import random


TEST_CASES = 10
N = 1000
TARGET = 1.5 * N


def solve(nums: List[int], target: int) -> List[int]:
    num_to_index = {num: i for i, num in enumerate(nums)}

    for i, num in enumerate(nums):
        if target - num in num_to_index and i != num_to_index[target - num]:
            return [i, num_to_index[target - num]]

    return []


if __name__ == "__main__":

    random.seed(43)

    for _ in range(TEST_CASES):

        n = random.randrange(N - 1) + 1
        nums = random.sample(range(0, N - 1), n)
        target = random.randrange(1, TARGET - 1) + 1

        print(solve(nums, target))

    pass
