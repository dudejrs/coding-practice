from typing import List
import heapq
import random

TEST_CASES = 10
N = 10000
MAX_VALUE = 10000

def solve(nums: List[int], k: int) -> int :
	heapq.heapify(nums)

	for _ in range(len(nums) - k) :
		heapq.heappop(nums)

	return heapq.heappop(nums)

def solve2(nums: List[int], k: int) -> int :
	return heapq.nlargest(k, nums)[-1]

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		nums = [random.randrange(MAX_VALUE) for _ in range(random.randrange(2, N))]
		k = random.randrange(1, len(nums))
		print(solve([*nums], k), solve2([*nums], k))