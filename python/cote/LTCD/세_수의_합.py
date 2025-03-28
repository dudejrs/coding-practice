from typing import *
import random

TEST_CASES = 10
N = 10000


def search(target: int, nums: List[int]) -> List[List[int]]:
    ret = []

    left, right = target + 1, len(nums) - 1

    while left < right:
        sum = nums[target] + nums[left] + nums[right]

        if sum < 0:
            left += 1
        elif sum > 0:
            right -= 1
        else:
            ret.append(sorted([nums[left], nums[right], nums[target]]))

            while left < right and nums[left] == nums[left + 1]:
                left += 1
            while left < right and nums[right] == nums[right - 1]:
                right -= 1

            left += 1
            right -= 1

    return ret


def solve(nums: List[int]) -> List[List[int]]:
    ret = []

    nums.sort()

    for i in range(len(nums) - 2):

        if nums[i] > 0 and nums[i] == nums[i - 1]:
            continue

        tmp = search(i, nums)

        if len(tmp) != 0:
            ret.extend(tmp)

    return ret


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(100, N)
        nums = random.sample(range(-(n // 2), n // 2), n // 2)
        print(solve(nums))
