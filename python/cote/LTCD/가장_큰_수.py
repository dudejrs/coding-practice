from typing import List
import random

MAX_VALUE = 1000
TEST_CASES = 10
N = 1000


def solve(nums: List[int]) -> int:

    def to_swap(a: int, b: int) -> bool:
        return str(a) + str(b) < str(b) + str(a)

    for i in range(len(nums)):
        cur = i - 1
        while cur >= 0 and to_swap(nums[cur], nums[cur + 1]):
            nums[cur], nums[cur + 1] = nums[cur + 1], nums[cur]
            cur -= 1

    return int("".join(list(map(str, nums))))


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        n = random.randrange(1, N)
        nums = [random.randrange(MAX_VALUE) for _ in range(n)]
        print(solve(nums))
